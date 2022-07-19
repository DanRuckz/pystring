#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct pystring{
    char* string; //implement free function
    void (*capitalize)(char* string);
    void (*strip)(struct pystring *this, char* strip_operand);
    void (*replace)(struct pystring *this, char* replace_this, char* replace_with);
    void (*casefold)(char* string);
    bool (*isalnum)(char* string);
    bool (*isalpha)(char* string);
    bool (*isascii)(char* string);
    bool (*islower)(char* string);
    bool (*isdecimal)(char* string);
    bool (*isidentifier)(char* string);
    bool (*isspace)(char* string);
    bool (*istitle)(char* string);
    bool (*isupper)(char* string);
};
extern const struct pystringClass{
    struct pystring (*create)(char* string);
} pystring;
typedef struct pystring Pystring;
void removeElement(char* string, char to_remove);