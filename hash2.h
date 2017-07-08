#ifndef HASH2
#define HASH2

#include "list2.h"

typedef struct{
        char callee_num[15];
        calleeList *info;
}bucket2Entry;

typedef struct bucket2List bucket2List;

struct bucket2List{
        bucket2Entry* num_array;
        int array_size;
        int in_array;
        bucket2List* next;
};

typedef struct Hash2 Hash2;

struct Hash2{
        bucket2List** buckets;
        int size;
	int bucket_size;
};

int hash2_function(int table_size,char* call_num);

bucket2List* create_bucket_two(int size);

void add_bucket_two(bucket2List* list,char* call_num,calleeInfo callee);

void destroy_bucket_two(bucket2List* list);

void print_bucket_two(bucket2List* list);

void dump_bucket_two(FILE* fp,bucket2List* list);

void print_bucket_callee(bucket2List* list,char* call_num);

void print_time_callee(bucket2List* list,char* call_num,int time1,int time2);

void print_year_callee(bucket2List* list,char* call_num,int year1,int year2);

void print_timeyear_callee(bucket2List* list,char* call_num,int time1,int time2,int year1,int year2);

char** callers_bucket_two(bucket2List* list,char* callee,char* other_callee);

Hash2* create_hashtable2(int size,int bucketsize);

void add_hashtable2(Hash2* table,char* call_num,calleeInfo caller);

void destroy_hashtable2(Hash2* table);

void print_hashtable2(Hash2* table);

void dump_hashtable2(FILE* fp,Hash2* table);

void print_hashtable2_callee(Hash2* table,char* call_num);

void print_hashtable2_time(Hash2* table,char* call_num,int time1,int time2);

void print_hashtable2_year(Hash2* table,char* call_num,int year1,int year2);

void print_hashtable2_timeyear(Hash2* table,char* call_num,int time1,int time2,int year1,int year2);

#endif
