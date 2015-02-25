import importlib
import mysql.connector
from mysql.connector import errorcode
import re

conn = None
util = importlib.import_module('util')

class MySQLDatabase:
  def __init__(self, conn, name):
    self.conn = conn
    self.name = name

  def tables(self):
    tbls = []
    query = ('SHOW TABLES FROM {0}'.format(self.name))
    try:
      cursor = self.conn.cursor()
      cursor.execute(query)
      tbls = [table for (table,) in cursor]
    except:
      print('Unable to list tables')
    else:
      cursor.close()
    return [MySQLTable(self.conn, self, table) for table in tbls]

class MySQLTable:
  def __init__(self, conn, db, name):
    self.conn = conn
    self.db = db
    self.name = name

  def columns(self):
    clmns = []
    query = ('SHOW COLUMNS FROM {0} FROM {1}'.format(self.name, self.db.name))
    try:
      cursor = self.conn.cursor()
      cursor.execute(query)
      clmns = [(name, type, (nullable == 'YES'), (key == 'PRI'), (key == 'MUL'), (key == 'UNI'), default) for (name, type, nullable, key, default, extra) in cursor]
    except:
      print('Unable to list columns')
    else:
      cursor.close()
    return [MySQLColumn(self.conn, self, *column) for column in clmns]

class MySQLColumn:
  def __init__(self, conn, table, name, type, nullable, primary, multiple, unique, default):
    self.conn = conn
    self.table = table
    self.name = name
    self.nullable = nullable
    self.primary = primary
    self.indexed = multiple
    self.unique = unique
    self.default = default
    self.is_foreign = self.__is_foreign_key()
    self.foreign_type = self.__get_foreign_type()
    self.type = self.__native_type(type)

  def __is_foreign_key(self):
    result = False
    query = (('SELECT'
              '  1 '
              ' FROM '
              '  INFORMATION_SCHEMA.KEY_COLUMN_USAGE'
              ' WHERE '
              '  (TABLE_SCHEMA = "{0}")'
              '  AND (TABLE_NAME = "{1}")'
              '  AND (COLUMN_NAME = "{2}")'
              '  AND (REFERENCED_COLUMN_NAME IS NOT NULL)').format(self.table.db.name, self.table.name, self.name))
    try:
      cursor = self.conn.cursor()
      cursor.execute(query)
      result = True if cursor.fetchall() else False
    except:
      print('Unable to list foreign key relationships')
    else:
      cursor.close()
    return result

  def __get_foreign_type(self):
    results = []
    query = (('SELECT'
              '  REFERENCED_TABLE_SCHEMA, REFERENCED_TABLE_NAME, REFERENCED_COLUMN_NAME '
              ' FROM '
              '  INFORMATION_SCHEMA.KEY_COLUMN_USAGE'
              ' WHERE '
              '  (TABLE_SCHEMA = "{0}")'
              '  AND (TABLE_NAME = "{1}")'
              '  AND (COLUMN_NAME = "{2}")'
              '  AND (REFERENCED_COLUMN_NAME IS NOT NULL)').format(self.table.db.name, self.table.name, self.name))
    try:
      cursor = self.conn.cursor()
      cursor.execute(query)
      results = [x for x in cursor]
    except:
      print('Unable to list foreign key relationships')
    else:
      cursor.close()
    return results[0] if results else None

  def __native_type(self, type):
    m = re.search(r"^([^(]+)(\((.+)\))?(\sunsigned)?$", type, re.IGNORECASE)
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
    native_enum = lambda unsigned, extent: 'enum_' + util.id_generator()
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
    if not self.nullable:
      return mapped
    else:
      return '{0}*'.format(mapped)


def connect(host, user, passwd):
  global conn

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
    return False
  else:
    return True

def disconnect():
  global conn
  conn.close()

def databases(dbs):
  global conn

  if not dbs:
    cursor = conn.cursor()
    query = ('SHOW DATABASES')
    try:
      cursor.execute(query)
      dbs = [database for (database,) in cursor]
    except:
      print('Unable to list databases')
    else:
      cursor.close()
  return [MySQLDatabase(conn, db) for db in dbs]

