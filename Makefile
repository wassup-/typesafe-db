# Environment
MKDIR 	= mkdir
CP 		= cp
GREP 	= grep
NM 		= nm
AS 		= as

# Compiler flags
LDFLAGS		= -lpthread -lmysqlclient
CCFLAGS		= -c -std=c++0x -Wall -Werror -pedantic-errors -O3
CXXFLAGS 	= -c -std=c++11 -Wall -Werror -pedantic-errors -O3

CCFLAGS_DEBUG	= -c -std=c++0x -Wall -Werror -pedantic-errors -g
CXXFLAGS_DEBUG 	= -c -std=c++11 -Wall -Werror -pedantic-errors -g

# Directories
BINDIR 		= bin/
SRCDIR 		=	

DIR_GUARD 	= @mkdir -p $(@D)

# Helpers
EMPTY :=
SPACE := $(EMPTY) $(EMPTY)

FILES = src/core/impl/linux/mutex_impl.cpp \
		src/core/impl/linux/semaphore_impl.cpp \
		src/core/impl/linux/condition_impl.cpp \
		src/core/impl/linux/thread_impl.cpp \
		src/core/mutex.cpp \
		src/core/semaphore.cpp \
		src/core/condition.cpp \
		src/core/thread.cpp \
		src/core/threadpool.cpp \
		example.cpp

SOURCES	= $(SRCDIR)$(subst $(SPACE), $(SRCDIR),$(FILES))
OBJECTS	= $(subst .cpp,.o,$(BINDIR)$(subst $(SPACE), $(BINDIR),$(FILES)))
SOURCE 	= $(subst .o,.cpp,$(subst $(BINDIR),$(SRCDIR),$(1)))

EXE_PREFIX=
EXE_POSTFIX=
EXE_BASE=typesafe-db
EXECUTABLE=$(EXE_PREFIX)$(EXE_BASE)$(EXE_POSTFIX)

# Stages

all: $(EXE_BASE)

release: $(EXE_BASE)

$(EXE_BASE): $(OBJECTS)
	$(DIR_GUARD)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)

$(OBJECTS):
	$(DIR_GUARD)
	$(CXX) $(CXXFLAGS) $(call SOURCE,$@) -o $@

debug: CXXFLAGS = $(CXXFLAGS_DEBUG)
debug: CCFLAGS = $(CCFLAGS_DEBUG)
debug: $(EXE_BASE)

.PHONY: clean
clean:
	rm -rf $(BINDIR)
