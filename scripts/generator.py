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
fmt = importlib.import_module('formatter_{0}'.format('cpp'))

if not dbms.connect(args.host, args.user, args.passwd):
  print("Unable to connect to database")
  sys.exit()

ctx = fmt.Context()

for db in dbms.databases(args.db):
  # every namespace denotes a database
  fdb = fmt.Database(db.name)

  for table in db.tables():
    ftable = fmt.Table(table.name)

    for column in table.columns():
      fcolumn = fmt.Column(column.name)
      fcolumn.type = column.type
      fcolumn.is_foreign = column.is_foreign
      fcolumn.foreign_type = column.foreign_type

      if column.primary:
        ftable.primaries.append(fcolumn)
      elif column.unique:
        ftable.uniques.append(fcolumn)
      elif column.indexed:
        ftable.indices.append(fcolumn)

      ftable.columns.append(fcolumn)

    fdb.tables.append(ftable)

  ctx.databases.append(fdb)

  print ctx.format()

dbms.disconnect()
