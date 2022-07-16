#include "pystring.h"

int main(){

    struct pystring mystring = pystring.create("some_string_with_substring\n");
    mystring.replace(&mystring, "substring", "mellon");
    mystring.capitalize(&mystring);
    mystring.strip(&mystring, "_");
    printf("%s", mystring.string);
    return 0;
}