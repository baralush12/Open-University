#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "error.h"
#include "global.h"
#include "function.h"

/* first pass operation */
void fpass(FILE* file_desc, char* name)
{
    char* line;
    int line_index = 1;
    line = (char *) malloc(200);
    /*  defined it in main */
    IC = 0;
    DC = 0;
    /* read until EOF */ 
	
    while (fgets(line, MAX_LINE_LEN, file_desc))
    {
        error = SUCCEED; /* intialize error as SUCCEED to start without errors and avoid garbage  */
        if (!jump(line))  /* jump the spaces, tab or ; */
            analyze_line(line); /* check the line and extract line meaning, label, extern\entry,opp */
        if(iserror()){ /* if there is an error in the file stop and define there_error as true */
            there_error = TRUE; 
            print_err(line_index); /* print the error */
            return;
        } 
        line_index++;
    }
    /*function that counting and address after first pass */
    valid_address(symbols_tab, MEMORY_INDEX, FALSE);
    valid_address(symbols_tab, IC + MEMORY_INDEX, TRUE);
}


