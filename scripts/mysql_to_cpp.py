import argparse
import mysql.connector
from mysql.connector import errorcode
import random
import re
import string

def connect_mysql(host, user, passwd):
  try:
    conn = mysql.connector.connect(host= host,
                                   user= user,
                                   password= passwd)
  except mysql.connector.Error as err:
    if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
      print('Wrong username and/or password')
    elif err.errno == errorcode.ER_BAD_DB_ERROR:
      print('Database does not exist')
    else:
      print(err)
  else:
    return conn

def list_databases(conn, dbs):
  if dbs:
    return dbs
  databases = []
  cursor = conn.cursor()
  query = ('SHOW DATABASES')
  try:
    cursor.execute(query)
    for (database,) in cursor:
      databases.append(database)
  except:
    print('Unable to list databases')
  else:
    cursor.close()
    return databases

def list_tables(conn, db):
  tables = []
  cursor = conn.cursor()
  query = ('SHOW TABLES FROM ' + db)
  try:
    cursor.execute(query)
    for (table,) in cursor:
      tables.append(table)
  except:
    print('Unable to list tables')
  else:
    cursor.close()
    return tables

def make_column_descriptor(name, type, nullable, primary, indexed, unique, default):
  return (name, type, nullable, primary, indexed, unique, default)

def list_columns(conn, db, table):
  columns = []
  cursor = conn.cursor()
  query = ('SHOW COLUMNS FROM ' + table + ' FROM ' + db)
  try:
    cursor.execute(query)
    for (name, type, nullable, key, default, extra) in cursor:
      descr = make_column_descriptor(name, type, (nullable == 'YES'), (key == 'PRI'), (key == 'MUL'), (key == 'UNI'), default)
      columns.append(descr)
  except:
    print('Unable to list columns')
  else:
    cursor.close()
    return columns

def id_generator(size=6, chars=string.ascii_lowercase + string.digits):
  return ''.join(random.choice(chars) for _ in range(size))

def map_type(type, nullable):
  m = re.search(r"^([^(]+)(\((.+)\))?(\sunsigned)?$", type)
  mt = m.group(1, 4, 3)
  # lambdas
  native_bits = lambda unsigned, extent: 'std::array<bool, ' + extent + '>';
  native_bool = lambda unsigned, extent: 'bool'
  native_int8 = lambda unsigned, extent: 'unsigned char' if unsigned else 'char'
  native_int16 = lambda unsigned, extent: 'unsigned short' if unsigned else 'short'
  native_int32 = lambda unsigned, extent: 'unsigned int' if unsigned else 'int'
  native_int64 = lambda unsigned, extent: 'uint64' if unsigned else 'int64'
  native_double = lambda unsigned, extent: 'double'
  native_float = lambda unsigned, extent: 'float'
  native_chars = lambda unsigned, extent: 'char[' + extent + ']'
  native_string = lambda unsigned, extent: 'std::string'
  native_text = lambda unsigned, extent: 'std::string'
  native_blob = lambda unsigned, extent: 'std::vector<unsigned char>'
  native_date = lambda unsigned, extent: 'boost::datetime'
  native_time = lambda unsigned, extent: 'boost::datetime'
  native_datetime = lambda unsigned, extent: 'boost::datetime'
  native_timestamp = lambda unsigned, extent: 'boost::datetime'
  native_enum = lambda unsigned, extent: 'enum_' + id_generator()
  # mappings
  mappings = {
    # integral types
    'bit': native_bits,
    'bool': native_bool,
    'tinyint': native_int8,
    'smallint': native_int16,
    'int': native_int32,
    'integer': native_int32,
    'bigint': native_int64,
    # real types
    'decimal': native_double,
    'dec': native_double,
    'numeric': native_double,
    'fixed': native_double,
    'double': native_double,
    'float': native_float,
    # string types
    'char': native_chars,
    'varchar': native_string,
    # text types
    'tinytext': native_text,
    'text': native_text,
    'mediumtext': native_text,
    'longtext': native_text,
    # blob types
    'tinyblob': native_blob,
    'blob': native_blob,
    'mediumblob': native_blob,
    'longblob': native_blob,
    # time types
    'datetime': native_datetime,
    'date': native_date,
    'time': native_time,
    'timestamp': native_timestamp,
    # enum types
    'set': native_enum,
    'enum': native_enum
  }

  mapped = mappings[mt[0]](mt[1], mt[2]);
  return mapped if not nullable else mapped + '*'


parser = argparse.ArgumentParser(description="Generate C++ classes for MySQL database",
                                 formatter_class=argparse.ArgumentDefaultsHelpFormatter)
parser.add_argument('--host', default='localhost', help='host to connect to')
parser.add_argument('--user', default='root', help='username to use for connection')
parser.add_argument('--pass', dest='passwd', help='password to use for connection')
parser.add_argument('--db', nargs='*', help='databases to use')

args = parser.parse_args();

conn = connect_mysql(args.host, args.user, args.passwd)
if(conn is None):
  print("Unable to connect to database")
  sys.exit()

for db in list_databases(conn, args.db):
  # every namespace denotes a database
  print 'namespace', db
  print '{'

  strings = []
  deferred = []

  for table in list_tables(conn, db):
    # every table denotes a struct
    deferred.append('struct {0}'.format(table))
    deferred.append('{')
    deferred.append('constexpr static fp::table<{0}, _strings::{0}> table = {{ }};'.format(table))
    strings.append((table, ''))

    for (name, type, nullable, primary, indexed, unique, default) in list_columns(conn, db, table):
      native_type = map_type(type, nullable)
      strings.append((table, name))
      deferred.append('constexpr static fp::column<{0}, _strings::{0}_{1}, fp::field<{2}> > {1} = {{ }};'.format(table, name, native_type))

    deferred.append('};')
  # print all referenced strings
  print 'namespace', '_strings'
  print '{'
  for (table, field) in strings:
    if field:
      print 'constexpr static char const {0}_{1}[] = "{1}";'.format(table, field)
    else:
      print 'constexpr static char const {0}[] = "{0}";'.format(table)
  print '}'
  for line in deferred:
    print line
  print '}'

conn.close()
