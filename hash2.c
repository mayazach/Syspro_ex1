#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash2.h"
#include "list2.h"

int hash2_function(int table_size,char* call_num){
        char buf[11];
        int i;
	long long num;
        for(i=4;i<14;i++)
                buf[i-4] = call_num[i];
        buf[10] = '\0';
        num = atoll(buf);
        return (num % table_size);
}


bucket2List* create_bucket_two(int size){
        int i;
        bucket2List* head = NULL;
        head = malloc(sizeof(bucket2List));
        if(head == NULL){
                printf("Error creating bucket list for hashtable2.\n");
                return NULL;
        }
        head->array_size = size;
        head->in_array = 0;
        head->next = NULL;
        head->num_array = malloc(size*sizeof(bucket2Entry));
        if(head->num_array == NULL){
                return NULL;
        }
	for(i=0;i<size;i++){
		strcpy(head->num_array[i].callee_num,"\0");
		head->num_array[i].info = NULL;
	}
        return head;
}

void add_bucket_two(bucket2List* list,char* call_num,calleeInfo callee){
	bucket2List* temp = list;
	int i;
	while(temp != NULL){
		if(temp->in_array < temp->array_size){
			for(i = 0;i < temp->array_size;i++){
				if(!strcmp(temp->num_array[i].callee_num,"\0")){
					strcpy(temp->num_array[i].callee_num,call_num);
					temp->num_array[i].info = create_callee_list(temp->array_size);
					if(temp->num_array[i].info == NULL){
						printf("Error allocating memory.\n");
						exit(EXIT_FAILURE);
					}
					add_callee_list(temp->num_array[i].info,callee);
					(temp->in_array)++;
					return;
				}
				if(!strncmp(temp->num_array[i].callee_num,call_num,14)){
					add_callee_list(temp->num_array[i].info,callee);
                                        (temp->in_array)++;
                                        return;
				}
			}

		}
		else{
			if(temp->next == NULL){
				temp->next = malloc(sizeof(bucket2List));
				if(temp->next == NULL){
	                		printf("Error allocating memory.\n");
        	        		exit(EXIT_FAILURE);
        			}
				temp->next->array_size = temp->array_size;
			        temp->next->in_array = 0;
        			temp->next->next = NULL;
        			temp->next->num_array = malloc((temp->array_size)*sizeof(bucket2Entry));
        			if(temp->next->num_array == NULL){
                			printf("Error allocating memory.\n");
					exit(EXIT_FAILURE);
        			}
        			for(i=0;i < temp->array_size;i++){
                			strcpy(temp->next->num_array[i].callee_num,"\0");
					temp->next->num_array[i].info = NULL;
        			}
				temp=temp->next;
			}
			else
				temp = temp->next;
		}
	}
}

void destroy_bucket_two(bucket2List* list){
	bucket2List* temp;
	int i;
	while(list != NULL){
		temp = list->next;
		for(i = 0;i < list->array_size;i++)
			if(list->num_array[i].info != NULL)
				destroy_callee_list(list->num_array[i].info);
		free(list->num_array);
		free(list);
		list = temp;
	}
}

void print_bucket_two(bucket2List* list){
	bucket2List* temp = list;
	int i,j;
	while(temp != NULL){
		for(i=0;i < temp->array_size;i++)
			if(strcmp(temp->num_array[i].callee_num,"\0")){
				printf("Callee: %s\n",temp->num_array[i].callee_num);
				print_callee_list(temp->num_array[i].info);
			}
		temp=temp->next;
	}
}

void dump_bucket_two(FILE* fp,bucket2List* list){
        bucket2List* temp = list;
        int i,j;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->num_array[i].callee_num,"\0")){
                                fprintf(fp,"Callee: %s\n",temp->num_array[i].callee_num);
                                dump_callee_list(fp,temp->num_array[i].info);
                        }
                temp=temp->next;
        }
}

void print_bucket_callee(bucket2List* list,char* call_num){
	bucket2List* temp = list;
        int i,j;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->num_array[i].callee_num,"\0"))
				if(!strncmp(temp->num_array[i].callee_num,call_num,14)){
                                	printf("Callee: %s\n",temp->num_array[i].callee_num);
                                	print_callee_list(temp->num_array[i].info);
				}
                temp=temp->next;
        }
}

void print_time_callee(bucket2List* list,char* call_num,int time1,int time2){
	bucket2List* temp = list;
        int i,j;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->num_array[i].callee_num,"\0"))
                                if(!strncmp(temp->num_array[i].callee_num,call_num,14)){
                                        printf("Callee: %s\n",temp->num_array[i].callee_num);
                                        printtime_callee_list(temp->num_array[i].info,time1,time2);
                                }
                temp=temp->next;
        }
}

void print_year_callee(bucket2List* list,char* call_num,int year1,int year2){
	bucket2List* temp = list;
        int i,j;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->num_array[i].callee_num,"\0"))
                                if(!strncmp(temp->num_array[i].callee_num,call_num,14)){
                                        printf("Callee: %s\n",temp->num_array[i].callee_num);
                                        printyear_callee_list(temp->num_array[i].info,year1,year2);
                                }
                temp=temp->next;
        }
}

void print_timeyear_callee(bucket2List* list,char* call_num,int time1,int time2,int year1,int year2){
	bucket2List* temp = list;
        int i,j;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->num_array[i].callee_num,"\0"))
                                if(!strncmp(temp->num_array[i].callee_num,call_num,14)){
                                        printf("Callee: %s\n",temp->num_array[i].callee_num);
                                        printtimeyear_callee_list(temp->num_array[i].info,time1,time2,year1,year2);
                                }
                temp=temp->next;
        }
}

char** callers_bucket_two(bucket2List* list,char* callee,char* other_callee){
	bucket2List* temp = list;
        int i,j;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(!strncmp(temp->num_array[i].callee_num,callee,14)){
                                return get_callers(temp->num_array[i].info,other_callee);
                        }
                temp=temp->next;
        }
        return NULL;
}

Hash2* create_hashtable2(int size,int bucketsize){
        int i;
        Hash2* table = NULL;
        table = malloc(sizeof(Hash2));
        if(table == NULL){
                printf("Memory allocation error.\n");
                exit(EXIT_FAILURE);
        }
        table->size = size;
        table->bucket_size = bucketsize;
        table->buckets = malloc(size*sizeof(bucket2List*));
        if(table->buckets == NULL){
                printf("Memory allocation error.\n");
                exit(EXIT_FAILURE);
        }
        for(i=0;i<size;i++)
                table->buckets[i] = NULL;
        return table;

}

void add_hashtable2(Hash2* table,char* call_num,calleeInfo callee){
        int num;
        num = hash2_function(table->size,call_num);
        if(table->buckets[num] == NULL){
                table->buckets[num] = create_bucket_two(table->bucket_size);
                add_bucket_two(table->buckets[num],call_num,callee);
        }
        else
                add_bucket_two(table->buckets[num],call_num,callee);
}

void destroy_hashtable2(Hash2* table){
        int i;
        for(i=0;i < table->size;i++){
                if(table->buckets[i] != NULL)
                        destroy_bucket_two(table->buckets[i]);
        }
        free(table->buckets);
        free(table);
        table = NULL;
}

void print_hashtable2(Hash2* table){
	int i;
	for(i=0;i< table->size;i++){
		printf("Bucket %d:\n\n",i);
		if(table->buckets[i] != NULL){
			print_bucket_two(table->buckets[i]);
			printf("\n");
		}
	}
}

void dump_hashtable2(FILE* fp,Hash2* table){
        int i;
        for(i=0;i< table->size;i++){
                fprintf(fp,"Bucket %d:\n\n",i);
                if(table->buckets[i] != NULL){
                        dump_bucket_two(fp,table->buckets[i]);
                        fprintf(fp,"\n");
                }
        }
}

void print_hashtable2_callee(Hash2* table,char* call_num){
	int num;
	num = hash2_function(table->size,call_num);
	if(table->buckets[num] != NULL)
		print_bucket_callee(table->buckets[num],call_num);
}

void print_hashtable2_time(Hash2* table,char* call_num,int time1,int time2){
	int num;
        num = hash2_function(table->size,call_num);
        if(table->buckets[num] != NULL)
                print_time_callee(table->buckets[num],call_num,time1,time2);
}

void print_hashtable2_year(Hash2* table,char* call_num,int year1,int year2){
        int num;
        num = hash2_function(table->size,call_num);
        if(table->buckets[num] != NULL)
                print_year_callee(table->buckets[num],call_num,year1,year2);
}


void print_hashtable2_timeyear(Hash2* table,char* call_num,int time1,int time2,int year1,int year2){
        int num;
        num = hash2_function(table->size,call_num);
        if(table->buckets[num] != NULL)
                print_timeyear_callee(table->buckets[num],call_num,time1,time2,year1,year2);
}
