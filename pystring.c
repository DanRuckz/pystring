#include "pystring.h"

static void replace(Pystring *this, char* replace_this, char* replace_with){
    enum state{init, change, end};
    const int MAX_STRING = 2048;
    bool sequence = false;
    int sequence_start;
    enum state sequence_location[MAX_STRING];
    enum state sequence_temp[MAX_STRING];
    unsigned int size_delta, changed_delta, numberof_sequences=0, current_size, new_size;
    if(strlen(replace_with) == 0){
        for(int i=0;i<strlen(replace_this);i++){
            removeElement(this->string, replace_this[i]);
        }
        return;
    }

    //initialize sequence location array
    memset(sequence_location, 0, sizeof(enum state) * MAX_STRING);
    //memset(sequence_temp, 0, sizeof(enum state) * MAX_STRING);
    for (int i=0;i<strlen(this->string);i++){
        if(this->string[i] == replace_this[0]){
            sequence = true;
            sequence_start = i;
        }

        for(int j=0;j<strlen(replace_this);j++){
            if(this->string[i+j] != replace_this[j]){
                sequence = false;
                sequence_start = -1;
                break;
            }
        }

        if(sequence){
            sequence_location[i] = change;
            sequence = false;
            numberof_sequences+=1;
        }
        if(i == strlen(this->string)-1){
            sequence_location[i+1] = end;
        }
    }
    unsigned int jump = strlen(replace_this);
    unsigned int jump_counter =0;
    unsigned int i=0,j=0,l=0,n=0;
    size_delta = ((strlen(replace_with)+1) - (strlen(replace_this)+1))* numberof_sequences;
    changed_delta = ((strlen(replace_with)+1) - (strlen(replace_this)+1));
    current_size = strlen(this->string)+1 *sizeof(char);
    new_size = current_size + size_delta;
    memcpy(sequence_temp, sequence_location, MAX_STRING);
    while(true){
        if(sequence_temp[i] == change){
            for(int n=0;n<strlen(replace_with);n++){
                sequence_location[j] = change;
                j+=1;
            }
            i+=jump;
        }
        if(sequence_temp[i]==end){
            sequence_location[j] = end;
            i+=1;
            break;
        }
        if(sequence_temp[i]==init){
            sequence_location[j] =init;
            j+=1;
            i+=1;
        }
    }
    
    i=0,j=0,l=0,n=0;


    char* string_temp = malloc(new_size*sizeof(char));
    while(true){
        if(sequence_location[i] == init){
            string_temp[j] = this->string[l];
            j+=1;
            l+=1;
            i+=1;
        }
        else if(sequence_location[i] == change){
            string_temp[j] = replace_with[n];
            j+=1;
            i+=1;
            n+=1;
            if(n == strlen(replace_with)){
                l+=jump;
                n=0;
            }
        }
        else if(sequence_location[i] == end){
            string_temp[j] = '\0';
            break;
        }
    }
    
    i=0;j=0;
    this->string = realloc(this->string,new_size*sizeof(char));
    memcpy(this->string,string_temp,new_size);
    free(string_temp);
}



static void strip(Pystring *this,char* strip_operand){
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

static void capitalize(char* string){
    char upper;
    char* temp;
    if (string[0] > 0x60 && string[0] < 0x7b) {
        string[0] = string[0] - 0x20;
    }
}

static void casefold(char* string){
    for(int i = 0;i<strlen(string);i++){
        if(string[i] > 0x40 && string[i] < 0x5B){
            string[i] = string[i] + 0x20;
        }
    }
}

static bool isalnum(char* string){
    for(int i=0;i<strlen(string);i++){
        if((string[i] >0x2F && string[i] < 0x3A) || (string[i] >0x40 && string[i] < 0x5B) || (string[i] > 0x60 && string[i] < 0x7B)){
        }
        else{return false;}
    }
    return true;
}

static bool isalpha(char* string){
    for(int i=0;i<strlen(string);i++){
        if((string[i] >0x40 && string[i] < 0x5B) || (string[i] > 0x60 && string[i] < 0x7B)){
        }
        else{return false;}
    }
    return true;
}

static bool isascii(char* string){
    for (int i=0;i<strlen(string);i++){
        if(string[i] > 0x7F && string[i] < 0x0){
            return false;
        }
    }
    return true;
}

static bool islower(char* string){
    for(int i=0;i<strlen(string);i++){
        if(string[i] > 0x40 && string[i] < 0x5B){
            return false;
        }
    }
    return true;
}

static bool isdecimal(char* string){
    for(int i=0;i<strlen(string);i++){
        if(string[i] <- 0x2F || string[i] >= 0x3A){
            return false;
        }
    }
    return true;
}

static bool isidentifier(char* string){
    if(string[0] > 0x2F && string[0] <0x3A){
        return false;
    }
    for(int i=0;i<strlen(string);i++){
        if((string[i] >0x2F && string[i] < 0x3A) || (string[i] >0x40 && string[i] < 0x5B) || (string[i] > 0x60 && string[i] < 0x7B)
        || string[i] == 0x5F){
        }
        else{return false;}
    }
    return true;
}
static bool isspace(char* string){
    if(strlen(string) == 0){
        return false;
    }
    for(int i=0;i<strlen(string);i++){
        if(string[i] != 0x20){
            return false;
        }
    }
    return true;
}

static bool istitle(char* string){
    /*
    to pass:
    first letter has to be either uppercase or number/sign
    if a letter was an uppercase, the next one has to be a number or a sign or a lowercase (not upper)
    if a letter was lowercase the next has to be another lowercase or a number or a sign (not upper)
    if a letter was a number or a sign(not alpha) the next one has to be a number or an uppercase (not lower)
    */

    if(string[0] > 0x60 && string[0] < 0x7B){
        return false;
    }

    for(int i=1;i<strlen(string);i++){
        char* current = string[i];
        char* previous = string[i-1];

        if(isupper(string) && isupper(current)){
            printf("%d\n", i);
            return false;
        }
        if(islower(previous) && isupper(current)){
            printf("%d\n", i);
            return false;
        }
        if(!isalpha(previous) && islower(current)){
            printf("%d\n", i);
            return false;
        }
    }
    return true;
}

static bool isupper(char* string){
    for(int i=0;i<strlen(string);i++){
        if(string[i] > 0x60 && string[i] < 0x7B){
            return false;
        }
    }
    return true;
}

static Pystring create(char* string){
    if((strlen(string) >2048)){
        printf("the length is: %ld and it's too long\n", strlen(string));
        exit(0);
    }
    char* stralloc;
    stralloc = malloc(strlen(string)*sizeof(char)+1);
    strcpy(stralloc,string);
    return (Pystring){.string=stralloc, .capitalize=&capitalize, .strip=&strip, .replace=&replace, .casefold=&casefold, .isalnum=&isalnum,
    .isalpha=&isalpha, .isascii=&isascii, .islower=&islower, .isdecimal=&isdecimal, .isidentifier=&isidentifier, .isspace=&isspace, .istitle=&istitle,
    .isupper=&isupper};
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
                string = realloc(string, strlen(string)*sizeof(char) +1);
            }
            else{string[i] = string[j];
            }

        }
        i++;j++;
    }    
}