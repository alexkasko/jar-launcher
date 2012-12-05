# all variables may be set from environmment, use:
# . myapp.env
# make icon # windows only step
# make

# platform name
# allowed values are: 'linux', 'macosx' and 'windows'
JL_PLATFORM ?= linux

# compile settings
JL_CC ?= gcc
JL_COMPILER_OPTIONS ?= -g -O0 -Wall -std=gnu99

# result executable name
JL_EXECUTABLE_NAME ?= launcher

# paths are relative to executable file
JL_JAVA_RELATIVE_PATH ?= jre/bin/java
JL_JAR_RELATIVE_PATH ?= launcher.jar

# icon on windows
JL_ICON_RC_FILE ?= icon.rc
JL_ICON_RES_FILE ?= icon.res

all: compile

compile:
	$(JL_CC) $(JL_COMPILER_OPTIONS) \
		-DJL_JAVA_RELATIVE_PATH=\"$(JL_JAVA_RELATIVE_PATH)\" \
		-DJL_JAR_RELATIVE_PATH=\"$(JL_JAR_RELATIVE_PATH)\" \
		jl_common.c \
		jl_heap.c \
		jl_platform_$(JL_PLATFORM).c \
		jl_main.c \
		-o $(JL_EXECUTABLE_NAME)

clean:
	rm $(JL_EXECUTABLE_NAME)

vg: 
	valgrind --track-origins=yes \
		--leak-check=full \
		--leak-check=full \
		--show-reachable=yes \
		$(JL_EXECUTABLE_NAME)

run:
	./$(JL_EXECUTABLE_NAME)

# windows only
icon:	
	windres $(JL_ICON_RC_FILE) -O coff -o $(JL_ICON_RES_FILE)
