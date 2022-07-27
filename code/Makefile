# Compiler settings - Can be customized.
CC = g++
LIB = -I$(LIBRARY_CPP) -L$(LIBRARY_CPP)

RELEASE_LDFLAGS = -lfunctions
RELEASE_CCFLAGS = -std=c++11 -O2 $(LIB)

DEBUG_LDFLAGS = -lfunctions-debug
DEBUG_CCFLAGS = -std=c++11 -Wall -Wextra -Wsign-conversion -pedantic-errors -Werror -Wuninitialized -g3  -Wno-error=unused-but-set-parameter -Wno-error=unused-parameter -Wno-error=unknown-pragmas $(LIB)

# Makefile settings - Can be customized.
APPNAME = realease.app
APPNAMEDEV = debug.app
EXT = .cpp
SRCDIR = .
OBJDIR = build

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)

SRCDEV = $(wildcard $(SRCDIR)/*$(EXT))
OBJDEV = $(SRCDEV:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.odg)
DEPDEV = $(OBJDEV:$(OBJDIR)/%.odg=%.dg)
# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ)

DELOBJDEV = $(OBJDEV)

########################################################################
####################### Targets beginning here #########################

all: $(APPNAME) cleandep cleandepdev

dev: $(APPNAMEDEV) cleandepdev cleandep

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $^ $(RELEASE_LDFLAGS)

$(APPNAMEDEV): $(OBJDEV)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $^ $(DEBUG_LDFLAGS)

# Creates the dependecy rules
%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(RELEASE_CCFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

%.dg: $(SRCDIR)/%$(EXT)
	@$(CPP) $(DEBUG_CCFLAGS) $< -MM -MT $(@:%.dg=$(OBJDIR)/%.odg) >$@

# Includes all .h files
-include $(DEP)

-include $(DEPDEV)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(RELEASE_CCFLAGS) -o $@ -c $<

$(OBJDIR)/%.odg: $(SRCDIR)/%$(EXT)
	$(CC) $(DEBUG_CCFLAGS) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

.PHONY: cleandepdev
cleandepdev:
	$(RM) $(DEPDEV)
