#include "pystring.h"

static void strip(struct pystring *this,char* strip_operand){
    int i=0;
    int j=0;
    while(strip_operand[i] != '\0'){
        while(this->string[j] != '\0'){
            if(strip_operand[i] == this->string[j]){
                removeElement(this->string,strip_operand[i]);
                j-=1;
                }
            j+=1;
        }
        i+=1;
        j=0;
    }
}

static void capitalize(struct pystring *this){
    char upper;
    char* temp;
    if (this->string[0] > 0x60 && this->string[0] < 0x7b) {
        this->string[0] = this->string[0] - 0x20;
    }
}

static struct pystring create(char* string){
    if((strlen(string) >2048)){
        printf("the length is: %ld and it's too long\n", strlen(string));
        exit(0);
    }
    char* stralloc;
    stralloc = malloc(strlen(string)*sizeof(char)+1);
    strcpy(stralloc,string);
    return (struct pystring){.string=stralloc, .capitalize=&capitalize, .strip=&strip};
}
const struct pystringClass pystring={.create=&create};

void removeElement(char* string, char to_remove){
    unsigned int i=0;
    unsigned int j=i+1;
    bool found = false;
    while(string[i] != '\0' ){
        if (string[i] == to_remove){
            found = true;
        }
        if(found){
            if (string[j] == '\0'){
                string[i] = '\0';
                string = realloc(string, strlen(string)*sizeof(char));
            }
            else{string[i] = string[j];
            }

        }
        i++;j++;
    }    
}