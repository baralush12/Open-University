#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#include "error.h"
#include "global.h"
#include "function.h"


/*This function creates a new file containing the macro contents*/
int preproccesor(int argc, char *argv[])
{
	int index;
	char* new_fname;
	FILE* fp;
	int line1 = 0;
	int line2 = 0;
	macro_next macro_table = (macro_next)is_valid_malloc(sizeof(macrolist));
	macro_table = NULL;
	has_macro = FALSE;

	for (index = 1; index < argc; index++) 
	{
		new_fname = create_new_file_name(argv[index], INPUT);/*returns a string containg the file name.*/
		fp = fopen(new_fname, "r");
		line1 = which_line_is_endmacro(fp); /* returns the next line after last "endmacro"*/
		fclose(fp);

		fp = fopen(new_fname, "r");
		line2 = which_line_is_first_macro(fp);
		fclose(fp);

		fp = fopen(new_fname, "r");
		macro_table = extract_macro_info(fp); /* build the macro table based on input*/

		fp = fopen(new_fname, "r");
		input_macro_into_file(macro_table, fp, line1, line2, new_fname);/*create a new file with macros translated*/

	}

	fclose(fp);
	return 0;
}

/* This function goes through all slices in source code and replaces any macros found with the proper content.*/

macro_next extract_macro_info(FILE* input_file)
{
	char* temp;
	bool in_macro_flag = FALSE;
	char* macro = "macro";
	char endmacro[8] = "endmacro";
	char* first_word;
	char* second_word;
	bool first_macro_flag = TRUE;
	char* temp_null = "\0";
	macro_next macro_ptr;
	macro_next first_macro_ptr;
	char* line_from_input = (char *) malloc(100);
	first_word = (char *) malloc(100);
	second_word = (char *) malloc(100);
	macro_ptr = (macro_next)is_valid_malloc(sizeof(macrolist));
	first_macro_ptr = (macro_next)is_valid_malloc(sizeof(macrolist));
	first_macro_ptr = macro_ptr;
	while (fgets(line_from_input, MAX_LINE_LEN, input_file)) 
	{
		first_word = get_first_word(line_from_input);/*too look for "macro" and "endmacro"*/
		second_word = get_second_word(line_from_input);/*too look for the name of macro*/
		if (strcmp(first_word,endmacro) == 0) /* checks if we reached the end of a macro.*/
		{
			in_macro_flag = FALSE;			
		}
		if (in_macro_flag == TRUE && (strcmp(first_word,endmacro) != 0)) /*checks too see if we are still inside a macro, if we are, continue reading the macro's content into our macro struct.*/
				{
					strcat(macro_ptr->macro_content, line_from_input);/*add the line to macro content*/
				}

		 if(strcmp(first_word , macro) == 0)/* if first slice in line is "macro" we save the next slice as name and know we are inside a macro's data*/		
		{
			 has_macro = TRUE;
			if(first_macro_flag == FALSE)
			{
				macro_ptr->next = (macro_next) malloc(sizeof(macrolist));
				macro_ptr = macro_ptr->next; /* if we reached the end of macro, we finish writing into current macro_struct and move to next empty struct.*/
			}
			first_macro_flag = FALSE;
			strcpy(macro_ptr->macro_name, second_word);/*if first word is macro we know the second word is the macro name.*/
			in_macro_flag = TRUE;
		 }
	}
	macro_ptr = first_macro_ptr;/*reset pointer to first struct in list*/
	free(line_from_input);
    	temp = macro_ptr->macro_name;/*temp holds the fisrt macro sturct's name, if it exists.*/
	if(strcmp(temp , temp_null) == 0)/*too check if macro list is null, if it is return null*/
	{
		macro_ptr = NULL;
	}
	return macro_ptr;
}

/*THis function builds a new file with ".am" type and translates the macros if there are any.*/
FILE* input_macro_into_file(macro_next macrolist, FILE* input_file, int last_endmacro_line, int first_macro_line, char *new_fname)
{	
	char* macro_match_checker;
	char* temp;
	char* temp_null;
	int counter = 0; /*counter too know from which line we should start trying to translate*/
	char* name;
	FILE* output_file;
	char line_from_input[80];
	macro_next macro_first_pointer;
	char* temp_macro_name;
	new_fname = cut(new_fname);
	name = create_new_file_name(new_fname, MACRO);
	output_file = fopen(name, "w+");
	temp_macro_name = (char *) malloc(100);
	macro_match_checker = (char *) malloc(50);
	temp = (char *) malloc(50);
	temp_null = (char *) malloc(50);
	macro_first_pointer = (macro_next)is_valid_malloc(5 * sizeof(macrolist));
	macro_first_pointer = macrolist;

	while (fgets(line_from_input, MAX_LINE_LEN, input_file))
	{
		temp_macro_name = NULL;
		macro_match_checker = NULL;
		counter++;

		if(first_macro_line != -1)/*checks to see if there are macros in file, -1 = no macro*/
		{
			temp = macrolist->macro_name;
		}

		if(strcmp(temp , temp_null) == 0)
		{
			fputs(line_from_input, output_file);
		}
		else if(counter >= last_endmacro_line || counter < first_macro_line) /* true only if we have passed the last "endmacro"*/
		{
				while(macrolist != NULL) /*checking if macro struct is empty*/
				{
					if(macrolist->macro_name != NULL)/*too check if the current struct is empty or not*/
					{
						temp_macro_name = macrolist->macro_name;
						macro_match_checker = strstr(line_from_input, temp_macro_name); /* checks if our saved macro_name are inside the line we are reading*/
						if(macro_match_checker != NULL)/*too check if the macro name we are currently checking is in the line.*/
						{
							swap(line_from_input, macrolist->macro_content);
						}
					}
					macrolist = macrolist->next;
				}
				macrolist = macro_first_pointer; /*reset pointer to start of struct*/
				
				fputs(line_from_input, output_file); /* if new_line_to_write is null, use original line.*/	
		}
	}
	fclose(output_file);
	return output_file;
}



