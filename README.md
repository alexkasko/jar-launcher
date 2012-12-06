Cross-platform native Java launcher
===================================

Native executable launcher, starts JAR applications using relative (to launcher executable) paths
to JRE and JAR file. Paths are compiled into launcher. Works on Linux, Mac OS X and Windows.

*Note: this is not an executable wrapper, for JAR wrapping you may use 
[launch4j](http://launch4j.sourceforge.net/) (or others like it) instead*

Build prerequisites
-------------------

To compile launcher you will need:
 - bash-like shell
 - GNU make
 - C99 compiler

On windows you may use [msysGit bash](http://code.google.com/p/msysgit/) as shell and
[mingw-w64](http://mingw-w64.sourceforge.net/) compiler with 
[patched version of make](http://sourceforge.net/projects/mingw-w64/files/External%20binary%20packages%20%28Win64%20hosted%29/make/)
([description](http://sourceforge.net/apps/trac/mingw-w64/wiki/Make)).

To build launcher with paths, specific for your application, you must prepare environment file, example:

    export JL_PLATFORM=macosx
    export JL_EXECUTABLE_NAME=myapp
    export JL_JAVA_RELATIVE_PATH=jre/bin/java
    export JL_JAR_RELATIVE_PATH=path/to/myapp.jar

Then run:

    . myapp.env
    make

Build on windows using custom icon and version info
---------------------------------------------------

Icon file path, version information (author, company etc) and manifest file
are specified in `resources/resources.rc` file. To use custom parameters copy
`resources.rc` to `myapp.rc`, edit it approproately and set this variable in env file:

    export JL_RC_FILE=path/to/myapp.rc

License information
-------------------

Code is provided under the terms of [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0)

Changelog
---------

**2012-12-05**

 * fix "This program might not have installed correctly" message on windows7

**2012-12-05**

 * initial public version
