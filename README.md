logutils
========

Tools for manipulating logfiles.

So far:

- `stamp`: print an accurate timestamp in ISO8601 format
- `stamplines`: prefix each input line with an accurate timestamp in ISO8601 format 
- `tagalog`: convert log data into a stream of tagged JSON documents (tagging yet to be implemented)
- `logatag`: convert a stream of JSON documents into a stream of log data (python prototype)

Build
-----

You'll need [redo](https://github.com/apenwarr/redo) and a C compiler.

    $ redo

So far, compilation (and, indeed, compileability) has been tested only on Mac
OS X 10.8 and Ubuntu 12.04. Experiences on other platforms may vary.

Install
-------

    $ sudo PREFIX=/usr/local redo install
