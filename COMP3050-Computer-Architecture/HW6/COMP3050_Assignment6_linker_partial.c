/**** This is the Mic-1 linker ****/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEADERS         1
#define NO_HEADERS      0

typedef struct nament{
        char   name[26];
        int    addr;
        struct nament *next;
}SYMTABENTRY;


void  add_symbol(char * symbol, int line_number);
void  generate_code(int);
void  print_first_pass(int);
void  append_table(void);
void  dump_table(void);


SYMTABENTRY *symtab = NULL;
FILE  *p1, *p2;
char  cstr_12[13];

int main(int argc, char *argv[])
{
	int  i, start, pc_offset=0, pc=0;
	int  linum=0, object_file=0, dump_tab=0;
        int  line_number, new_pc;
	char instruction[18];
	char symbol[26];

/***
	for(i=0; i<argc; i++){
	  printf("arg %d is %s\n", i, argv[i]);
	}
***/

        if(argc > 1 && (strcmp(argv[1], "-s") == 0)) dump_tab = linum = 1;
        else if(argc > 1 && (strcmp(argv[1], "-o") == 0)) object_file = 1;

	if(dump_tab == 1 | object_file == 1)start=2;
	else start = 1; 

	p1 = fopen("/tmp/passone", "w+");
        unlink("/tmp/passone");

	for(i=start; i<argc; ++i){
		if((p2 = fopen(argv[i], "r")) == NULL){
		  printf("ERROR: cannot open file %s\n", argv[i]);
		  exit(6);
		}
		while(fscanf(p2,"%d %s", &pc, instruction) != EOF){
		  if(pc == 4096)break;
		  new_pc = pc + pc_offset;
		  symbol[0] = '\0';
		  if(instruction[0] == 'U'){
            	    fscanf(p2, "%s", symbol);
		  }
		  fprintf(p1, "  %d  %s  %s\n", new_pc, instruction, symbol);
		}
		while(fscanf(p2,"%s %d",symbol, &line_number) != EOF){
		  add_symbol(symbol, line_number+pc_offset);
		}
		pc_offset = new_pc + 1;
		fclose(p2);
	}

