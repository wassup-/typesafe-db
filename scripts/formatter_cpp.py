import string

class Context:
  def __init__(self):
   self.databases = []

  def format(self):
    output =  '#include "include/meta.hpp"' '\n'
    output += '#include "include/column.hpp"' '\n'
    output += '#include "include/field.hpp"' '\n'
    output += '#include "include/table.hpp"' '\n'
    output += '#include "include/type_traits.hpp"' '\n'
    output += '\n'
    output += '{0}'
    dbs = '\n'.join([db.format() for db in self.databases])
    return output.format(dbs)

class Database:
  def __init__(self, name):
    self.name = name
    self.tables = []

  @staticmethod
  def __traverse_columns(tables):
    for table in tables:
      for column in table.columns:
        yield (table.name, column.name)

  def format(self):
    output =  'namespace {0}' '\n'
    output += '{{' '\n'
    output += '\n'
    output += 'namespace _strings' '\n'
    output += '{{' '\n'
    output += '\n'
    output += '{2}' '\n'
    output += '\n'
    output += '}}' '\n'
    output += '\n'
    output += '{1}' '\n'
    output += '}}' '\n'

    column_strings = self.__traverse_columns(self.tables)
    column_strings = ['constexpr static char const {0}_{1}[] = "{1}";'.format(table, column) for (table, column) in column_strings]
    table_strings = ['constexpr static char const {0}[] = "{0}";'.format(table.name) for table in self.tables]
    strings = '\n'.join(['{0}'.format(string) for string in (table_strings + column_strings)])

    tables = '\n'.join([table.format(self) for table in self.tables])

    return output.format(self.name, tables, strings)


class Table:
  def __init__(self, name):
    self.name = name
    self.columns = []
    self.primaries = []
    self.uniques = []
    self.indices = []

  def format(self, db):
    output =  'struct {0} : fp::table<{0}>' '\n'
    output += '{{' '\n'
    output += '\tconstexpr static const char* _name() noexcept {{ return _strings::{0}; }}' '\n'
    output += '\n'
    output += '{1}' '\n' # columns
    output += '\n'
    output += '{2}' '\n' # record type
    output += '\n'
    output += '{3}' '\n' # primaries
    output += '{4}' '\n' # uniques
    output += '{5}' '\n' # indices
    output += '}};' '\n'

    columns = '\n'.join(['\t{0}'.format(x) for x in [column.format(self) for column in self.columns]])
    record    = '\tusing columns = meta::transform<meta::list<{0}>, meta::quote<fp::Unqualified> >;'.format(', '.join('decltype({0})'.format(column.name) for column in self.columns))
    primaries = '\tusing primary_keys = meta::transform<meta::list<{0}>, meta::quote<fp::Unqualified> >;'.format(', '.join('decltype({0})'.format(column.name) for column in self.primaries))
    uniques   = '\tusing unique_keys  = meta::transform<meta::list<{0}>, meta::quote<fp::Unqualified> >;'.format(', '.join('decltype({0})'.format(column.name) for column in self.uniques))
    indices   = '\tusing index_keys   = meta::transform<meta::list<{0}>, meta::quote<fp::Unqualified> >;'.format(', '.join('decltype({0})'.format(column.name) for column in self.indices))

    return output.format(self.name, columns, record, primaries, uniques, indices)


class Column:
  def __init__(self, name):
    self.name = name
    self.type = None
    self.is_foreign = False
    self.foreign_type = None

  def format(self, table):
    return 'constexpr static fp::column<{0}, _strings::{0}_{1}, fp::field<{2}>> {1} = {{ }};'.format(table.name, self.name, self.type)
