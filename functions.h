#ifndef FUNCTIONS
#define FUNCTIONS

#include "hash1.h"
#include "hash2.h"
#include "heap.h"

typedef struct{
        Hash1* table1;
        Hash2* table2;
	heapNode* heap;
}myPointers;

void insert_function(char* cdr_record,float config[5][3],int* sizes,myPointers* pointers);

void delete_function(char* caller,char* cdr_id,myPointers* pointers);

void find_function(int argnum,char** my_args,myPointers* pointers);

void lookup_function(int argnum,char** my_args,myPointers* pointers);

void indist_function(char* caller1, char* caller2,myPointers* pointers);

void topdest_function(char* caller,myPointers* pointers);

void top_function(char* k,myPointers* pointers);

void bye_function(myPointers* pointers);

void print_function(char* hashttableX,myPointers* pointers);

void dump_function(char* hashttableX,char* filename,myPointers* pointers);

#endif
