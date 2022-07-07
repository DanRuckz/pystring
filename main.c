#include "pystring.h"

int main(){

    struct pystring mystring = pystring.create("abc\n");
    //mystring.strip(&mystring, "abcdef\n");
    //mystring.capitalize(&mystring);
    removeElement(mystring.string, 'a');
    removeElement(mystring.string, 'b');
    removeElement(mystring.string, 'c');
    printf("%s", mystring.string);
    return 0;
}