#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list2.h"

static int cmpstringp(const void * p1, const void * p2){
	return strcmp(* (char * const *) p1,*(char * const *) p2);
}

void print_callee_info(calleeInfo callee){
	printf("%s\t%s\t%c%c-%c%c-%c%c%c%c\t%s\t%d\t%d\t%d\t%d\n",callee.call_id,callee.caller_num,callee.date[0],callee.date[1],callee.date[2],callee.date[3],callee.date[4],callee.date[5],callee.date[6],callee.date[7],callee.time,callee.duration,callee.type,callee.tarrif,callee.fault_condition);
        return;
}

void dump_callee_info(FILE* fp,calleeInfo callee){
        fprintf(fp,"%s\t%s\t%c%c-%c%c-%c%c%c%c\t%s\t%d\t%d\t%d\t%d\n",callee.call_id,callee.caller_num,callee.date[0],callee.date[1],callee.date[2],callee.date[3],callee.date[4],callee.date[5],callee.date[6],callee.date[7],callee.time,callee.duration,callee.type,callee.tarrif,callee.fault_condition);
}

calleeList* create_callee_list(int size){
        int i;
        calleeList* head = NULL;
        head = malloc(sizeof(calleeList));
        if(head == NULL){
                printf("Error creating list for callee data.\n");
                return NULL;
        }
        head->array_size = size;
        head->in_array = 0;
        head->next = NULL;
        head->callee_array = malloc(size*sizeof(calleeInfo));
        if(head->callee_array == NULL){
                return NULL;
        }
        for(i=0;i<size;i++){
                strcpy(head->callee_array[i].call_id,"\0");
        }
        return head;

}

void add_callee_list(calleeList* head,calleeInfo entry){
        calleeList* temp = head;
        int i;
        while(temp != NULL){
                if(temp->in_array < temp->array_size){
                        for(i = 0;i < temp->array_size;i++)
                                if(!strcmp(temp->callee_array[i].call_id,"\0")){
                                        strcpy(temp->callee_array[i].call_id,entry.call_id);
                                        strcpy(temp->callee_array[i].caller_num,entry.caller_num);
                                        strcpy(temp->callee_array[i].date,entry.date);
                                        strcpy(temp->callee_array[i].time,entry.time);
                                        temp->callee_array[i].duration = entry.duration;
                                        temp->callee_array[i].type = entry.type;
                                        temp->callee_array[i].tarrif = entry.tarrif;
                                        temp->callee_array[i].fault_condition = entry.fault_condition;
                                        (temp->in_array)++;
                                        return;
                                }
                }
                else{
                        if(temp->next == NULL){
                                temp->next = malloc(sizeof(calleeList));
                                if(temp->next == NULL){
                                        printf("Error allocating memory.\n");
                                        exit(EXIT_FAILURE);
                                }
                                temp->next->array_size = temp->array_size;
                                temp->next->in_array = 0;
                                temp->next->next = NULL;
                                temp->next->callee_array = malloc((temp->array_size)*sizeof(calleeInfo));
                                if(temp->next->callee_array == NULL){
                                        printf("Error allocating memory.\n");
                                        exit(EXIT_FAILURE);
                                }
                                for(i=0;i < temp->array_size;i++){
                                        strcpy(temp->next->callee_array[i].call_id,"\0");
                                }
                                temp=temp->next;
                        }
                        else
                                temp = temp->next;
                }
        }
}

void destroy_callee_list(calleeList* list){
        calleeList* temp;
        while(list != NULL){
                temp = list->next;
                free(list->callee_array);
                free(list);
                list = temp;
        }
}

void print_callee_list(calleeList* list){
        calleeList* temp = list;
        int i;
	int found = 0;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->callee_array[i].call_id,"\0")){
                                print_callee_info(temp->callee_array[i]);
				found = 1;
			}
                temp=temp->next;
        }
	if(!found)
                puts("No CDRs found.");
}

void dump_callee_list(FILE* fp,calleeList* list){
        calleeList* temp = list;
        int i;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->callee_array[i].call_id,"\0"))
                                dump_callee_info(fp,temp->callee_array[i]);
                temp=temp->next;
        }
}

void printtime_callee_list(calleeList* list,int time1, int time2){
	calleeList* temp = list;
        int i,time;
        char buf[9];
	short found = 0;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->callee_array[i].call_id,"\0")){
                                buf[0] = temp->callee_array[i].time[0];
                                buf[1] = temp->callee_array[i].time[1];
                                buf[2] = temp->callee_array[i].time[3];
                                buf[3] = temp->callee_array[i].time[4];
                                buf[4]='\0';
                                time = atoi(buf);
                                if((time >= time1) && (time <= time2)){
                                        print_callee_info(temp->callee_array[i]);
					found = 1;
				}
                        }
                temp=temp->next;
        }
	if(!found)
                puts("No CDRs found.");
}

void printyear_callee_list(calleeList* list,int year1, int year2){
	calleeList* temp = list;
        int i,j,year;
        char buf[9];
	short found = 0;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->callee_array[i].call_id,"\0")){
                                for(j = 4;j<=7;j++){
                                        buf[j-4] = temp->callee_array[i].date[j];
                                }
                                buf[4] = temp->callee_array[i].date[2];
                                buf[5] = temp->callee_array[i].date[3];
                                buf[6] = temp->callee_array[i].date[0];
                                buf[7] = temp->callee_array[i].date[1];
                                buf[8] = '\0';
                                year = atoi(buf);
                                if((year >= year1) && (year <= year2)){
                                        print_callee_info(temp->callee_array[i]);
					found = 1;
				}
                        }
                temp=temp->next;
        }
	if(!found)
                puts("No CDRs found.");
}

void printtimeyear_callee_list(calleeList* list,int time1, int time2,int year1,int year2){
	calleeList* temp = list;
        int i,j,time,year;
        char buf[9];
	short found = 0;
	while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->callee_array[i].call_id,"\0")){
                                buf[0] = temp->callee_array[i].time[0];
                                buf[1] = temp->callee_array[i].time[1];
                                buf[2] = temp->callee_array[i].time[3];
                                buf[3] = temp->callee_array[i].time[4];
                                buf[4]='\0';
                                time = atoi(buf);
                                for(j = 4;j<=7;j++){
                                        buf[j-4] = temp->callee_array[i].date[j];
                                }
                                buf[4] = temp->callee_array[i].date[2];
                                buf[5] = temp->callee_array[i].date[3];
                                buf[6] = temp->callee_array[i].date[0];
                                buf[7] = temp->callee_array[i].date[1];
                                buf[8] = '\0';
                                year = atoi(buf);
                                if((time >= time1) && (time <= time2) && (year >= year1) && (year <= year2)){
                                        print_callee_info(temp->callee_array[i]);
					found = 1;
				}
                        }
                temp=temp->next;
        }
	if(!found)
                puts("No CDRs found.");
}

char** get_callers(calleeList* list,char* other_callee){

	char** result;
	int i,count = 0,index=0;
	int distinct = 0;
	calleeList* temp = list;
	while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->callee_array[i].call_id,"\0")){
                                if(strncmp(temp->callee_array[i].caller_num,other_callee,14))
					count++;
			}
                temp=temp->next;
        }
	if(count == 0)
		return NULL;
	char** all_calls = malloc(count*sizeof(char*));
	if(all_calls == NULL){
		printf("Memory allocation error.\n");
		exit(EXIT_FAILURE);
	}
	for(i=0;i<count;i++){
		all_calls[i] = malloc(15 * sizeof(char));
		if(all_calls[i] == NULL){
			printf("Memory allocation error.\n");
			exit(EXIT_FAILURE);
		}
	}

	temp = list;
	while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->callee_array[i].call_id,"\0")){
				if(strncmp(temp->callee_array[i].caller_num,other_callee,14)){
					strcpy(all_calls[index],temp->callee_array[i].caller_num);
					index++;
				}
			}
                temp=temp->next;
        }

	qsort(all_calls,count,sizeof(char*),cmpstringp);

	if(count > 0)
		distinct = 1;
	index = 1;
	for(i=1;i<count;i++){
		if(strncmp(all_calls[i-1],all_calls[i],14))
			distinct++;
	}

	if(distinct == 0)
		return NULL;
	result = malloc((distinct+1) * sizeof(char*));
	if(result == NULL){
		printf("Memory allocation error.\n");
		exit(EXIT_FAILURE);
	}
	for(i=0;i<(distinct);i++){
		result[i] = malloc(15 * sizeof(char));
		if(result[i] == NULL){
			printf("Memory allocation error.\n");
			exit(EXIT_FAILURE);
		}
	}

	if(count)
		strcpy(result[0],all_calls[0]);

	for(i=1;i<count;i++){
                if(strncmp(all_calls[i],all_calls[i-1],14)){
                        strcpy(result[index],all_calls[i]);
			index++;
		}
        }


	result[distinct] = NULL;

	for(i=0;i<count;i++)
		free(all_calls[i]);
	free(all_calls);

	return result;
}
