
JL_PLATFORM = windows
JL_JAVA_RELATIVE_PATH = jre/bin/java
JL_JAR_RELATIVE_PATH = install.jar

all: compile run

compile:
	gcc -g -O0 -Wall -std=gnu99 -o build/install.exe \
		-DJL_JAVA_RELATIVE_PATH=\"$(JL_JAVA_RELATIVE_PATH)\" \
		-DJL_JAR_RELATIVE_PATH=\"$(JL_JAR_RELATIVE_PATH)\" \
		jl_common.c \
		jl_heap.c \
		jl_platform_$(JL_PLATFORM).c \
		install.c

clean:
	rm -rf build
	mkdir build

vg: 
	valgrind --track-origins=yes \
		--leak-check=full \
		--leak-check=full \
		--show-reachable=yes \
		build/install

run:
	build/install.exe
