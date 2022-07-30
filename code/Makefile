# Compiler settings - Can be customized.
CC = g++
CC_INCLUDES = -I$(LIBRARY_CPP)
LDFLAGS = -L$(LIBRARY_CPP)

RM = rm

export LDFLAGS CC CC_INCLUDES RM

all: realease debug

realease: 
	@$(MAKE) -f realease.mk

debug: 
	@$(MAKE) -f debug.mk

.PHONY: clean
clean: clean_release clean_debug

.PHONY: clean_release
clean_release:
	@$(MAKE) -f realease.mk clean

.PHONY: clean_debug
clean_debug:
	@$(MAKE) -f debug.mk clean
