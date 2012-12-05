Cross-platform native Java launcher
===================================

Native executable launcher, starts JAR applications using relative (to launcher executable) paths
to JRE and JAR file. Paths are compiled into launcher. Works on Linux, Mac OSX and Windows.

*Note: this is not an executable wrapper, for JAR wrapping you may use 
[launch4j](http://launch4j.sourceforge.net/) (or others like it) instead*

Build prerequisites
-------------------

To compile launcher you will need:
 - bash-like shell
 - GNU make
 - C99 compiler

On windows you may use [msysGit bash](http://code.google.com/p/msysgit/) as shell and
[mingw-w64](http://mingw-w64.sourceforge.net/) compiler.

To build launcher with paths, specific for your application, you must prepare environment file, example:

    export JL_PLATFORM=macosx
    export JL_EXECUTABLE_NAME=myapp
    export JL_JAVA_RELATIVE_PATH=jre/bin/java
    export JL_JAR_RELATIVE_PATH=path/to/myapp.jar

Then set this variables into environment and run:

    . myapp.env
    make

Build on windows using custom icon
----------------------------------

To build executable with custom icon use these environment options:

    export JL_ICON_RC_FILE=path/to/myapp.rc

where `myapp.rc` is a resource file, see example [here](http://stackoverflow.com/a/708382/314015).
Then run (from msysGit bash):

    . my_windows.env
    make icon
    make

License information
-------------------

Code is provided under the terms of [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0)

Changelog
---------

**2012-12-05**

 * initial public version
