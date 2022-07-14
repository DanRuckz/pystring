#include "pystring.h"

static void replace(struct pystring *this, char* replace_this, char* replace_with){
    enum state{init, change, letter, end};
    const int MAX_STRING = 2048;
    char string_temp[MAX_STRING];
    bool sequence = false;
    int sequence_start;
    enum state sequence_location[MAX_STRING];
    enum state sequence_temp[MAX_STRING];
    unsigned int size_delta, changed_delta, numberof_sequences =0, current_size, new_size;
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
    unsigned int i=0,j=0,l=0;
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
    i=0,j=0,l=0;
    /*while(true){
        if(sequence_location[i] == init){
            string_temp[j] = this->string[l];
            j+=1;
            l+=1;
        }
        else if(sequence_location[i] == change){
            for(int n=0;n<strlen(replace_with);n++){
                string_temp[j] = replace_with[n];
                j+=1;
            }
            l+=jump;
            i+=1;
        }
        else if(sequence_location[i] == end){
            string_temp[j] = '\0';
            break;
        }
    }
    */
i=0;j=0;

    for(int i =0;i<MAX_STRING;i++){
        printf("%d",sequence_location[i]);
    }

    /*for(int j=0;j<MAX_STRING;j++){
        if(sequence_location[j] != end){
            printf("%d", sequence_location[j]);
        }
        else{
            printf("%d", sequence_location[j]);
            puts("");
            break;
        }
    }*/
}

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
    return (struct pystring){.string=stralloc, .capitalize=&capitalize, .strip=&strip, .replace=&replace};
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


/*else if(j>=sequence_start && j<strlen(replace_with)){
                sequence_location[j] = empty;
            }
            else if(j>=sequence_start+strlen(replace_with) && j<=strlen(this->string)+letter_difference){
                sequence_location[j] = letter;
            }
        } 
                //for(int j=sequence_start;j<strlen(replace_with);j++){
                //    sequence_location[j] = empty;
                //}
            }

            else if(strlen(replace_this) > strlen(replace_with)){
                letter_difference = strlen(replace_this) - strlen(replace_with);
                //implement remove letter
                puts("remove");
            }
            else{
                letter_difference = 0;
                //no need to change the allocation, only the letters
                puts("equal");
            }*/