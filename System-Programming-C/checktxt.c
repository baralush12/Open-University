#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "error.h"
#include "global.h"
#include "function.h"


/* The function analyze the line from file and tell us what the lines means and what operation we need to do */
void analyze_line(char *line)
{
    /* initalize unknown values to directive and commands to reset before analyzing and avoid garbage */
    int dir_type = DIR_NONE;
    int op_type = OP_NONE;
    bool label;
    label_next head_label;
    char curr_slice[MAX_LINE_LEN];/*string that will store the current slice from the whole line that we will analyze*/

    label = FALSE; /* initalize label as false and after the analyzing if its will be label we will assign true */
    head_label = NULL;/*will be there the label we analyzed*/
    line = delete_space(line);


    if (end_line(line)) return;
    /*if the line start with dot or is not be alphanumeric, the syntax is invalid*/
    if (!isalpha(*line) && *line != '.') {
        error = INVALID_SYNTAX;
        return;
    }
    transfer_line(curr_slice, line);/*transfer the first operand to curr_slice for analyzing*/

    if (is_label(curr_slice, IS_EXT_OR_ENT))
    {
        label = TRUE;


        head_label = addlabel(&symbols_tab, curr_slice, 0, FALSE, FALSE);/*Add label to symbol table*/
        if (head_label == NULL) {
            return;
        }

        line = next_slice(line);/*read the next operand\slice of line*/


        if (end_line(line))
        {
            error = INVALID_LABEL;
            return;
        }
        transfer_line(curr_slice, line);


    }
    /*if we got any error from the islabel we will return and start over*/
    if (iserror()) {
        return;
    }

    /*checking if its directive type*/
    if ((dir_type = checkin_dir(curr_slice)) != NONE)
    {
        if (label)
        {
            if (dir_type == ENTRY || dir_type == EXTERN) {
                remove_label(&symbols_tab, head_label->lname); /*if the label is entry or extern, the assembler ignore*/
                label = FALSE;
                error = ENTRY_OR_EXTRN_IGNORE;
            }
            else {
                head_label->laddress = DC; 
            }
        }
        /*read the next slice\operand and check what type of directive and operands and encoding or if its invalid return faield*/
        line = next_slice(line);
        what_dir(dir_type, line);
    }

    /*checking if its command type*/
    else if ((op_type = check_val_in(curr_slice, commands, 16)) != NONE)
    {

        if (label)
        {
            head_label->label_op = TRUE; /*if command is a label, define as true in label_op*/
            head_label->laddress = IC; 
        }
        /*read the next slice\operand and check what type of command and operands and encoding or if its invalid return faield*/
        line = next_slice(line);
        what_op(op_type, line);
    }
    else {
        error = NO_OP_DIR_FOUND; /*if in line there is no command or directive is false*/
    }    
}


