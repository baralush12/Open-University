#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#include "function.h"
#include "global.h"
#include "error.h"


/* check if the line is over */
int end_line(char* ptr)
{
    return ptr == NULL || *ptr == '\0' || *ptr == '\n';
}
/*deletes space.*/
char* delete_space(char* ptr)
{
    if (ptr == NULL) return NULL;
    while (isspace(*ptr))
        ptr++;
    return ptr;
}
/*checks too see if ptr is ";" or end of line.*/
int jump(char* ptr)
{
    ptr = delete_space(ptr);
    return *ptr == ';' || *ptr == '\0' || *ptr == '\n';
}


/* Check if string is a number */
bool is_num(char *c)
{
    if(end_line(c)) 
        return FALSE;
    if (*c == '+' || *c == '-')
     {
        c++;
        if (!isdigit(*c++)) {
            return FALSE;
        }
     }
     
     /* check the whole token is digits */
     while(!end_line(c))
     {
        if(!isdigit(*c++)) return FALSE;
     }
     return TRUE;
     
}
/* Check if its a valid string */
bool is_str(char *s)
{
    if(s == NULL) return FALSE;
    
    if (*s == '"')
    {
        s++;
    }else
        return FALSE;
    
    while(*s && *s != '"')
    {
        s++;
    }
    if(*s != '"'){
        return FALSE; /* invalid string */
    }
    s++;
    if(*s !='\0'){
        return FALSE;
    }
    return TRUE;  
}
/*function that checks if the word is register or not*/
bool is_reg(char* word) {
    return strlen(word) == 2 && word[0] == 'r' && word[1] >= '0' && word[1] <= '7';
}
/* checks if the index value equal to one of array's value */
int check_val_in(char *c,const char *array[], int n)
{
    int i;
    for(i = 0; i<n; i++){
        if(strcmp(c,array[i]) == 0)
            return i;
    }
    return NONE;
}


/*This function extarcts the new slice until we reach space/tab/EOF* and put to new string and then we can analyze the first orerand*/
void transfer_line(char* new_line, char* curr_line)
{
    int i = 0;
    if (new_line == NULL || curr_line == NULL) return;
    while (i < MAX_LINE_LEN && !isspace(curr_line[i]) && curr_line[i] != '\0') {
        new_line[i] = curr_line[i];
        i++;
    }
    /*for (i = 0; i < MAX_LINE_LEN && !isspace(curr_line[i]) && curr_line[i] != '\0'; i++) {
        new_line[i] = curr_line[i];
    }*/
    new_line[i] = '\0';
}
/*Checks if the string is syntactically correct as a label*/
bool is_label(char *word, int is_ext_or_ent) {
    bool digit_in = FALSE; /*we assume there is not digits in the string*/
    int i;
    if (word == NULL) return FALSE;

    if (strlen(word) > MAX_LABEL_LEN) {
        if (is_ext_or_ent) {
            error = LONG_LABEL_ERR;
        }
        return FALSE;
    }
    if (is_ext_or_ent && word[strlen(word) - 1] != ':') {
        return FALSE;
    }
    if (!isalpha(*word)) {
        if (is_ext_or_ent) {
            error = FIRST_CHAR_NOT_ALPHANUMERIC;
        }
        return FALSE;
    }
    if (is_ext_or_ent)
    {
        word[strlen(word) - 1] = '\0';  
    }

    for (i = 0; i < strlen(word) - 1; i++) {
        if (isdigit(word[i])){
            digit_in = TRUE; /* if true we will not check if its opperation*/
        }else if(!isalpha(word[i])) {
            if (is_ext_or_ent) {
                error = ONLY_ALPHANUMERIC_OR_DIGIT;
            }
            return FALSE;
        }
    }
    
    if (!digit_in)
    {
        /*check if its command , label can`t be with command name*/
        if (check_val_in(word, commands, 16) != NONE) {
            if (is_ext_or_ent) {
                error = COMMAND_INVALID_AS_LABEL;
            }
            return FALSE;
        }
    }
    if (is_reg(word))
    {
        if (is_ext_or_ent) {
            error = REGISTER_INVALID_AS_LABEL;
        }
        return FALSE;
    }
    return TRUE;   
}
/*checks the string and returns the nubmber representing "directive type"*/
int checkin_dir(char* word)
{
    if (word == NULL || *word != '.') {
        return NONE;
    }
    return(check_val_in(word, directives, 5));
}

/*jump to next operand/slice of line*/
char *next_slice(char *line)
{
    if (line == NULL) {
        return NULL;
    }
    while (!isspace(*line) && !end_line(line)) { /*checks if the string is not a space or the end of the line*/
        line++;
    }
    line = delete_space(line);
    if (end_line(line)) {
        return NULL;
    }
    return line;
}
/*checks if memory allocation is possible and returns a pointer to allocated memory*/
void* is_valid_malloc(long size)
{
    void* ptr = malloc(size);
    if (!ptr)
    {
        printf("\nERROR!, not able to allocate memory\n");
        exit(1);
    }
    return ptr;
}
/*checks if memory allocation is possible and returns a pointer to allocated memory*/
void* is_valid_calloc(size_t nitems, size_t size) {
    void* ptr = (void*)calloc(nitems, size);
    if (!ptr)
    {
        printf("\nERROR!, not able to allocate memory\n");
        exit(1);
    }
    return ptr;
}
/*this function recieves a line of code and breaks it into seperate strings, ignoring spaces and irrelevant chars*/
char* get_next_slice(char* to, char* line)
{
    char* tmp = to;
    
    if (end_line(line))
    {
        to[0] = '\0';
        return NULL;
    }
    /*if there are spaces , ignore them*/
    if (isspace(*line))
    {
        line = delete_space(line);
    }
    /*if there is a comma copy the coma to a given parameter and return the line without the comma*/
    if (*line == ',')
    {
        strcpy(to, ",");
        return ++line;
    }

    while (!end_line(line) && *line != ',' && !isspace(*line))/*copy until reaching ',', EOF, whitespace */
    {
        *tmp = *line;
        tmp++;
        line++;
    }
    *tmp = '\0';
    return line;
}
/*get next string in line.*/
char* get_next_string(char* to, char* line)
{
    char tmp[MAX_LINE_LEN];
    line = get_next_slice(to, line);
    if (*to != '"') return line;
    while (!end_line(line) && to[strlen(to) - 1] != '"')
    {
        line = get_next_slice(tmp, line);
        if (line) strcat(to, tmp);
    }
    return line;
}
/*resets the values in link_label struct.*/
void reset_all()
{
    symbols_tab = NULL;
    entry_flag = FALSE;
    extern_flag = FALSE;
    there_error = FALSE;
}

/* translates input into requested base32.*/
char* int_to_base32(unsigned int num)
{
    const char base32_array[32] = { '!','@','#','$','%','^','&','*','<','>','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v' };
    int ptr = 0;
    char *test = (char*)malloc(10);
    char* temp = (char*)malloc(3);
 
    test = toBinary(num, 10);
    ptr = binToDec(test);

    if (ptr > 31)
    {
        temp[0] = base32_array[ptr / 32];
        temp[1] = base32_array[ptr % 32];        
        temp[2] = '\0';
    }
    else
    {
        temp[0] = base32_array[0];
        temp[1] = base32_array[ptr];
        temp[2] = '\0';
    }
    return temp;
}
/*convert unsigned int to int.*/
int convert(unsigned int n) {
    int dec = 0, i = 0, rem;
    while (n != 0) {
        rem = n % 10;
        n /= 10;
        dec += rem * pow(2, i);
        ++i;
    }
    return dec;
}
/*convert from int to binary.*/
char* toBinary(int n, int len)
{
    char* binary = (char*)malloc(sizeof(char) * len);
    int k = 0;
    unsigned int i;
    for (i = (1 << (len - 1)); i > 0; i = (i / 2)) {
        binary[k++] = (n & i) ? '1' : '0';
    }
    binary[k] = '\0';
    return binary;
}
/*convert from binary to decimal.*/
int binToDec(char* x)
{
    char* num = x;
    int decimal_value = 0;
    int base = 1;
    int i;

    int len = 10;
    for (i = len - 1; i >= 0; i--)
    {
        if (num[i] == '1')
            decimal_value += base;
        base = base * 2;
    }

    return decimal_value;
}

/* replaces a substring in a given string with another string, string = original line, sub = substring to replace, new_str = new substring*/

void swap(char* str1, char* str2)
{
    char* temp = (char*)malloc((strlen(str1) + 1) * sizeof(char));
    strcpy(temp, str1); 
    strcpy(str1, str2); 
    free(temp);
}

/* returns the next line number after last "endmacro"*/
int which_line_is_endmacro(FILE* input_file)
{
	int counter = 1;
	int return_line = 0;
	char* line_from_input;
	char* endmacro = "endmacro\0";
	char* temp = (char *) malloc(100);
	line_from_input = (char *) malloc(100); 
	while (fgets(line_from_input, MAX_LINE_LEN, input_file)) 
	{
		temp = NULL;
		counter++;
		temp = strstr(line_from_input, endmacro);
		if(temp != NULL)
		{
			return_line = counter;
		}
	}
    /*free(temp);*/
    return return_line;
}

/* returns the line number on first "macro"*/
int which_line_is_first_macro(FILE* input_file)
{
	int counter = 0;
	char* macro = "macro\0";
	char* temp = (char *) malloc(50);
	char* line_from_input = (char *) malloc(50); 
	
	while (fgets(line_from_input, MAX_LINE_LEN, input_file)) 
	{
		temp = NULL;
		counter++;
		temp = strstr(line_from_input, macro);
		if(temp != NULL)
		{
			return counter;
		}
	}
	counter = -1;
    /*free(temp);*/
	return counter;
}

/* returns second word in line*/
char* get_second_word(char* line)
{
    char* temp;
    char space = ' ';
    temp = (char *) malloc(20);
    temp = line;
    if((*temp) == space) /* to check for space in the first character.*/
	{
		temp++;
	}
    
    if (end_line(temp))
    {
        return NULL;
    }

    while ((*temp) != space && !end_line(temp))/*copy until reaching ',', EOF, whitespace */
    {
        temp++;
    }
    temp++;
	
    return temp;
}

/* returns first word in line*/
char* get_first_word(char* line)
{
    char* return_word;
    char* temp;
    char space = ' ';
    int i = 0;
    return_word = (char *) malloc(100);
    temp = (char *) malloc(100);
    temp = line;
    
    if((*temp) == space) /* to check for space in the first character.*/
	{
		temp++;
	}
    
    while ((*temp) != space && !end_line(temp))
    {

        *return_word = *temp;
        temp++;
        return_word++;
        i++;
    }
    
   *return_word = '\0';
    return_word = return_word - i;
    /*free(temp);*/
    return return_word;
}


char* cut(char* buffer)
{
    int i = 0;
    int j = 0;
    char* name = (char*)is_valid_calloc(strlen(buffer), sizeof(char));

    while (buffer[i] != '.')
        name[j++] = buffer[i++];
    return name;
}
