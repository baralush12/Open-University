#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#include "error.h"
#include "global.h"
#include "function.h"

/*Analzying the directive and check the validity of parameters, and will encode the to DC*/
int what_dir(int dir, char* line)
{
    if (line == NULL || end_line(line))
    {
        error = PARAM_DIR_ERR;
        return FAILED;
    }

    switch (dir)
    {
    case DATA:
        return is_data_dir(line);

    case STRING:
        return is_string_dir(line);

    case STRUCT:
        return is_struct_dir(line);

    case ENTRY:
        if (!end_line(next_slice(line)))
        {
            error = DIR_ERR_INPUT_PARAMS;
            return FAILED;
        }
        break;

    case EXTERN:
        return is_extrn_dir(line);
    }
    return SUCCEED;
}

/*Analzying the command and check the validity of parameters, and will encode the first word of command and extra codes if needs*/
int what_op(int op, char* line)
{
    bool is_first_op = FALSE, is_second_op = FALSE; /* assume we have no parameters, and check what we get and if its valid to command requirement */
    int first_address, second_address; /* type of address */
    char first_op[MAX_LABEL_LEN], second_op[MAX_LABEL_LEN]; /* operands name */
    
    /* parse 2 operands */
    line = get_next_slice(first_op, line);
    if (!end_line(first_op)) /* if first isn`t empty continue */
    {
        is_first_op = TRUE; /* There is a valid first operand */
      
        line = get_next_slice(second_op, line); /*check if there is sceond operand*/
        if (!end_line(second_op)) /* only if the second operand not empty */
        {
            if (second_op[0] != ',') /* if there is no comma return error, because comma must be berween two operands*/
            {
                error = INVALID_SYNTAX_OPP;
                return FAILED;
            }

            else /*if there is comma, parse the next slice*/
            {
                line = get_next_slice(second_op, line);
                if (end_line(second_op)) /* if the second slice is invalid return error */
                {
                    error = INVALID_SYNTAX_OPP;
                    return FAILED;
                }
                is_second_op = TRUE; /* There is a valid second operand */
            }
        }      
    }
    line = delete_space(line);
    if (!end_line(line)) /* if there is more text after the operands we analyzed , return error, command can be with max 2 opperands */
    {
        error = MAX_2_OPERANDS_OP;
        return FAILED;
    }
    if (is_first_op) /*check if there is first operand, if yes analyze the address and assign to first_address*/
        first_address = what_meth(first_op, is_first_pass);
    if (is_second_op)/*check if there is second operand, if yes analyze the address and assign to first_address*/
        second_address = what_meth(second_op, is_first_pass);
    if (!iserror())
    {
        if (valid_opp(op, is_first_op, is_second_op)) /* check if the number operands we get is valid */
        {
            if (valid_add_meth(op, first_address, second_address)) /* check if address adjust to commands requirements */
            {
                /* increase IC by the first word number, and encode the word */
                /*build the first word (array bits of the commands) and insert to instruction[IC++] tab*/
                instruction_encode(first_word(op, is_first_op, is_second_op, first_address, second_address));
                if (is_first_op || is_second_op) {
                  add_extra_words(first_op, second_op, is_first_op, is_second_op, first_address, second_address);
                }
            }
            /*if the addresses doesnt adjust to command requirements*/
            else
            {
                error = INVALID_NUM_OPERANDS_ADDRESS;
                return FAILED;
            }
        }
        /*if the numbers of the operands doesnt fit to command requirements*/
        else
        {
            error = INVALID_NUM_OPERANDS_OP;
            return FAILED;
        }
    }

    return SUCCEED;
}

/*check the extra words and encoding to ic*/
int add_extra_words(char *first_op,char *second_op,bool has_source ,bool has_destination ,int first_meth,int second_meth) {
    if (has_source && has_destination && first_meth == REG_ADS && second_meth == REG_ADS)
    {
        instruction_encode(add_reg_word(first_op, FALSE ) | add_reg_word(second_op, TRUE));
    }
    else {
        if (has_source) {
            add_extra_word(first_meth, FALSE, first_op);
        }
        if (has_destination) {
            add_extra_word(second_meth, TRUE, second_op);
        }
    }
    return iserror();
}
/*add register word*/
unsigned int add_reg_word(char* word, bool destination)
{
    unsigned int temp = (unsigned int) atoi(word + 1);/*Assign Register number to temp*/
    /*if its source put it to right location(4,5) and if its destination put it in the right location(2,3) */
    if (!destination) {
        temp <<= 4;
    }
    temp = are_put(temp, ABSOLUTE);
    return temp;
}
void add_extra_word(int type_meth, bool destination, char *word) {

    unsigned int temp = 0;
    /*char* ptr;
    char parse[MAX_LINE_LEN];*/

    switch(type_meth) {
        case IMMEDIATE_ADS:
            temp = (unsigned int)atoi(word + 1);
            temp = are_put(temp, ABSOLUTE);
            instruction_encode(temp);
            break;
        case DIRECT_ADS:
            IC++;
            break;
        case ACCESS_ADS:
            IC++;
            temp = (unsigned int)atoi(word + 3);
            temp = are_put(temp, ABSOLUTE);
            instruction_encode(temp);
            break;
        case REG_ADS:
            temp = add_reg_word(word, destination);
            instruction_encode(temp);
    }
}
/*what kind of addressing method and if there is no address method return -1*/
int what_meth(char* op, bool is_first_pass)
{ 
    char* str; /*if its struct its will keep the part after '.'*/

    if (end_line(op)) return NONE;

    /*if its immediate address*/
    if (*op == '#') {
        op++;
        if (is_num(op))
            return IMMEDIATE_ADS;
    }

    /*if its register address*/
    else if (is_reg(op))
        return REG_ADS;
    
    /*if its direct address*/
    else if ((!is_first_pass || is_first_pass) && is_label(op, NONE_EXT_OR_ENT)) /* make sure is not a label */
        return DIRECT_ADS;

    /*if its struct address*/
    else if (is_label(strtok(op, "."), NONE_EXT_OR_ENT)) { /* split the text where have '.' */
        str = strtok(NULL, ""); /* assign to str the rest of the string */
        if (strlen(str) == 1 && (is_first_pass) && (*str == '1' || *str == '2')) {
            op = str;
            return ACCESS_ADS;
        }
        else if (strlen(str) == 1 && (*str == '1' || *str == '2')) {
            return ACCESS_ADS;
        }
    }
    error = NO_ADDRESS_METH;
    return NONE;
}


/* check if the command is valid based on the number of operands we get*/
bool valid_opp(int op, bool first_op, bool second_op)
{
    switch (op)
    {
     /*can accept only 2 operands*/
    case MOV:
    case CMP:
    case ADD:
    case SUB:
    case LEA:
        return first_op && second_op;

     /*can accept only 1 operand*/
    case NOT:
    case CLR:
    case INC:
    case DEC:
    case JMP:
    case BNE:
    case GET:
    case PRN:
    case JSR:
        return first_op && !second_op;

    /*can accept only 0 operand*/
    case RTS:
    case RTL:
        return !first_op && !second_op;
    }
    return FALSE;
}

/* check if address adjust to commands requirements*/
bool valid_add_meth(int op, int first_op, int second_op)
{
    switch (op)
    {
    /*first operand must be immediate\direct\access\register address method, and the second direct\access\register address method*/
    case MOV:
    case ADD:
    case SUB:
        return (first_op == IMMEDIATE_ADS ||
                first_op == DIRECT_ADS ||
                first_op == ACCESS_ADS ||
                first_op == REG_ADS)
                &&
                (second_op == DIRECT_ADS ||
                 second_op == ACCESS_ADS ||
                 second_op == REG_ADS);
    /*first operand must be immediate\direct\access\register address method, and the second immediate\direct\access\register address method*/
    case CMP:
        return (first_op == IMMEDIATE_ADS ||
            first_op == DIRECT_ADS ||
            first_op == ACCESS_ADS ||
            first_op == REG_ADS)
            &&
            (second_op == IMMEDIATE_ADS || 
                second_op == DIRECT_ADS ||
                second_op == ACCESS_ADS ||
                second_op == REG_ADS);
    /*first operand must be direct\access address method, and the second direct\access\register address method*/
    case LEA:
        return (first_op == DIRECT_ADS ||
                first_op == ACCESS_ADS)
                &&
                (second_op == DIRECT_ADS ||
                 second_op == ACCESS_ADS ||
                 second_op == REG_ADS);
    /*can get only one operand, and is has to be direct\access\register address method*/
    case NOT:
    case CLR:
    case INC:
    case DEC:
    case JMP:
    case BNE:
    case GET:
    case JSR:
        return first_op == DIRECT_ADS ||
               first_op == ACCESS_ADS ||
               first_op == REG_ADS;
    case PRN:
        return first_op == IMMEDIATE_ADS || 
               first_op == DIRECT_ADS ||
               first_op == ACCESS_ADS ||
               first_op == REG_ADS;
    /*will not get and address methods*/
    case RTS:
    case RTL:
        return TRUE;
    }

    return FALSE;
}

/*encode the first word*/
unsigned int first_word(int opcode, int first_w, int second_w, int first_address, int second_address)
{
    unsigned int word = 0;
    
    word = opcode;
    /*clear place for the first addresing source operand*/
    word <<= 2;
    /* put first operand if have two */
    if (first_w && second_w)
        word |= first_address;

    /*clear place for the second addresing destination operand*/
    word <<= 2;

    /* put second operand if have two */
    if (first_w && second_w)
        word |= second_address;
  
    /*if only one operand define the first address ass desination operand*/
    else if (first_w)
        word |= first_address;
    /*the first word of command have 00(absolue) at the A\R\E section*/
    word = are_put(word, ABSOLUTE);
    return word;
}

/*Assign the A\R\E bits to bits array*/
unsigned int are_put(unsigned int line, int type)
{
    return (line << 2) | type;
}

/*put word to instruction memory*/
void instruction_encode(unsigned int val)
{
    instructions[IC++] = val;
}

/*put data word to data memory*/
void num_data_encode(int val) {
    data[DC++] = (unsigned int)val;

}
/*encode data into memory*/
void str_data_encode(char* val)
{
    while (!end_line(val))
    {
        data[DC++] = (unsigned int)*val;
        val++;
    }
    data[DC++] = '\0';
}

/* analyze line of a data directive and encode to memory, check if its valid data directive - NEED TO FIX*/
int is_data_dir(char* line)
{
    bool has_num;
    bool has_comma;
    char word[MAX_LABEL_LEN];
    /*
    intialize first false on number and comma, we assume first there is no number and comma,
    if has_num = true its meant here is number so the next slice have to be comma if no return error.
    if the has_comma=true its ment here is cooma so the next slice have to be number if no return error.
    */
    has_num = FALSE;
    has_comma = FALSE;

    while (!end_line(line))
    {
        line = get_next_slice(word, line); /*assign to word the current slice*/
        if (strlen(word) > 0)
        {
            /*if has_num = false, have to come number to get valid directive data*/
            if (!has_num) {
                if (!is_num(word)) {  /*there is no number*/
                    error = SHOULD_BE_NUM;
                    return FAILED;
                }
                else {
                    /*if its valid number we encoding to data and assign false to comma because the next operand can be comma*/
                    has_num = TRUE;
                    has_comma = FALSE;
                    num_data_encode(atoi(word));
                }
            }

            else if (*word != ',') 
            {
                /*if there is no comma after number will print error*/
                error = SHOULD_BE_NUM;
                return FAILED;
            }
            /*should be only one comma*/
            else
            {
                /*if we get another comma we send error, we expecting to number*/
                if (has_comma) {
                    error = INVALID_COMMA_IN_DATA;
                    return FAILED;
                }
                /*we got only one comma so we assign has_comma = true and define has_num=false because the next should be number*/
                else {
                    has_comma = TRUE;
                    has_num = FALSE;
                }
            }

        }
    }
    /*the line has to end with number, if has_comma true is meant the last slice was comma and its an error*/
    if (has_comma == TRUE)
    {
        error = INVALID_COMMA_IN_DATA;
        return FAILED;
    }
    return SUCCEED;
}

/* analyze line of a .string directive and encode to memory, check if its valid string directive */
/*string directive accept only one parameter*/
int is_string_dir(char* line)
{
    char word[MAX_LINE_LEN];

    line = get_next_string(word, line);
    if (!end_line(word) && is_str(word)) {
        line = delete_space(line);
        /*if we got only one parameter encoding the string without the ""*/
        if (end_line(line))
        {
            word[strlen(word) - 1] = '\0';
            str_data_encode(word + 1);
        }
        /*if we got more than one parameter is an error , max one parameter for string directive*/
        else
        {
            error = ONLY_ONE_OPERAND_STRING;
            return FAILED;
        }

    }
    /*if the string is invalid  parameter*/
    else
    {
        error = INVALID_OPERAND_STRING;
        return FAILED;
    }

    return SUCCEED;
}

/* analyze line of a .struct directive and encode to memory, check if its valid struct directive */
int is_struct_dir(char* line)
{
    char word[MAX_LINE_LEN];
    line = get_next_slice(word, line);

    /*first parameter has to be number*/
    if (!end_line(word) && is_num(word))
    {
        /*encoding the first parameter*/
        num_data_encode(atoi(word));
        /*get the next parameter*/
        line = get_next_slice(word, line);

        /*next parameter has to ve comma, by struct directive requirements*/
        if (!end_line(word) && *word == ',') {
            /*get the next parameter*/
            line = get_next_string(word, line);
            /*the next parameter has to be string*/
            if (!end_line(word)) { 
                if (is_str(word)) {
                    /* encoding the second parameter without the "" */
                    word[strlen(word) - 1] = '\0';
                    str_data_encode(word + 1);
                }
                /*the second parameter is not string, return error*/
                else {
                    error = INVALID_STRING;
                    return FAILED;
                }
            }
            /*if we dont get second parameter return error*/
            else 
            {
                error = SHOULD_BE_STRING;
                return FAILED;
            }
        }
        /*if we dont get comma return error*/
        else
        {
            error = SHOULD_BE_COMMA;
            return FAILED;
        }
    }
    /*if the first parameters is not number return error*/
    else
    {
        error = FIRST_PARAM_MUST_BE_NUM;
        return FAILED;
    }
    /*we can accept only two parameters, return error if there is more*/
    if (!end_line(get_next_slice(word, line)))
    {
        error = MAX_TWO_OPERANDS;
        return FAILED;
    }
    return SUCCEED;
}


/* analyze line of a .extern directive and encode to memory, check if its valid extern directive */

int is_extrn_dir(char* line)
{
    char word[MAX_LABEL_LEN];

    transfer_line(word, line);
    if (end_line(word))
    {
        error = SHOULD_BE_LABEL_AFTER;
        return FAILED;
    }
    /*check if the word + ":" is valid label, if no return error*/
    if (!is_label(word, NONE_EXT_OR_ENT))
    {
        error = INVALID_LABEL_AFTER_EXT;
        return FAILED;
    }
    line = next_slice(line);
    if (!end_line(line))
    {
        error = ONLY_ONE_OPERAND_EXTRN;
        return FAILED;
    }

    if (addlabel(&symbols_tab, word, 0, TRUE) == NULL) {
        return FAILED;
    }
    /*if was an error in if we got error*/
    return iserror();
}

