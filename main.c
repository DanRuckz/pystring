#include "pystring.h"

int main(){

    Pystring mystring = pystring.create("hello");
    mystring.capitalize(&mystring);
    printf("%s\n", mystring.string);
    mystring.delete(&mystring);
    return 0;
}