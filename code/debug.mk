BUILD_CCFLAGS = -std=c++11 -Wall -Wextra -Wsign-conversion -pedantic-errors -Werror -Wuninitialized -g3  -Wno-error=unused-but-set-parameter -Wno-error=unused-parameter -Wno-error=unknown-pragmas -DDEBUG=1 $(CC_INCLUDES)
BUILD_LDFLAGS = $(LDFLAGS) -lfunctions-debug

# Makefile settings - Can be customized.
APPNAME = debug.app
EXT = .cpp
SRCDIR = .
OBJDIR = build

############## Do not change anything from here downwards! #############

SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o+debug)
DEP = $(OBJ:$(OBJDIR)/%.o+debug=%.d+debug)
# UNIX-based OS variables & settings
DELOBJ = $(OBJ)

########################################################################
####################### Targets beginning here #########################

all: $(APPNAME) cleandep

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(BUILD_CCFLAGS) -o $@ $^ $(BUILD_LDFLAGS)

%.d+debug: $(SRCDIR)/%$(EXT)
	@$(CPP) $(BUILD_CCFLAGS) $< -MM -MT $(@:%.d+debug=$(OBJDIR)/%.o+debug) >$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o+debug: $(SRCDIR)/%$(EXT)
	$(CC) $(BUILD_CCFLAGS) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)

# Cleans only all files with the extension .d+debug
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

