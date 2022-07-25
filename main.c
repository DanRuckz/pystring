#include "pystring.h"

int main(){

    Pystring mystring = pystring.create("99 This Is @ Symbol.");
    //__private_removeElement("thestring", 'g');
    //mystring.strip(&mystring, "sub");
    bool title = mystring.istitle(&mystring);
    printf(title ? "true\n" : "false\n");
    //printf("%s\n", mystring.string);
    return 0;
}