import argparse
import importlib

parser = argparse.ArgumentParser(description="Generate C++ classes for MySQL databases",
                                 formatter_class=argparse.ArgumentDefaultsHelpFormatter)
parser.add_argument('--engine', default='mysql', help='DBMS to use')
parser.add_argument('--host', default='localhost', help='host to connect to')
parser.add_argument('--user', default='root', help='username to use for connection')
parser.add_argument('--pass', dest='passwd', help='password to use for connection')
parser.add_argument('--db', nargs='*', help='databases to use')

args = parser.parse_args();

dbms = importlib.import_module('dbms_{0}'.format(args.engine))

if not dbms.connect(args.host, args.user, args.passwd):
  print("Unable to connect to database")
  sys.exit()

for db in dbms.databases(args.db):
  # every namespace denotes a database
  print 'namespace', db.name
  print '{'

  strings = []
  deferred = []

  for table in db.tables():
    # every table denotes a struct
    deferred.append('struct {0}'.format(table.name))
    deferred.append('{')

    primaries = []
    uniques = []
    indices = []

    deferred.append('constexpr static fp::table<{0}, _strings::{0}> table = {{ }};'.format(table.name))
    strings.append((table.name, ''))

    for column in table.columns():
      strings.append((table.name, column.name))
      deferred.append('constexpr static fp::column<{0}, _strings::{0}_{1}, fp::field<{2}>> {1} = {{ }};'.format(table.name, column.name, column.type))
      if column.primary:
        primaries.append(column.name)
      elif column.unique:
        uniques.append(column.name)
      elif column.indexed:
        indices.append(column.name)

    format_str = 'fp::Unqualified<decltype({0})>'
    primaries = map(format_str.format, primaries)
    uniques = map(format_str.format, uniques)
    indices = map(format_str.format, indices)

    deferred.append('using primary_key = mpl::identity<{0}>;'.format(', '.join(primaries)))
    deferred.append('using unique_key = mpl::identity<{0}>;'.format(', '.join(uniques)))
    deferred.append('using index_key = mpl::identity<{0}>;'.format(', '.join(indices)))

    deferred.append('};')
  # print all referenced strings
  print 'namespace', '_strings'
  print '{'
  for (table, column) in strings:
    if column:
      print 'constexpr static char const {0}_{1}[] = "{1}";'.format(table, column)
    else:
      print 'constexpr static char const {0}[] = "{0}";'.format(table)
  print '}'
  for line in deferred:
    print line
  print '}'

dbms.disconnect()
