====================
image feature sample
====================

Require
=======

- jubatus 0.5.x
- opencv


How to build
============

::

   $ ./waf configure --prefix=$JUBATUS_HOME
   $ ./waf build
   $ ./waf install


Run sample
==========

::

   $ jubaclassifier -f classifier_config.json &
   $ ./build/sample /path/to/jpg/file

