#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "error.h"
#include "global.h"
#include "function.h"

/*Label structre function*/
bool entry_in(label_next hp, char* lname)
{
	label_next p_label = check_label(hp, lname); /*p_label holds the struct with specified name*/
	if (p_label != NULL)
	{
		if (p_label->label_extern)
		{
			error = ENTRY_INVALID_AS_EXTERN;
			return FALSE;
		}
		p_label->label_entry = TRUE;
		entry_flag = TRUE; /*defiend as global in main, if true the label are entry*/
		return TRUE;
	}
	else {
		error = NO_LABEL_IN_ENTRY;
	}
	return FALSE;
}
/*returns the address of given name from symbol table */
unsigned int get_laddress(label_next hp, char* lname)
{
	label_next p_label = check_label(hp, lname);
    if (p_label != NULL)
	{
		return p_label->laddress;
	}
	return FALSE;
}

/*This function checks if the label is in the list and returns it, returns NULL if it isnt in table */
label_next check_label(label_next hp, char* lname)
{
	while (hp)
	{
		if (strcmp(hp->lname, lname) == 0) {
			return hp;
		}
		hp = hp->next;
	}
	return NULL;
}
/*check if the label name is a syntactically valid name*/
bool is_valid_label(label_next hp, char* lname)
{
	return check_label(hp, lname) != NULL;
}

/*Function that add new external label with his address to the external linklist*/
is_ext add_ext_label(is_ext* hp, char* ext_name, unsigned int ext_address)
{
	is_ext h = *hp;
	is_ext h_temp;

	h_temp = (is_ext)is_valid_malloc(sizeof(link_ext));

	h_temp->ext_address = ext_address;
	strcpy(h_temp->ext_name, ext_name);
	

	if (!(*hp)) /*if list empty*/
	{
		*hp = h_temp;
		h_temp->next = h_temp;
		h_temp->pre = h_temp;
		return h_temp;
	}

	((*hp)->pre)->next = h_temp;
	h_temp->next = h;
	h_temp->pre = h->pre;
	(*hp)->pre = h_temp;

	return h_temp;
}
/*The function free all the external labels name and addresses*/
void free_ext_labels(is_ext* hp)
{
	is_ext hp_temp = *hp;
	if (hp_temp) {
		unsigned int old_add = ((*hp)->pre)->ext_address;
		unsigned int add = 0;
		do {
			hp_temp = *hp;
			add = hp_temp->ext_address;
			*hp = (*hp)->next;
			free(hp_temp);
		} while (add != old_add);
	}
}

/*function that adds a new label to the linked list*/
label_next addlabel(label_next *hp, char *lname, unsigned int laddress, bool label_extern, ...)
{
	va_list ptr;

	label_next h = *hp;
	label_next h_temp;

	/*avoid multiple labels with the same name, the name shoud be union*/
	if (is_valid_label(*hp, lname))
	{
		error = EXIST_LABEL_ERR;
		return NULL;
	}
	/*create new linklist for h_temp*/
	h_temp = (label_next)is_valid_malloc(sizeof(link_labels));
	/*insert the given label to temp*/ 
	strcpy(h_temp->lname, lname);
	h_temp->label_entry = FALSE;
	h_temp->laddress = laddress;
	h_temp->label_extern = label_extern;

	/*make sure the label isn`t a command*/
	if (!label_extern)
	{
		va_start(ptr, label_extern);
		h_temp->label_op = va_arg(ptr, bool);
	}
	else
	{
		extern_flag = TRUE;
	}
	if (!(*hp)) /*if list empty*/
	{
		*hp = h_temp;
		h_temp->next = NULL;
		return h_temp;
	}

	while (h->next != NULL)
	{
		h = h->next;
	}
	h_temp->next = NULL;
	h->next = h_temp;
	
	va_end(ptr);
	return h_temp;
}

/*
Free the allocated memory for the symbols table to avoid memory issues
will move each label and free the memory one by one
*/
void free_all_labels(label_next* hp)
{
	label_next hp_temp;
	while (*hp)
	{
		hp_temp = *hp;
		*hp = (*hp)->next;
		free(hp_temp);
	}
}
/*removes the label matching the input name from the symbol table, and reorganizes the list*/
int remove_label(label_next* hp, char* lname)
{
	label_next hp_temp = *hp;
	label_next prev;
	while (hp_temp)
	{
		if (strcmp(hp_temp->lname, lname) == 0) 
		{
			if (strcmp(hp_temp->lname, (*hp)->lname) == 0)
			{
				*hp = (*hp)->next;
				free(hp_temp);
			}
			else {
				prev->next = hp_temp->next;
				free(hp_temp);
			}
			return 1;
		}
		prev = hp_temp;
		hp_temp = hp_temp->next;
	}
	return 0;
}

/*updates the symbol's address in symbol table for given symbol*/
void valid_address(label_next hp, int index, bool get_data)
{
	while (hp)
	{
		if (!(hp->label_extern) && (get_data ^ (hp->label_op)))
		{
			hp->laddress += index;
		}
		hp = hp->next;
	}
}

