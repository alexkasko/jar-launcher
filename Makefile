# all variables may be set from environmment, use:
# . myapp.env
# make icon # windows only step
# make

# platform name
# allowed values are: 'linux', 'macosx' and 'windows'
JL_PLATFORM ?= linux

# compile settings
JL_CC ?= gcc
JL_COMPILER_OPTIONS ?= -O0

# result executable name
JL_EXECUTABLE_NAME ?= launcher

# paths are relative to executable file
JL_JAVA_RELATIVE_PATH ?= jre/bin/java
JL_JAR_RELATIVE_PATH ?= launcher.jar

# resources on windows
JL_RC_FILE ?= resources/resources.rc
JL_RES_FILE ?= resources.res
# resources switch
ifeq ($(JL_PLATFORM),windows)	
	JL_RESOURCES_TARGET = resfile
endif

all: compile

compile: $(JL_RESOURCES_TARGET)
	$(JL_CC) -g -Wall -std=gnu99 $(JL_COMPILER_OPTIONS) \
		-DJL_JAVA_RELATIVE_PATH=\"$(JL_JAVA_RELATIVE_PATH)\" \
		-DJL_JAR_RELATIVE_PATH=\"$(JL_JAR_RELATIVE_PATH)\" \
		jl_common.c \
		jl_heap.c \
		jl_platform_$(JL_PLATFORM).c \
		jl_main.c \
		-o $(JL_EXECUTABLE_NAME)

clean:
	rm $(JL_EXECUTABLE_NAME) 2>/dev/null || true
ifeq ($(JL_PLATFORM),windows)	
	rm $(JL_RES_FILE) 2>/dev/null || true
endif

vg: 
	valgrind --track-origins=yes \
		--leak-check=full \
		--leak-check=full \
		--show-reachable=yes \
		$(JL_EXECUTABLE_NAME)

run:
	./$(JL_EXECUTABLE_NAME)

# windows only
resfile:	
	windres $(JL_RC_FILE) --output-format coff --output $(JL_RES_FILE)
