#ifndef ERROR_H

#define ERROR_H
#include "global.h"


enum errors {
    INVALID_SYNTAX = 1, EXIST_LABEL_ERR, NONE_COLLON_LABEL, LONG_LABEL_ERR, FIRST_CHAR_NOT_ALPHANUMERIC
    , ONLY_ALPHANUMERIC_OR_DIGIT, COMMAND_INVALID_AS_LABEL, INVALID_LABEL, REGISTER_INVALID_AS_LABEL,
    PARAM_DIR_ERR, DIR_ERR_INPUT_PARAMS, INVALID_COMMA_IN_DATA,
    SHOULD_BE_NUM, ONLY_ONE_OPERAND_STRING, INVALID_OPERAND_STRING, SHOULD_BE_STRING,
    INVALID_STRING, SHOULD_BE_COMMA, FIRST_PARAM_MUST_BE_NUM, MAX_TWO_OPERANDS,
    SHOULD_BE_LABEL_AFTER, INVALID_LABEL_AFTER_EXT, ONLY_ONE_OPERAND_EXTRN,
    NO_OP_DIR_FOUND, INVALID_SYNTAX_OPP, MAX_2_OPERANDS_OP,
    NO_ADDRESS_METH, INVALID_NUM_OPERANDS_OP, INVALID_NUM_OPERANDS_ADDRESS,
    NO_LABEL_IN_ENTRY, ENTRY_INVALID_AS_EXTERN, NO_LABEL_FOUND, ENTRY_OR_EXTRN_IGNORE, IN_VALID_SYNTAX_FILE_NAME,
    FAILED_OPEN_FILE
};


#endif
