#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

struct pystring{
    char* string; //implement free function
    void (*capitalize)(struct pystring *this);
    void (*strip)(struct pystring *this, char* strip_operand);
    void (*replace)(struct pystring *this, char* replace_this, char* replace_with);
    void (*lower)(struct pystring *this);
    void (*upper)(struct pystring *this);
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
    void (*center)(struct pystring *this, unsigned int numof_maxchars, char padding);
    unsigned int (*count)(struct pystring *this,char* substr);
    void (*swapcase)(struct pystring *this);
    unsigned int (*find)(struct pystring *this, char* substr);
    unsigned int (*find_windex)(struct pystring *this, char* substr, unsigned int __start, unsigned int __end);
    bool (*startswith)(struct pystring *this, char* substr);
    bool (*startswith_windex)(struct pystring* this, char* substr, unsigned int __start, unsigned int __end);
    void (*zfill)(struct pystring* this, int max_tofill);
};
extern const struct pystringClass{
    struct pystring (*create)(char* string)
}pystring;
typedef struct pystring Pystring;
static void __private_removeElement(char* string, char to_remove);
static bool __private_isupper(char* string);
static bool __private_islower(char* string);
static bool __private_isalpha(char* string);
static void __private_capitalize(char* string);
static void __private_lower(char* string);
static void __private_upper(char* string);
static unsigned int __private_find(char* string, char* substr);
static unsigned int __private_find_windex(char *string, char* substr, unsigned int __start, unsigned int __end);