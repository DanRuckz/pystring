#include "pystring.h"

int main(){

    struct pystring mystring = pystring.create("sasaaaasasa");
    mystring.replace(&mystring, "a", "AAA");
    mystring.casefold(&mystring);
    printf("%s\n", mystring.string);
    return 0;
}