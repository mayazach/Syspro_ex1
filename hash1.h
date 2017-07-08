#ifndef HASH1
#define HASH1

#include "list1.h"
typedef struct{
        char caller_num[15];
        callerList *info;
}bucket1Entry;

typedef struct bucket1List bucket1List;

struct bucket1List{
        bucket1Entry* num_array;
        int array_size;
        int in_array;
        bucket1List* next;
};

typedef struct Hash1 Hash1;

struct Hash1{
	bucket1List** buckets;
	int size;
	int bucket_size;
};

int hash1_function(int table_size,char* call_num);

bucket1List* create_bucket_one(int size);

void add_bucket_one(bucket1List* list,char* call_num,callerInfo caller);

void destroy_bucket_one(bucket1List* list);

void print_bucket_one(bucket1List* list);

void dump_bucket_one(FILE* fp,bucket1List* list);

void print_bucket_caller(bucket1List* list,char* call_num);

void print_time_caller(bucket1List* list,char* call_num,int time1,int time2);

void print_year_caller(bucket1List* list,char* call_num,int year1,int year2);

void print_timeyear_caller(bucket1List* list,char* call_num,int time1,int time2,int year1,int year2);

void delete_bucket_one(bucket1List* list,char* call_num,char* cdr_id);

void topdest_bucket_one(bucket1List* list,char* call_num);

char** callees_bucket_one(bucket1List* list,char* caller,char* other_caller);

Hash1* create_hashtable1(int size,int bucketsize);

void add_hashtable1(Hash1* table,char* call_num,callerInfo caller);

void destroy_hashtable1(Hash1* table);

void print_hashtable1(Hash1* table);

void dump_hashtable1(FILE* fp,Hash1* table);

void print_hashtable1_caller(Hash1* table,char* call_num);

void print_hashtable1_time(Hash1* table,char* call_num,int time1,int time2);

void print_hashtable1_year(Hash1* table,char* call_num,int year1,int year2);

void print_hashtable1_timeyear(Hash1* table,char* call_num,int time1,int time2,int year1,int year2);

void delete_hashtable1(Hash1* table,char* call_num,char* cdr_id);

void topdest_hashtable1(Hash1* table,char* call_num);

#endif
