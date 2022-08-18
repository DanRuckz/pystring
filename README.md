# pystring
An attepmt to implement a python like string functionallity in C
To use:
Add pystring.h and pystring.c into your code

to create a string with pystring:

#include "pystring.h"
Pystring mystring = pystring.create("hello");
to use functions:
mystring.<function>(&mystring,args...)
for example:
mystring.capitalize(&mystring); - this will capitalize the string
you can use any other function too.

When finished using the string you'd need to free the memory that it used.
to free the allocation:
mystring.delete(&mystring)

the main file serves as an example.
