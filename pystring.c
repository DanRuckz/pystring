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
            __private_removeElement(this->string, replace_this[i]);
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
                __private_removeElement(this->string,strip_operand[i]);
                j-=1;
                }
            j+=1;
        }
        i+=1;
        j=0;
    }
}

static void capitalize(Pystring *this){
    return __private_capitalize(this->string);
}

static void __private_capitalize(char* string){
    if (string[0] > 0x60 && string[0] < 0x7b) {
        string[0] = string[0] - 0x20;
    }
}


static void lower(Pystring *this){
    __private_lower(this->string);
}

static void __private_upper(char* string){
    for(int i =0;i<strlen(string);i++){
        if(string[i] > 0x60 && string[i] <0x7B){
            string[i] = string[i] - 0x20;
        }
    }
}

static void upper(Pystring *this){
    __private_upper(this->string);
}

static void __private_lower(char* string){
    for(int i = 0;i<strlen(string);i++){
        if(string[i] > 0x40 && string[i] < 0x5B){
            string[i] = string[i] + 0x20;
        }
    }
}

static bool isalnum(Pystring *this){
    for(int i=0;i<strlen(this->string);i++){
        if((this->string[i] >0x2F && this->string[i] < 0x3A) || (this->string[i] >0x40 && this->string[i] < 0x5B) || (this->string[i] > 0x60 && this->string[i] < 0x7B)){
        }
        else{return false;}
    }
    return true;
}


static bool isalpha(Pystring *this){
    return __private_isalpha(this->string);
}

static bool __private_isalpha(char* string){
    for(int i=0;i<strlen(string);i++){
        if((string[i] >0x40 && string[i] < 0x5B) || (string[i] > 0x60 && string[i] < 0x7B)){
        }
        else{return false;}
    }
    return true;
}

static bool isascii(Pystring *this){
    for (int i=0;i<strlen(this->string);i++){
        if(this->string[i] > 0x7F && this->string[i] < 0x0){
            return false;
        }
    }
    return true;
}


static bool islower(Pystring *this){
    return __private_islower(this->string);
}

static bool __private_islower(char* string){
    for(int i=0;i<strlen(string);i++){
        if(string[i] <= 0x60 || string[i] >= 0x7B){
            return false;
        }
    }
    return true;
}

static bool isupper(Pystring *this){
    return __private_isupper(this->string);
}

static bool __private_isupper(char* string){
        for(int i=0;i<strlen(string);i++){
        if(string[i] <= 0x40 || string[i] >= 0x5B){
            return false;
        }
    }
    return true;
}

static bool isdecimal(Pystring *this){
    for(int i=0;i<strlen(this->string);i++){
        if(this->string[i] <- 0x2F || this->string[i] >= 0x3A){
            return false;
        }
    }
    return true;
}

static bool isidentifier(Pystring *this){
    if(this->string[0] > 0x2F && this->string[0] <0x3A){
        return false;
    }
    for(int i=0;i<strlen(this->string);i++){
        if((this->string[i] >0x2F && this->string[i] < 0x3A) || (this->string[i] >0x40 && this->string[i] < 0x5B) || (this->string[i] > 0x60 && this->string[i] < 0x7B)
        || this->string[i] == 0x5F){
        }
        else{return false;}
    }
    return true;
}
static bool isspace(Pystring *this){
    if(strlen(this->string) == 0){
        return false;
    }
    for(int i=0;i<strlen(this->string);i++){
        if(this->string[i] != 0x20){
            return false;
        }
    }
    return true;
}

static bool istitle(Pystring *this){
    /*
    to pass:
    first letter has to be either uppercase or number/sign
    if a letter was an uppercase, the next one has to be a number or a sign or a lowercase (not upper)
    if a letter was lowercase the next has to be another lowercase or a number or a sign (not upper)
    if a letter was a number or a sign(not alpha) the next one has to be a number or an uppercase (not lower)
    */
    
    char* previous = malloc(2*sizeof(char));
    char* current = malloc(2*sizeof(char));
    previous[1] = '\0';
    current[1] = '\0';
    memcpy(current, this->string,1);
    //checking first letter separately
    if(__private_islower(current)){
        return false;
    }
    
    for(int i=1;i<strlen(this->string);i++){
        memcpy(previous, this->string+i-1,1);
        memcpy(current, this->string +i,1);
        if(__private_isupper(previous) && __private_isupper(current)){
            return false;
        }
        if(__private_islower(previous) && __private_isupper(current)){
            return false;
        }
        if(!__private_isalpha(previous) && __private_islower(current)){
            return false;
        }
    }
    free(previous);
    free(current);
    return true;
}

static void title(Pystring *this){
    /*
    If first letter is a lowercase then capitalize it
    if previous letter is a sign/number and the current letter is lower, capitalize (if prev not alpha and current is lower -> capitalize)
    if previous was uppercase or lowercase (alpha) and current is upper case, lower it (if prev alpha and current is upper -> lower it)
    */
    char* previous = malloc(2*sizeof(char));
    char* current = malloc(2*sizeof(char));
    previous[1] = '\0';
    current[1] = '\0';
    char ccurrent;
    memcpy(current, this->string,1);
    if(__private_islower(current)){
        __private_capitalize(this->string);
    }
    for(int i=1;i<strlen(this->string);i++){
        memcpy(previous,this->string + i-1, 1);
        memcpy(current,this->string + i, 1);
        if(!__private_isalpha(previous) && __private_islower(current)){
            __private_capitalize(current);
            //to avoid any undefined behaviour, we explicitly take the first letter from the "string".
            ccurrent = current[0];
            this->string[i] = ccurrent;
        }
        if(__private_isalpha(previous) && __private_isupper(current)){
            __private_lower(current);
            ccurrent = current[0];
            this->string[i] = ccurrent;
        }
    }
    free(previous);
    free(current);
    
}

static unsigned int find(Pystring *this, char* substr){
    return __private_find(this->string, substr);
}

static unsigned int __private_find(char* string, char* substr){
    bool sequence = false;
    int i=0;
    for (i=0;i<strlen(string);i++){
        if(string[i] == substr[0]){
            sequence = true;
        }
        if(sequence){
            for(int j=0;j<strlen(substr);j++){
                if(string[j+i] != substr[j]){
                    sequence = false;
                    break;
                }    
            }
            if(sequence){
                return i;
            }
        }    
    }
    return -1;
}
static unsigned int find_windex(Pystring *this, char* substr, unsigned int __start, unsigned int __end){
    return __private_find_windex(this->string,substr,__start,__end);
}

static unsigned int __private_find_windex(char *string, char* substr, unsigned int __start, unsigned int __end){
    bool sequence = false;
    int i=0;
    if(__start >= __end){
        return -1;
    }
    if(__end > strlen(substr)){
        __end = strlen(substr);
    }
    for (i=__start;i<strlen(string);i++){
        if(string[i] == substr[0]){
            sequence = true;
        }
        if(sequence){
            for(int j=0;j<strlen(substr);j++){
                if(string[j+i] != substr[j]){
                    sequence = false;
                    break;
                }    
            }
            if(sequence){
                return i;
            }
        }    
    }
    return -1;
}

static unsigned int count(Pystring *this, char* substr){
    unsigned int counter = 0;
    unsigned int index = -1;
    for(int i=0;i<strlen(this->string);i++){
        index = __private_find_windex(this->string,substr, i, strlen(this->string));
        if(index != -1){
            counter +=1;
            i = index;
            index = -1;
        }
    }
    return counter;
}

static bool startswith(Pystring *this, char* substr){
    int index = __private_find(this->string,substr);
    return (index == 0) ? true : false;
}

static bool startswith_windex(Pystring *this, char* substr, unsigned int __start, unsigned int __end){
    int index = __private_find_windex(this->string,substr,__start,__end);
    return (index == __start) ? true : false;
}

static void swapcase(Pystring *this){
    char* letter = malloc(2*sizeof(char));
    letter[1] = '\0';
    char to_insert;
    for(int i=0;i<strlen(this->string);i++){
        memcpy(letter, this->string + i, 1);
        if(__private_isupper(letter)){
            __private_lower(letter);
            to_insert = letter[0];
            this->string[i] = to_insert;
        }
        else{
            __private_upper(letter);
            to_insert = letter[0];
            this->string[i] = to_insert;
        }
    }
    free(letter);
}

static void zfill(Pystring *this, int maxto_fill){
    char temp[2048];
    unsigned int numof_zeros = maxto_fill - strlen(this->string);
    if(strlen(this->string) >= maxto_fill || maxto_fill <1){
        return;
        }
    memcpy(temp,this->string,strlen(this->string)+1);
    this->string = realloc(this->string, (strlen(this->string) + numof_zeros + 1)*sizeof(char));
    for(int i=0;i<strlen(this->string) + numof_zeros;i++){
        if(i<numof_zeros){
            this->string[i] = '0';
        }
        else{
            this->string[i] = temp[i-numof_zeros];
        }
    }
}

static void center(Pystring *this,unsigned int numof_max_chars, char padding){
    int numof_paddings = numof_max_chars - strlen(this->string);
    int lpaddings;
    int rpaddings;
    if(numof_paddings%2==0){
        lpaddings = numof_paddings/2;
        rpaddings = numof_paddings/2;
    }
    else{
        lpaddings = numof_paddings/2;
        rpaddings = numof_paddings/2 +1;
    }
    if(numof_max_chars <= strlen(this->string)){
        return;
    }
    char temp[2048];
    memcpy(temp,this->string,(strlen(this->string)+1)*sizeof(char));
    this->string = realloc(this->string, (strlen(this->string) + numof_max_chars +1)*sizeof(char));

    for(int i=0;i<numof_max_chars;i++){
        if(i<lpaddings){
            this->string[i] = padding;
            }
        else if(i<numof_max_chars-rpaddings){
            this->string[i] = temp[i-lpaddings];
        }
        else{
            this->string[i] = padding;
        }
    }
}

static void delete(Pystring *this){
    free(this->string);
}


static Pystring create(char* string){
    if((strlen(string) >2048)){
        printf("the length is: %ld and it's too long\n", strlen(string));
        exit(0);
    }
    char* stralloc;
    stralloc = malloc(strlen(string)*sizeof(char)+1);
    strcpy(stralloc,string);
    return (Pystring){.string=stralloc, .capitalize=&capitalize, .strip=&strip, .replace=&replace, .lower=&lower, .upper=&upper, .isalnum=&isalnum,
    .isalpha=&isalpha, .isascii=&isascii, .islower=&islower, .isdecimal=&isdecimal, .isidentifier=&isidentifier, .isspace=&isspace, .istitle=&istitle,
    .isupper=&isupper, .delete=&delete, .title=&title, .count=&count, .swapcase=&swapcase, .find=&find, .find_windex=&find_windex, .startswith=&startswith,
    .startswith_windex=&startswith_windex, .zfill=&zfill, .center=&center};
}
const struct pystringClass pystring={.create=&create};

static void __private_removeElement(char* string, char to_remove){
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

