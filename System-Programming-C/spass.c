#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "error.h"
#include "global.h"
#include "function.h"


/* second pass operation */
void spass(FILE* file_desc, char* fname)
{
    char line[MAX_LINE_LEN];
    int line_index = 1;
    IC = 0;
    /* read until EOF */
    while (fgets(line, MAX_LINE_LEN, file_desc) != NULL)
    {
        error = SUCCEED;
        if (!jump(line))  /* skip the spaces, tab or ; */


            analyze_line_spass(line); /* check the line and extract line meaning, label, extern\entry,opp */
        if (iserror()) { /* if there is an error in the file stop and define there_error as true */
            there_error = TRUE;
            print_err(line_index); /* print the error */
        }
        line_index++;

    }

    if (!there_error) {
        fname = cut(fname);
        create_files(fname);
     
    }else {
    }
    free_all_labels(&symbols_tab);
    free_ext_labels(&ext_tab);
}

void analyze_line_spass(char* line) {
     int dir_type = DIR_NONE;
     int op_type = OP_NONE;
     char curr_slice[MAX_LINE_LEN]; /* store our curr line we analyzing*/

     line = delete_space(line);
     if (end_line(line)) return;
     
     transfer_line(curr_slice, line);/*make sure the label without spaces and valid*/
     

     if (is_label(curr_slice, IS_EXT_OR_ENT))
      {
        line = next_slice(line);/*start to read new slice in line*/
        transfer_line(curr_slice, line);
      }

     if ((dir_type = checkin_dir(curr_slice)) != NONE)
     {
         line = next_slice(line);
         if (dir_type == ENTRY) /*if the symbol exsit in the symbol table*/
         {
             transfer_line(curr_slice, line);
             entry_in(symbols_tab, curr_slice);
         }
     }
     else if ((op_type = check_val_in(curr_slice, commands, 16)) != NONE)
     {
         line = next_slice(line);
         analyze_command_words(op_type, line);
     }
}


void analyze_command_words(int op_type, char* word)
{
    bool has_source = FALSE, has_destination = FALSE; /* type of address */
    char first_op[MAX_LINE_LEN], second_op[MAX_LINE_LEN]; /* operands name */
    char* source_add = first_op, * destination_add = second_op; /*pointers to operand names*/
    int first_address = METHOD_UNKNOWN, second_address = METHOD_UNKNOWN;
    if (op_type >= MOV && op_type <= LEA)
    {
        has_source = TRUE;
        has_destination = TRUE;
    }
    else if (op_type >= NOT && op_type <= JSR) {
        has_source = FALSE;
        has_destination = TRUE;
    }
    else if (op_type >= RTS && op_type <= RTL) {
        has_source = FALSE;
        has_destination = FALSE;
    }
    if (has_source || has_destination) {
        word = get_next_slice(first_op, word);
        if (has_source && has_destination) {
            word = get_next_slice(second_op, word);
            get_next_slice(second_op, word);
        }
        else {
            destination_add = first_op;
            source_add = NULL;
            if (!(check_if_external(symbols_tab, destination_add)) && is_label(destination_add, NONE_EXT_OR_ENT)) {
                IC--;
            }
        }
    }
    if (has_source) {/*check if there is first operand, if yes analyze the address and assign to first_address*/
        first_address = what_meth(source_add, !is_first_pass);
    } 
        
    if (has_destination) {/*check if there is second operand, if yes analyze the address and assign to first_address*/
        second_address = what_meth(destination_add, !is_first_pass);
    }

    IC++; /*we already built the first word on the first pass*/
    if (has_source) {
        add_extra_word_spass(first_address, first_op);
    }
    if (has_destination) {
        add_extra_word_spass(second_address, destination_add);
        /*add_extra_word_spass(second_address, second_op);*/
    }
}

/*This function checks if given symbol is external or not*/
bool check_if_external(label_next hp, char* name)
{
    label_next ptr = check_label(hp, name);
    if (ptr != NULL)
        {
        return ptr->label_extern;
        }
    return FALSE;
}

/*Add label word to IC after analyzing*/
void add_extra_word_label(char* word)
{
    unsigned int temp;
    if (is_valid_label(symbols_tab, word)) /*if symbol is in symboltable then its RELOCATABLE, if not its EXTERNAL*/
    {
        temp = get_laddress(symbols_tab, word);
        if (check_if_external(symbols_tab, word)) {
            add_ext_label(&ext_tab, word, IC + MEMORY_INDEX);
            temp = are_put(temp, EXTERNAL);
        }
        else {
            
            temp = are_put(temp, RELOCATABLE);
        }
        instruction_encode(temp);
    }
    else {
        IC++;
    }
}

void add_extra_word_spass(int type_meth, char* word)
{
    char* ptr;
    switch (type_meth)
    {
    case IMMEDIATE_ADS:
        IC++;
        break;

    case DIRECT_ADS:
        add_extra_word_label(word);
        break;

    case ACCESS_ADS:
        ptr = strtok(word, ".");
        add_extra_word_label(ptr);
        IC++;
        break;

    case REG_ADS:
        IC++;
    }
}


