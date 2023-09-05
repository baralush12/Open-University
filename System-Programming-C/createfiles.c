#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "error.h"
#include "global.h"
#include "function.h"
/*creates files with selected type*/
int create_files(char* filename)
{
	FILE* file_desc;
	file_desc = new_file(filename, OBJ);
	create_ob_file(file_desc);

	if (entry_flag) {
		file_desc = new_file(filename, ENTR);
		create_ent_file(file_desc);
	}
	if (extern_flag) {
		file_desc = new_file(filename, EXTRN);
		create_ext_file(file_desc);
	}
	return SUCCEED;
}


/*creates and returns a name from source code with correct type ending */
char* create_new_file_name(char* fname, int file_type)
{
	char* slice = (char*)is_valid_malloc(strlen(fname) + 6);

	strcpy(slice, fname); /* Copying original filename to the bigger string */

	/* Concatenating the required file extension */

	switch (file_type)
	{
	case INPUT:
		strcat(slice, ".as");
		break;

	case OBJ:
		strcat(slice, ".ob");
		break;

	case ENTR:
		strcat(slice, ".ent");
		break;

	case EXTRN:
		strcat(slice, ".ext");
		break;
	case MACRO:
		strcat(slice, ".am");
		break;

	}
	return slice;
}

/* creates a new blank file with specified type (ob/ent/ext)*/
FILE* new_file(char* filename, int type)
{
	FILE* file_desc;
	filename = create_new_file_name(filename, type); /*filename holds the correct name with specified ending.*/
	file_desc = fopen(filename, "w");

	free(filename);

	if (file_desc == NULL)
	{
		printf("Can't create or rewrite to file %s.", filename);
		return NULL;
	}
	return file_desc;
}

/*craetes the ".ob" output file containing the instructions in requested base32*/
void create_ob_file(FILE *file_desc)
{
	unsigned int address = MEMORY_INDEX;
	int i;
	char* m, * f;
	m = int_to_base32(IC);/*displays how many instructions there are*/

	f = int_to_base32(DC); /*displays how much data there is*/

	fprintf(file_desc, "\n %s\t%s", m, f);

	free(m);
	free(f);

	for (i = 0; i < IC; i++) { /*converts the string from instructions and inserts into output ".ob" file*/

		m = int_to_base32(address);
		f = int_to_base32(instructions[i]);

		fprintf(file_desc, "\n %s\t%s", m, f);
		address++;

		free(m);
		free(f);
	}

	for (i = 0; i < DC; i++) {/*converts the string from DATA and inserts into output ".ob" file*/

		m = int_to_base32(address);
		f = int_to_base32(data[i]);

		fprintf(file_desc, "\n %s\t%s", m, f);
		address++;

		free(m);
		free(f);
	}
	fclose(file_desc);
}

/* creates the entry output */
void create_ent_file(FILE *file_desc)
{
	char* base32data;

	label_next temp = symbols_tab;

	while (temp) /*checks which labels are labeled as "entries" in symbol table and inserts them into ".ent" output file as base32*/
	{
		if (temp->label_entry) {
			base32data = int_to_base32(temp->laddress);
			fprintf(file_desc, "\n %s\t%s", temp->lname, base32data);
			free(base32data);
		}
		temp = temp->next;
	}
	fclose(file_desc);
}
/* creates the external output */
void create_ext_file(FILE *file_desc)
{
	char* base32data;

	is_ext temp = ext_tab;

	do {
		base32data = int_to_base32(temp->ext_address);
		fprintf(file_desc, "\n %s\t%s", temp->ext_name, base32data);
		free(base32data);
		temp = temp->next;
	} while (temp != ext_tab);
	fclose(file_desc);
}
