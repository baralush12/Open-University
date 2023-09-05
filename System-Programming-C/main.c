#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "global.h"
#include "function.h"

unsigned int data[2500];
unsigned int instructions[2500];
int IC;
int DC;
int error;
bool entry_flag = FALSE, extern_flag = FALSE, there_error= FALSE, is_first_pass = TRUE, has_macro;
label_next symbols_tab;
is_ext ext_tab;
macro_next macro_table;

const char *commands[] = {
        "mov", "cmp", "add", "sub", "lea", "not" , "clr" , "inc", "dec", "jmp", "bne",
        "get", "prn", "jsr", "rts", "hlt"
};

const char *directives[] = {
        ".data", ".string", ".struct", ".entry", ".extern"
};


int main(int argc, char* argv[])
{
    int index;
    char* new_fname;
    FILE* fp;

    for (index = 1; index < argc; index++) 
    {
       /*function to extract info and make a new file containg the translated macros with ".am" type.*/
        macro_table = NULL;
        preproccesor(argc, argv); 
	new_fname = create_new_file_name(argv[index], MACRO);
	
        fp = fopen(new_fname, "r");
        if (fp != NULL) 
	{
	    rewind(fp);
        printf("Starting First Pass Assembling With FILE: %s \n\n", new_fname);
            reset_all();
            fpass(fp, new_fname);/*First pass*/
            if (!there_error) 
	    {
                rewind(fp);
                printf("************* Started Second Pass assembling process *************\n\n");
                spass(fp, new_fname);/*Second pass*/
            }
            printf("\n The Assembling Proccess %s is done!\n", new_fname);
        }
        else print_err(FAILED_OPEN_FILE);
        free(new_fname);
    }
	fclose(fp);
    return 0;
}
