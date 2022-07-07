#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct pystring{
    char* string; //implement free function
    void (*capitalize)(struct pystring *this);
    void (*strip)(struct pystring *this, char* strip_operand);
};
extern const struct pystringClass{
    struct pystring (*create)(char* string);
} pystring;
void removeElement(char* string, char to_remove);