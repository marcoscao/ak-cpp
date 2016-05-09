# ak-cpp

NOTE: under development beta project and documentation


1. Description
2. Features
3. Build
5. TODO

Appendix A: Running Tests 



## 1. Description

This is the suite of ak tools to process, query and manage media files such audio ones.
It is based on C++11/14

* ak_gen: Process source data

* ak_query: Performs queries to processed data

* ak_sync: Synchronizes data between different media devices


## 2. Features



## 3. Build

** Only tested in 'linux' based environments ( Apple OSX 'El Capitan' with ports usage and Windows 7 'Cygwin' )
** Tested with clang and gcc compilers with C++11/14 support
** It requires:
   - boost libraries
   - sqlite
   - lxml

The steps to make it work are:

1. Download / Clone the source code 
2. run from shell: "./build.sh && ./compile.sh"
3. Binary files will be generated under out/bin




## Appendix A. Running tests

1. Simply run: "out/bin/test_sources_option --log_level=test_suite"



