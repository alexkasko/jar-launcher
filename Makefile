
JL_JAVA_RELATIVE_PATH = jre/bin/java
JL_JAR_RELATIVE_PATH = install.jar

all: compile vg

compile:
	gcc -g -O0 -Wall -std=gnu99 -o install \
		-DJL_JAVA_RELATIVE_PATH=\"$(JL_JAVA_RELATIVE_PATH)\" \
		-DJL_JAR_RELATIVE_PATH=\"$(JL_JAR_RELATIVE_PATH)\" \
		jl_heap.c \
		install.c

clean:
	rm install

vg: 
	valgrind --track-origins=yes \
		--leak-check=full \
		--leak-check=full \
		--show-reachable=yes \
		install
