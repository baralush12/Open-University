#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#include "global.h"
#include "error.h"
#include "function.h"

/*Return TRUE if has an error, FALSE if not*/
int iserror()
{
    return error != SUCCEED;
}

/*Print the error details*/

void print_err(int index)
{
    fprintf(stderr, "ERROR (line %d): ", index);

    switch (error)
    {
    case INVALID_SYNTAX:
        fprintf(stderr, "First char who`s not null has to be letter or '.'\n");

        break;

    case EXIST_LABEL_ERR:
        fprintf(stderr, "Invalid label, the label allready exists.\n");

        break;

    case NONE_COLLON_LABEL:
        fprintf(stderr, "Invalid label, there is no collon the end of the word.\n");

        break;

    case LONG_LABEL_ERR:
        fprintf(stderr, "Invalid label, max label length is: %d\n", MAX_LABEL_LEN);

        break;

    case FIRST_CHAR_NOT_ALPHANUMERIC:
        fprintf(stderr, "Invalid label, first char should be alphanumeric\n");

        break;

    case ONLY_ALPHANUMERIC_OR_DIGIT:
        fprintf(stderr, "Invalid label, label must contain alphanumeric or digits.\n");

        break;

    case COMMAND_INVALID_AS_LABEL:
        fprintf(stderr, "Invalid label, can`t define label as command name.\n");

        break;

    case INVALID_LABEL:
        fprintf(stderr, "Invalid label, after label should be command or directive.\n");

        break;

    case REGISTER_INVALID_AS_LABEL:
        fprintf(stderr, "Invalid label, can`t define label as register name.\n");

        break;


    case PARAM_DIR_ERR:
        fprintf(stderr, "Invalid directive, have to be parameters with directives .\n");

        break;

    case DIR_ERR_INPUT_PARAMS:
        fprintf(stderr, "Invalid directive, number of parameters doesn`t fit the directive.\n");

        break;

    case INVALID_COMMA_IN_DATA:
        fprintf(stderr, "Invalid directive, wrong comma location.\n");

        break;

    case SHOULD_BE_NUM:
        fprintf(stderr, "Invalid data directive, should be integer or '-' or '+'.\n");

        break;

    case SHOULD_BE_COMMA:
        fprintf(stderr, "Invalid data directive, after number should be comma.\n");

        break;

    case ONLY_ONE_OPERAND_STRING:
        fprintf(stderr, "Invalid string directive, directive,scan contain only one parameter.\n");

        break;

    case INVALID_OPERAND_STRING:
        fprintf(stderr, "Invalid string directive, the string is not correct.\n");

        break;

    case FIRST_PARAM_MUST_BE_NUM:
        fprintf(stderr, "Invalid struct directive, the first parameter has to be a number.\n");

        break;

    case SHOULD_BE_STRING:
        fprintf(stderr, "Invalid struct directive,has to be two parameters, first number and second string!.\n");

        break;

    case INVALID_STRING:
        fprintf(stderr, "Invalid struct directive,second parameter has to be string!.\n");

        break;

    case MAX_TWO_OPERANDS:
        fprintf(stderr, "Invalid struct directive,has to contain maximum two parameters!.\n");

        break;

    case SHOULD_BE_LABEL_AFTER:
        fprintf(stderr, "Invalid extern directive, has to be label after extern directive!\n");

        break;

    case INVALID_LABEL_AFTER_EXT:
        fprintf(stderr, "Invalid extern directive, the label is invalid!\n");

        break;

    case ONLY_ONE_OPERAND_EXTRN:
        fprintf(stderr, "Invalid extern directive,should be only one parameters as label!\n");

        break;

    case NO_OP_DIR_FOUND:
        fprintf(stderr, "Invalid directive or command!\n");

        break;

    case INVALID_SYNTAX_OPP:
        fprintf(stderr, "Invalid command, check the syntax!.\n");

        break;

    case MAX_2_OPERANDS_OP:
        fprintf(stderr, "Invalid command, command can contain maximum 2 parameters!\n");

        break;

    case NO_ADDRESS_METH:
        fprintf(stderr, "Invalid addressing!\n");

        break;

    case INVALID_NUM_OPERANDS_OP:
        fprintf(stderr, "Invalid command, the numbers of paraters doesn`t fit to command needs!\n");

        break;

    case INVALID_NUM_OPERANDS_ADDRESS:
        fprintf(stderr, "Invalid command, addressing doesn`t fit to command needs!\n");

        break;

    case NO_LABEL_IN_ENTRY:
        fprintf(stderr, "Invalid entry, directive should be along exsiting label!.\n");

        break;

    case ENTRY_INVALID_AS_EXTERN:
        fprintf(stderr, "Invalid extern, can`t defind as label that defiend as external label!\n");

        break;

    case NO_LABEL_FOUND:
        fprintf(stderr, "Invalid label, no label been found!\n");

        break;

    case ENTRY_OR_EXTRN_IGNORE:
        fprintf(stderr, "WARNING, a label defiend as external or entry is meaningless and the assembler ignoers this label! ");

        break;

    case IN_VALID_SYNTAX_FILE_NAME:
        fprintf(stderr, "Invalid file name syntax!\n");

        break;

    case FAILED_OPEN_FILE:
        fprintf(stderr, "Invalid file,there is issue while trying open the file!\n");
    }
}