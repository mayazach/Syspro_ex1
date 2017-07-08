#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list1.h"


void print_caller_info(callerInfo caller){
	printf("%s\t%s\t%c%c-%c%c-%c%c%c%c\t%s\t%d\t%d\t%d\t%d\n",caller.call_id,caller.callee_num,caller.date[0],caller.date[1],caller.date[2],caller.date[3],caller.date[4],caller.date[5],caller.date[6],caller.date[7],caller.time,caller.duration,caller.type,caller.tarrif,caller.fault_condition);
	return;
}

void dump_caller_info(FILE* fp,callerInfo caller){
	fflush(fp);
	fprintf(fp,"%s\t%s\t%c%c-%c%c-%c%c%c%c\t%s\t%d\t%d\t%d\t%d\n",caller.call_id,caller.callee_num,caller.date[0],caller.date[1],caller.date[2],caller.date[3],caller.date[4],caller.date[5],caller.date[6],caller.date[7],caller.time,caller.duration,caller.type,caller.tarrif,caller.fault_condition);

}

callerList* create_caller_list(int size){
	int i;
	callerList* head = NULL;
	head = malloc(sizeof(callerList));
	if(head == NULL){
		printf("Error creating list for caller data.\n");
		return NULL;
	}
	head->array_size = size;
	head->in_array = 0;
	head->next = NULL;
	head->caller_array = malloc(size*sizeof(callerInfo));
	if(head->caller_array == NULL){
		return NULL;
	}
	for(i=0;i<size;i++){
		strcpy(head->caller_array[i].call_id,"\0");
	}
	return head;

}

void add_caller_list(callerList* head,callerInfo entry){
	callerList* temp = head;
	int i;
	while(temp != NULL){
		if(temp->in_array < temp->array_size){
			for(i = 0;i < temp->array_size;i++)
				if(!strcmp(temp->caller_array[i].call_id,"\0")){
					strcpy(temp->caller_array[i].call_id,entry.call_id);
					strcpy(temp->caller_array[i].callee_num,entry.callee_num);
					strcpy(temp->caller_array[i].date,entry.date);
					strcpy(temp->caller_array[i].time,entry.time);
					temp->caller_array[i].duration = entry.duration;
					temp->caller_array[i].type = entry.type;
					temp->caller_array[i].tarrif = entry.tarrif;
					temp->caller_array[i].fault_condition = entry.fault_condition;
					(temp->in_array)++;
					return;
				}
		}
		else{
			if(temp->next == NULL){
				temp->next = malloc(sizeof(callerList));
				if(temp->next == NULL){
	                		printf("Error allocating memory.\n");
        	        		exit(EXIT_FAILURE);
        			}
				temp->next->array_size = temp->array_size;
			        temp->next->in_array = 0;
        			temp->next->next = NULL;
        			temp->next->caller_array = malloc((temp->array_size)*sizeof(callerInfo));
        			if(temp->next->caller_array == NULL){
                			printf("Error allocating memory.\n");
					exit(EXIT_FAILURE);
        			}
        			for(i=0;i < temp->array_size;i++){
                			strcpy(temp->next->caller_array[i].call_id,"\0");
        			}
				temp=temp->next;
			}
			else
				temp = temp->next;
		}
	}
}

void destroy_caller_list(callerList* list){
	callerList* temp;
	while(list != NULL){
		temp = list->next;
		free(list->caller_array);
		free(list);
		list = temp;
	}
}

void print_caller_list(callerList* list){
	callerList* temp = list;
	int i;
	short found = 0;
	while(temp != NULL){
		for(i=0;i < temp->array_size;i++)
			if(strcmp(temp->caller_array[i].call_id,"\0")){
				print_caller_info(temp->caller_array[i]);
				found = 1;
			}
		temp=temp->next;
	}
	if(!found)
                puts("No CDRs found.");
}

void dump_caller_list(FILE* fp,callerList* list){
	callerList* temp = list;
        int i;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->caller_array[i].call_id,"\0"))
                                dump_caller_info(fp,temp->caller_array[i]);
                temp=temp->next;
        }
}

void printtime_caller_list(callerList* list,int time1, int time2){
	callerList* temp = list;
        int i,time;
	char buf[9];
	short found = 0;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->caller_array[i].call_id,"\0")){
				buf[0] = temp->caller_array[i].time[0];
                        	buf[1] = temp->caller_array[i].time[1];
                        	buf[2] = temp->caller_array[i].time[3];
                        	buf[3] = temp->caller_array[i].time[4];
                        	buf[4]='\0';
				time = atoi(buf);
				if((time >= time1) && (time <= time2)){
                                	print_caller_info(temp->caller_array[i]);
					found = 1;
				}
			}
                temp=temp->next;
        }
	if(!found)
		puts("No CDRs found.");
}

void printyear_caller_list(callerList* list,int year1, int year2){
	callerList* temp = list;
        int i,j,year;
	char buf[9];
	short found = 0;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->caller_array[i].call_id,"\0")){
				for(j = 4;j<=7;j++){
	                                buf[j-4] = temp->caller_array[i].date[j];
        	                }
                	        buf[4] = temp->caller_array[i].date[2];
                        	buf[5] = temp->caller_array[i].date[3];
                        	buf[6] = temp->caller_array[i].date[0];
                        	buf[7] = temp->caller_array[i].date[1];
                        	buf[8] = '\0';
                        	year = atoi(buf);
				if((year >= year1) && (year <= year2)){
                                	print_caller_info(temp->caller_array[i]);
					found = 1;
				}
			}
                temp=temp->next;
        }
	if(!found)
		puts("No CDRs found.");
}

void printtimeyear_caller_list(callerList* list,int time1, int time2,int year1,int year2){
	callerList* temp = list;
        int i,j,time,year;
        char buf[9];
	short found = 0;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->caller_array[i].call_id,"\0")){
                                buf[0] = temp->caller_array[i].time[0];
                                buf[1] = temp->caller_array[i].time[1];
                                buf[2] = temp->caller_array[i].time[3];
                                buf[3] = temp->caller_array[i].time[4];
                                buf[4]='\0';
                                time = atoi(buf);
				for(j = 4;j<=7;j++){
                                        buf[j-4] = temp->caller_array[i].date[j];
                                }
                                buf[4] = temp->caller_array[i].date[2];
                                buf[5] = temp->caller_array[i].date[3];
                                buf[6] = temp->caller_array[i].date[0];
                                buf[7] = temp->caller_array[i].date[1];
                                buf[8] = '\0';
                                year = atoi(buf);
                                if((time >= time1) && (time <= time2) && (year >= year1) && (year <= year2)){
                                        print_caller_info(temp->caller_array[i]);
					found = 1;
				}
                        }
                temp=temp->next;
        }
	if(!found)
                puts("No CDRs found.");
}

void delete_caller_list(callerList* list,char* cdr_id){
	callerList* temp = list;
        int i;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(!strncmp(temp->caller_array[i].call_id,cdr_id,14)){
                                strcpy(temp->caller_array[i].call_id,"\0");
				return;
			}
                temp=temp->next;
        }

}

void topdest_caller_list(callerList* list){
	callerList* temp = list;
	int index[1000] = {0};
	int i,j,num,max=0;
	int calls = 0;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->caller_array[i].call_id,"\0")){
                                num = atoi(temp->caller_array[i].callee_num);
				index[num]++;
			}
                temp=temp->next;
        }
	for(i=0;i<1000;i++){
		if(index[i] > max){
			max = index[i];
			num = i;
		}
	}
	for(j=0;j<1000;j++){
		calls = 0;
		if(index[j] == max){
			temp = list;
			while(temp != NULL){
				for(i=0;i < temp->array_size;i++)
					if(strncmp(temp->caller_array[i].call_id,"\0",14)){
						if(atoi(temp->caller_array[i].callee_num) == j)
							calls++;
					}
				temp = temp->next;
			}
			if(j < 10)
				printf("Country code: 00%d, Calls made: %d\n",j,calls);
			else if(num < 100)
				printf("Country code: 0%d, Calls made:  %d\n",j,calls);
			else
				printf("Country code: %d, Calls made:  %d\n",j,calls);
		}
	}
	if(!max)
		puts("No calls found.");
}

char** get_callees(callerList* list,char* other_caller){

        char** result;
        int i,count = 0,index=0;
        int distinct = 0;
        callerList* temp = list;
        while(temp != NULL){
                for(i=0;i < temp->array_size;i++)
                        if(strcmp(temp->caller_array[i].call_id,"\0")){
                                if(strncmp(temp->caller_array[i].callee_num,other_caller,14))
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
                        if(strcmp(temp->caller_array[i].call_id,"\0")){
                                if(strncmp(temp->caller_array[i].callee_num,other_caller,14)){
                                        strcpy(all_calls[index],temp->caller_array[i].callee_num);
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

