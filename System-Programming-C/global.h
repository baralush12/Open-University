
/* Here will be all the global varibales/enums, externs and structers we will work during the program */

#ifndef GLOBAL_H

#define GLOBAL_H

#define MEMORY_INDEX 100
#define MAX_LINE_LEN 81
#define MAX_LABEL_LEN 30

#define FAILED 1
#define SUCCEED 0
#define NONE -1


extern unsigned int data[];
extern unsigned int instructions[];

/*Boolean types*/

typedef enum {
    FALSE,
    TRUE
} bool;

enum {
    NONE_EXT_OR_ENT, IS_EXT_OR_ENT
};

/*Instruction type*/

enum directives {

    DATA = 0,
    STRING = 1,
    STRUCT = 2,
    ENTRY = 3,
    EXTERN = 4,
    DIR_NONE = 5

};



/*Commands Types*/

enum opcodes {
    MOV = 0,
    CMP = 1,
    ADD = 2,
    SUB = 3,
    LEA = 4,
    NOT = 5,
    CLR = 6,
    INC = 7,
    DEC = 8,
    JMP = 9,
    BNE = 10,
    GET = 11,
    PRN = 12,
    JSR = 13,
    RTS = 14,
    RTL = 15,
    OP_NONE = 16
};



/* Addressing Types */

enum adressing {
    IMMEDIATE_ADS = 0,
    DIRECT_ADS = 1,
    ACCESS_ADS = 2,
    REG_ADS = 3,
    METHOD_UNKNOWN = 4
};

/* A/R/E Types */

enum ARE {
    ABSOLUTE = 0, /*The coding is absolute*/
    EXTERNAL = 1, /*The coding is external*/
    RELOCATABLE = 2 /*The encoding requires new allocation*/
};

/* Files Types */

enum whatfiles {
    INPUT = 0,
    OBJ = 1,
    ENTR = 2,
    EXTRN = 3,
    MACRO = 4
};


/* STRUCTUERS for labels */

/* struct to work with labels, for checking validity and store the labels */
typedef struct linklabel* label_next;
typedef struct linklabel {
    char lname[MAX_LABEL_LEN]; /*The name of label, could be max 30 chars*/
    unsigned int laddress;/*store the address of the label and help us to orginaize and define address method*/
    bool label_extern; /*check if the label extrn so true and if no will be false*/
    bool label_op; /*store if the label is command so true if no its will be false*/
    bool label_entry; /*store if the label is entry so true if not will be false*/
    label_next next;/*next label in the symbols table*/
} link_labels;

/*Struct to work with external labels to store the addresses and names of external and print to file.ext*/
typedef struct link_list_ext* is_ext;
typedef struct link_list_ext {
    char ext_name[MAX_LABEL_LEN]; /*The name of label, could be max 30 chars*/
    unsigned int ext_address;/*store the address of the extern label*/
    is_ext next;/*next label in the symbols table*/
    is_ext pre;/*previues label in the symbols table*/
} link_ext;


typedef struct macro_struct* macro_next;
typedef struct macro_struct {
    char macro_content[MAX_LINE_LEN];
    char macro_name[MAX_LABEL_LEN];
    macro_next next;
} macrolist;

#endif
