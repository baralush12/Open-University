/*declare all the function by order*/


#ifndef FUNCTION_H

#define FUNCTION_H

#include "global.h"

char* cut(char* buffer);
void swap(char* str1, char* str2);

/*MEMORY ALLOCATING FUNCTIONS*/
void* is_valid_malloc(long size);
void* is_valid_calloc(size_t nitems, size_t size);


/*GLOBAL/UTILS FUNCTIONS - analyzing word*/
char* toBinary(int n, int len);
int binToDec(char* x);
char* get_next_string(char* to, char* line);
char* get_next_slice(char* to, char* line);
char* next_slice(char* line);
char* delete_space(char* ptr);
void transfer_line(char* new_line, char* curr_line);
int end_line(char* ptr);
int jump(char* ptr);
int check_val_in(char* c, const char* array[], int n);
int checkin_dir(char* word);
char* int_to_base32(unsigned int num);
bool is_str(char* s);
bool is_num(char* c);
bool is_reg(char* word);


/*CREATE FILES*/
char* create_new_file_name(char* fname, int file_type);
FILE* new_file(char* filename, int type);
int create_files(char* filename);


/*PRE-PROCESSOR*/
int preproccesor(int argc, char *argv[]);
char* get_second_word(char* line);
char* get_first_word(char* line);
int which_line_is_endmacro(FILE* input_file);
int which_line_is_first_macro(FILE* input_file);
macro_next extract_macro_info(FILE* input_file);
FILE* input_macro_into_file(macro_next macrolist, FILE* input_file, int last_endmacro_line, int first_macro_line, char* new_fname);

/*LABEL*/
label_next addlabel(label_next* hp, char* lname, unsigned int laddress, bool label_extern, ...);
int remove_label(label_next* hp, char* lname);
void free_all_labels(label_next* hp);
void reset_all();
void valid_address(label_next hp, int index, bool get_data);
unsigned int get_laddress(label_next hp, char* lname);
bool is_valid_label(label_next hp, char* lname);
label_next check_label(label_next hp, char* lname);
bool check_if_external(label_next hp, char* name);
bool entry_in(label_next hp, char* lname);
is_ext add_ext_label(is_ext* hp, char* ext_name, unsigned int ext_address);
void free_ext_labels(is_ext* hp);

/*ERRORS*/
void print_err(int index);
int iserror();

/*DATA INCDOING FUNCTIONS*/
void instruction_encode(unsigned int val);
unsigned int are_put(unsigned int line, int type);


/*main*/

void fpass(FILE* file_desc, char* name);
void spass(FILE* file_desc, char* fname);


/*FIRST PASS*/
unsigned int add_reg_word(char* word, bool destination);
void add_extra_word(int type_meth, bool destination, char* word);
int add_extra_words(char* first_op, char* second_op, bool has_source, bool has_destination, int first_meth, int second_meth);
unsigned int first_word(int opcode, int first_w, int second_w, int first_address, int second_address);
bool valid_add_meth(int op, int first_op, int second_op);
bool valid_opp(int op, bool first_op, bool second_op);
int what_meth(char* op, bool is_first_pass);
int what_op(int op, char* line);
int is_data_dir(char* line);
int what_dir(int dir, char* line);
int is_extrn_dir(char* line);
int is_string_dir(char* line);
int is_struct_dir(char* line);
bool is_label(char* word, int is_ext_or_ent);
void analyze_line(char* line);
void num_data_encode(int val);
void str_data_encode(char* val);
int convert(unsigned int n);

/*SECOND PASS*/
void analyze_command_words(int op_type, char* word);
void add_extra_word_spass(int type_meth, char* word);
void add_extra_word_label(char* word);
void analyze_line_spass(char* line);

void create_ob_file(FILE *file_desc);
void create_ent_file(FILE* file_desc);
void create_ext_file(FILE* file_desc);


/*extern varibales*/
extern int IC, DC;
extern int error;
extern bool entry_flag, extern_flag, there_error, is_first_pass, has_macro;
extern const char* commands[];
extern const char* directives[];
extern label_next symbols_tab;
extern is_ext ext_tab;
extern macro_next macro_table;

#endif
