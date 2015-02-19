import fnmatch
import os

def get_subdirs(dir):
  return [root for root, dirnames, filenames in os.walk(dir)]

def get_sourcefiles(dir):
  sources = []
  for root, dirnames, filenames in os.walk(dir):
    for filename in fnmatch.filter(filenames, '*.cpp'):
      sources.append(os.path.join(root, filename))
  return sources

def get_sourcefiles_recursive(dir):
  sources = []
  for dir in get_subdirs(dir):
    sources = sources + get_sourcefiles(dir)
  return [source for source in sources if source]

def filter_unique(seq):
  seen = set()
  seen_add = seen.add
  return [ x for x in seq if not (x in seen or seen_add(x))]

current_dir = Dir('.')

env = Environment(ENV=os.environ, CPPPATH=[current_dir.abspath])
env['CC'] = os.environ['CC']
env['CXX'] = os.environ['CXX']
env.Append(LIBS=['pthread', 'mysqlclient'])
env.Append(CCFLAGS=['-std=c++11', '-Wall', '-Werror', '-pedantic-errors', '-O3', '-MMD'])

sources = get_sourcefiles_recursive(current_dir.abspath)
sources = filter_unique(sources)

env.Program(target='typesafe-db', source=sources)
