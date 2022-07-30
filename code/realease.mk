BUILD_CCFLAGS = -std=c++11 -O2 $(CC_INCLUDES)
BUILD_LDFLAGS = $(LDFLAGS) -lfunctions

# Makefile settings - Can be customized.
APPNAME = realease.app
EXT = .cpp
SRCDIR = .
OBJDIR = build

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)

# UNIX-based OS variables & settings
DELOBJ = $(OBJ)

########################################################################
####################### Targets beginning here #########################

all: $(APPNAME) cleandep 

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(BUILD_CCFLAGS) -o $@ $^ $(BUILD_LDFLAGS)

# Creates the dependecy rules
%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(BUILD_CCFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(BUILD_CCFLAGS) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)
