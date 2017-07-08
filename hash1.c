#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash1.h"
#include "list1.h"

int hash1_function(int table_size,char* call_num){
	char buf[11];
	int i;
	long long num;
	for(i=4;i<14;i++)
		buf[i-4] = call_num[i];
	buf[10] = '\0';
	num = atoll(buf);
	return (num % table_size);
}

bucket1List* create_bucket_one(int size){
	int i;
	bucket1List* head = NULL;
	head = malloc(sizeof(bucket1List));
	if(head == NULL){
		printf("Error creating bucket list for hashtable1.\n");
		return NULL;
	}
	head->array_size = size;
	head->in_array = 0;
	head->next = NULL;
	head->num_array = malloc(size*sizeof(bucket1Entry));
	if(head->num_array == NULL){
		return NULL;
	}
	for(i=0;i<size;i++){
                strcpy(head->num_array[i].caller_num,"\0");
                head->num_array[i].info = NULL;
        }
	return head;
}

void add_bucket_one(bucket1List* list,char* call_num,callerInfo caller){
        bucket1List* temp = list;
        int i;
        while(temp != NULL){
                if(temp->in_array < temp->array_size){
                        for(i = 0;i < temp->array_size;i++){
                                if(!strcmp(temp->num_array[i].caller_num,"\0")){
                                        strcpy(temp->num_array[i].caller_num,call_num);
                                        temp->num_array[i].info = create_caller_list(temp->array_size);
                                        if(temp->num_array[i].info == NULL){
                                                printf("Error allocating memory.\n");
                                                exit(EXIT_FAILURE);
                                        }
                                        add_caller_list(temp->num_array[i].info,caller);
                                        (temp->in_array)++;
                                        return;
                                }
                                if(!strncmp(temp->num_array[i].caller_num,call_num,14)){
                                        add_caller_list(temp->num_array[i].info,caller);
                                        (temp->in_array)++;
                                        return;
                                }
                        }

                }
                else{
                        if(temp->next == NULL){
                                temp->next = malloc(sizeof(bucket1List));
                                if(temp->next == NULL){
                                        printf("Error allocating memory.\n");
                                        exit(EXIT_FAILURE);
                                }
                                temp->next->array_size = temp->array_size;
                                temp->next->in_array = 0;
                                temp->next->next = NULL;
                                temp->next->num_array = malloc((temp->array_size)*sizeof(bucket1Entry));
                                if(temp->next->num_array == NULL){
                                        printf("Error allocating memory.\n");
                                        exit(EXIT_FAILURE);
                                }
                                for(i=0;i < temp->array_size;i++){
                                        strcpy(temp->next->num_array[i].caller_num,"\0");
                                        temp->next->num_array[i].info = NULL;
                                }
                                temp=temp->next;
                        }
                        else
                                temp = temp->next;
                }
        }
}


void destroy_bucket_one(bucket1List* list){
        bucket1List* temp;
        int i;
        while(list != NULL){
                temp = list->next;
                for(i = 0;i < list->array_size;i++)
                        if(list->num_array[i].info != NULL)
                                destroy_caller_list(list->num_array[i].info);
                free(list->num_array);
                free(list);
                list = temp;
        }
}

void print_bucket_one(bucket1List* list){
        bucket1List* temp = list;
        int i,j;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->num_array[i].caller_num,"\0")){
                                printf("Caller: %s\n",temp->num_array[i].caller_num);
                                print_caller_list(temp->num_array[i].info);
                        }
                temp=temp->next;
        }
}

void dump_bucket_one(FILE* fp,bucket1List* list){
	bucket1List* temp = list;
        int i,j;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->num_array[i].caller_num,"\0")){
                                fprintf(fp,"Caller: %s\n",temp->num_array[i].caller_num);
                                dump_caller_list(fp,temp->num_array[i].info);
                        }
                temp=temp->next;
        }
}

void print_bucket_caller(bucket1List* list,char* call_num){
        bucket1List* temp = list;
        int i,j;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->num_array[i].caller_num,"\0"))
                                if(!strncmp(temp->num_array[i].caller_num,call_num,14)){
                                        printf("Caller: %s\n",temp->num_array[i].caller_num);
                                        print_caller_list(temp->num_array[i].info);
					return;
                                }
                temp=temp->next;
        }
}

void print_time_caller(bucket1List* list,char* call_num,int time1,int time2){
        bucket1List* temp = list;
        int i,j;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->num_array[i].caller_num,"\0"))
                                if(!strncmp(temp->num_array[i].caller_num,call_num,14)){
                                        printf("Caller: %s\n",temp->num_array[i].caller_num);
                                        printtime_caller_list(temp->num_array[i].info,time1,time2);
					return;
                                }
                temp=temp->next;
        }
}

void print_year_caller(bucket1List* list,char* call_num,int year1,int year2){
        bucket1List* temp = list;
        int i,j;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->num_array[i].caller_num,"\0"))
                                if(!strncmp(temp->num_array[i].caller_num,call_num,14)){
                                        printf("Caller: %s\n",temp->num_array[i].caller_num);
                                        printyear_caller_list(temp->num_array[i].info,year1,year2);
					return;
                                }
                temp=temp->next;
        }
}

void print_timeyear_caller(bucket1List* list,char* call_num,int time1,int time2,int year1,int year2){
        bucket1List* temp = list;
        int i,j;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->num_array[i].caller_num,"\0"))
                                if(!strncmp(temp->num_array[i].caller_num,call_num,14)){
                                        printf("Caller: %s\n",temp->num_array[i].caller_num);
                                        printtimeyear_caller_list(temp->num_array[i].info,time1,time2,year1,year2);
					return;
                                }
                temp=temp->next;
        }
}

void delete_bucket_one(bucket1List* list,char* call_num,char* cdr_id){
	bucket1List* temp = list;
        int i,j;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(!strncmp(temp->num_array[i].caller_num,call_num,14)){
                                delete_caller_list(temp->num_array[i].info,cdr_id);
				return;
                        }
                temp=temp->next;
        }
	printf("DError: found nothing to delete.\n");
}

void topdest_bucket_one(bucket1List* list,char* call_num){
	bucket1List* temp = list;
        int i,j;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(!strncmp(temp->num_array[i].caller_num,call_num,14)){
                                topdest_caller_list(temp->num_array[i].info);
                                return;
                        }
                temp=temp->next;
        }
}

char** callees_bucket_one(bucket1List* list,char* caller,char* other_caller){
	bucket1List* temp = list;
        int i,j;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(!strncmp(temp->num_array[i].caller_num,caller,14)){
                                return get_callees(temp->num_array[i].info,other_caller);
                        }
                temp=temp->next;
        }
	return NULL;
}

Hash1* create_hashtable1(int size,int bucketsize){
	int i;
	Hash1* table = NULL;
	table = malloc(sizeof(Hash1));
	if(table == NULL){
		printf("Memory allocation error.\n");
		exit(EXIT_FAILURE);
	}
	table->size = size;
	table->bucket_size = bucketsize;
	table->buckets = malloc(size*sizeof(bucket1List*));
	if(table->buckets == NULL){
		printf("Memory allocation error.\n");
		exit(EXIT_FAILURE);
	}
	for(i=0;i<size;i++)
		table->buckets[i] = NULL;
	return table;

}

void add_hashtable1(Hash1* table,char* call_num,callerInfo caller){
	int num;
	num = hash1_function(table->size,call_num);
	if(table->buckets[num] == NULL){
		table->buckets[num] = create_bucket_one(table->bucket_size);
		add_bucket_one(table->buckets[num],call_num,caller);
	}
	else
		add_bucket_one(table->buckets[num],call_num,caller);
}

void destroy_hashtable1(Hash1* table){
	int i;
	for(i=0;i < table->size;i++){
		if(table->buckets[i] != NULL)
			destroy_bucket_one(table->buckets[i]);
	}
	free(table->buckets);
	free(table);
	table = NULL;
}

void print_hashtable1(Hash1* table){
	int i;
	for(i=0;i< table->size;i++){
		printf("Bucket %d:\n\n",i);
		if(table->buckets[i] != NULL){
			print_bucket_one(table->buckets[i]);
			printf("\n");
		}
	}
}

void dump_hashtable1(FILE* fp,Hash1* table){
	int i;
        for(i=0;i< table->size;i++){
                fprintf(fp,"Bucket %d:\n\n",i);
                if(table->buckets[i] != NULL){
                        dump_bucket_one(fp,table->buckets[i]);
                        fprintf(fp,"\n");
                }
        }
}

void print_hashtable1_caller(Hash1* table,char* call_num){
	int num;
	num = hash1_function(table->size,call_num);
	if(table->buckets[num] != NULL)
		print_bucket_caller(table->buckets[num],call_num);
}

void print_hashtable1_time(Hash1* table,char* call_num,int time1,int time2){
	int num;
        num = hash1_function(table->size,call_num);
        if((table->buckets[num]) != NULL)
                print_time_caller(table->buckets[num],call_num,time1,time2);
}

void print_hashtable1_year(Hash1* table,char* call_num,int year1,int year2){
        int num;
        num = hash1_function(table->size,call_num);
        if((table->buckets[num]) != NULL)
                print_year_caller(table->buckets[num],call_num,year1,year2);
}


void print_hashtable1_timeyear(Hash1* table,char* call_num,int time1,int time2,int year1,int year2){
        int num;
        num = hash1_function(table->size,call_num);
        if((table->buckets[num]) != NULL)
                print_timeyear_caller(table->buckets[num],call_num,time1,time2,year1,year2);
}

void delete_hashtable1(Hash1* table,char* call_num,char* cdr_id){
	int num;
        num = hash1_function(table->size,call_num);
        if((table->buckets[num]) != NULL)
                delete_bucket_one(table->buckets[num],call_num,cdr_id);
	else
		printf("DError: Caller not found.");
}

void topdest_hashtable1(Hash1* table,char* call_num){
	int num;
        num = hash1_function(table->size,call_num);
        if((table->buckets[num]) != NULL)
                topdest_bucket_one(table->buckets[num],call_num);
}
