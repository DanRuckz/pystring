#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct pystring{
    char* string; //implement free function
    void (*capitalize)(struct pystring *this);
    void (*strip)(struct pystring *this, char* strip_operand);
    void (*replace)(struct pystring *this, char* replace_this, char* replace_with);
    void (*casefold)(struct pystring *this);
    bool (*isalnum)(struct pystring *this);
    bool (*isalpha)(struct pystring *this);
    bool (*isascii)(struct pystring *this);
    bool (*islower)(struct pystring *this);
    bool (*isdecimal)(struct pystring *this);
    bool (*isidentifier)(struct pystring *this);
    bool (*isspace)(struct pystring *this);
    bool (*istitle)(struct pystring *this);
    bool (*isupper)(struct pystring *this);
    void (*delete)(struct pystring *this);
    void (*title)(struct pystring *this);
};
extern const struct pystringClass{
    struct pystring (*create)(char* string)
} pystring;
typedef struct pystring Pystring;
static void __private_removeElement(char* string, char to_remove);
static bool __private_isupper(char* string);
static bool __private_islower(char* string);
static bool __private_isalpha(char* string);
