#include "pystring.h"

int main(){

    struct pystring mystring = pystring.create("so");
    mystring.capitalize(mystring.string);
    //bool title = mystring.istitle(mystring.string);
    //printf(title ? "true\n" : "false\n");
    printf("%s\n", mystring.string);
    return 0;
}