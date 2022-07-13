#include "pystring.h"

int main(){

    struct pystring mystring = pystring.create("ab\n");
    mystring.replace(&mystring, "a", "abcdab\n");
    //gggcdggg\n\0
    //mystring.capitalize(&mystring);
    //mystring.strip(&mystring,"abc");

    /*char* string;
    char* temp = "ab\0a";
    int len = strlen(temp);
    printf("%d\n",len);
    string = malloc(strlen(temp)*sizeof(char)+1);
    strcpy(string,temp);
    strcpy(string,"");
    string = realloc(string,strlen(string)*sizeof(char)+1);
    printf("%s",string);
    */
    return 0;
}