# all variables may be set from environmment, use:
# . env_windows.sh
# make -e icon # windows only step
# make -e

# compile settings
CC = gcc
JL_COMPILER_OPTIONS = -g -Wall -std=gnu99

# result executable name
JL_EXECUTABLE_NAME = launcher.exe

# paths are relative to executable file
JL_JAVA_RELATIVE_PATH = jre/bin/java
JL_JAR_RELATIVE_PATH = launcher.jar

# platform settings
# allowed values are: 'linux', 'macosx' and 'windows'
JL_PLATFORM = windows
JL_PLATFORM_COMPILER_OPTIONS= -mwindows $(JL_ICON_RES_FILE)

# icon on windows
JL_ICON_RC_FILE = icon.rc
JL_ICON_RES_FILE = icon.res

default: compile

compile:
	$(CC) $(JL_COMPILER_OPTIONS) \
		-DJL_JAVA_RELATIVE_PATH=\"$(JL_JAVA_RELATIVE_PATH)\" \
		-DJL_JAR_RELATIVE_PATH=\"$(JL_JAR_RELATIVE_PATH)\" \
		$(JL_PLATFORM_COMPILER_OPTIONS) \
		jl_common.c \
		jl_heap.c \
		jl_platform_$(JL_PLATFORM).c \
		jl_main.c \
		-o $(JL_EXECUTABLE_NAME)

clean:
	rm $(JL_EXECUTABLE_NAME)
	ifeq ($(JL_PLATFORM),windows)
		rm $(JL_ICON_RES_FILE)
	endif

vg: 
	valgrind --track-origins=yes \
		--leak-check=full \
		--leak-check=full \
		--show-reachable=yes \
		$(JL_EXECUTABLE_NAME)

run:
	$(JL_EXECUTABLE_NAME)

# windows only
icon:	
	windres $(JL_ICON_RC_FILE) -O coff -o $(JL_ICON_RES_FILE)
