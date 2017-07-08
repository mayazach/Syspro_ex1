#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"
#include "heap.h"
#include "list1.h"
#include "list2.h"
#include "hash1.h"
#include "hash2.h"

void insert_function(char* cdr_record,float config[5][3],int* sizes,myPointers* pointers){
	callerInfo origin;
	calleeInfo dest;
	heapData cost;
	char* buf[MAX_LENGTH];
	int count;
	if(buf[0] = strtok(cdr_record,";"))
		for(count=1;count<9;count++){
			buf[count]=strtok(NULL,";");
			if(buf[count] == NULL){
				printf("Ierror: wrong CDR format.\n");
				return;
			}
		}
	else{
		printf("Ierror: wrong CDR format.\n");
		return;
	}
	strcpy(origin.call_id,buf[0]);
	strcpy(origin.callee_num,buf[2]);
	strcpy(origin.date,buf[3]);
	strcpy(origin.time,buf[4]);
	origin.duration = atoi(buf[5]);
	origin.type = atoi(buf[6]);
	origin.tarrif = atoi(buf[7]);
	origin.fault_condition = atoi(buf[8]);

	if((pointers->table1) == NULL){
		pointers->table1 = create_hashtable1(sizes[0],sizes[2]);
		add_hashtable1(pointers->table1,buf[1],origin);
	}
	else
		add_hashtable1(pointers->table1,buf[1],origin);

	strcpy(dest.call_id,buf[0]);
        strcpy(dest.caller_num,buf[1]);
        strcpy(dest.date,buf[3]);
        strcpy(dest.time,buf[4]);
        dest.duration = atoi(buf[5]);
        dest.type = atoi(buf[6]);
        dest.tarrif = atoi(buf[7]);
        dest.fault_condition = atoi(buf[8]);

	if((pointers->table2) == NULL){
                pointers->table2 = create_hashtable2(sizes[1],sizes[2]);
                add_hashtable2(pointers->table2,buf[2],dest);
        }
        else
                add_hashtable2(pointers->table2,buf[2],dest);

	strcpy(cost.caller_id,buf[1]);
	cost.spent = calculate_cost(config,atoi(buf[6]),atoi(buf[7]),atoi(buf[5]));
	if((pointers->heap) == NULL){
		pointers->heap = heap_create();
		heap_add(pointers->heap,cost);
	}
	else
		heap_add(pointers->heap,cost);
}

void delete_function(char* caller,char* cdr_id,myPointers* pointers){
	if((pointers->table1) != NULL){
		delete_hashtable1(pointers->table1,caller,cdr_id);
	}
	else
		printf("DError: Hashtable has been freed or not created yet.");
}

void find_function(int argnum,char** my_args,myPointers* pointers){
	int time1,time2,year1,year2;
	int i;
	char buf[9];
	if(argnum == 1){
		if((pointers->table1) != NULL)
			print_hashtable1_caller(pointers->table1,my_args[0]);
	}
	else if(argnum == 3){
		if(strlen(my_args[1]) == 5){
			buf[0] = my_args[1][0];
			buf[1] = my_args[1][1];
			buf[2] = my_args[1][3];
			buf[3] = my_args[1][4];
			buf[4]='\0';
			time1 = atoi(buf);
			buf[0] = my_args[2][0];
                        buf[1] = my_args[2][1];
                        buf[2] = my_args[2][3];
                        buf[3] = my_args[2][4];
                        buf[4]='\0';
			time2 = atoi(buf);
			if((pointers->table1) != NULL)
                        	print_hashtable1_time(pointers->table1,my_args[0],time1,time2);
		}
		else {
			for(i = 4;i<=7;i++){
				buf[i-4] = my_args[1][i];
			}
			buf[4] = my_args[1][2];
			buf[5] = my_args[1][3];
			buf[6] = my_args[1][0];
			buf[7] = my_args[1][1];
			buf[8] = '\0';
			year1 = atoi(buf);
			for(i = 4;i<=7;i++){
                                buf[i-4] = my_args[2][i];
                        }
                        buf[4] = my_args[2][2];
                        buf[5] = my_args[2][3];
                        buf[6] = my_args[2][0];
                        buf[7] = my_args[2][1];
			year2 = atoi(buf);
			if((pointers->table1) != NULL)
                                print_hashtable1_year(pointers->table1,my_args[0],year1,year2);
		}
	}
	else{
		buf[0] = my_args[1][0];
                buf[1] = my_args[1][1];
                buf[2] = my_args[1][3];
                buf[3] = my_args[1][4];
                buf[4]='\0';
                time1 = atoi(buf);
		for(i = 4;i<=7;i++){
                	buf[i-4] = my_args[2][i];
                }
                buf[4] = my_args[2][2];
                buf[5] = my_args[2][3];
                buf[6] = my_args[2][0];
                buf[7] = my_args[2][1];
                buf[8] = '\0';
		year1 = atoi(buf);
		buf[0] = my_args[3][0];
                buf[1] = my_args[3][1];
                buf[2] = my_args[3][3];
                buf[3] = my_args[3][4];
                buf[4]='\0';
                time2 = atoi(buf);
		for(i = 4;i<=7;i++){
                        buf[i-4] = my_args[4][i];
                }
                buf[4] = my_args[4][2];
                buf[5] = my_args[4][3];
                buf[6] = my_args[4][0];
                buf[7] = my_args[4][1];
                buf[8] = '\0';
                year2 = atoi(buf);
		if((pointers->table1) != NULL)
                                print_hashtable1_timeyear(pointers->table1,my_args[0],time1,time2,year1,year2);
	}
}

void lookup_function(int argnum,char** my_args,myPointers* pointers){
	int time1,time2,year1,year2;
        int i;
        char buf[9];
        if(argnum == 1){
                if((pointers->table2) != NULL)
                        print_hashtable2_callee(pointers->table2,my_args[0]);
        }

        else if(argnum == 3){
                if(strlen(my_args[1]) == 5){
                        buf[0] = my_args[1][0];
                        buf[1] = my_args[1][1];
                        buf[2] = my_args[1][3];
                        buf[3] = my_args[1][4];
                        buf[4]='\0';
                        time1 = atoi(buf);
                        buf[0] = my_args[2][0];
                        buf[1] = my_args[2][1];
                        buf[2] = my_args[2][3];
                        buf[3] = my_args[2][4];
                        buf[4]='\0';
                        time2 = atoi(buf);
			if((pointers->table2) != NULL)
                        	print_hashtable2_time(pointers->table2,my_args[0],time1,time2);
                }
                else {
                        for(i = 4;i<=7;i++){
                                buf[i-4] = my_args[1][i];
                        }
                        buf[4] = my_args[1][2];
                        buf[5] = my_args[1][3];
                        buf[6] = my_args[1][0];
                        buf[7] = my_args[1][1];
                        buf[8] = '\0';
                        year1 = atoi(buf);
                        for(i = 4;i<=7;i++){
                                buf[i-4] = my_args[2][i];
                        }
                        buf[4] = my_args[2][2];
                        buf[5] = my_args[2][3];
                        buf[6] = my_args[2][0];
                        buf[7] = my_args[2][1];
                        year2 = atoi(buf);
			if((pointers->table2) != NULL)
                                print_hashtable2_year(pointers->table2,my_args[0],year1,year2);
	        }
	}
        else{
                buf[0] = my_args[1][0];
                buf[1] = my_args[1][1];
                buf[2] = my_args[1][3];
                buf[3] = my_args[1][4];
                buf[4]='\0';
                time1 = atoi(buf);
                for(i = 4;i<=7;i++){
                        buf[i-4] = my_args[2][i];
                }
                buf[4] = my_args[2][2];
                buf[5] = my_args[2][3];
                buf[6] = my_args[2][0];
                buf[7] = my_args[2][1];
                buf[8] = '\0';
                year1 = atoi(buf);
                buf[0] = my_args[3][0];
                buf[1] = my_args[3][1];
                buf[2] = my_args[3][3];
                buf[3] = my_args[3][4];
                buf[4]='\0';
		time2 = atoi(buf);
                for(i = 4;i<=7;i++){
                        buf[i-4] = my_args[4][i];
                }
                buf[4] = my_args[4][2];
                buf[5] = my_args[4][3];
                buf[6] = my_args[4][0];
                buf[7] = my_args[4][1];
                buf[8] = '\0';
                year2 = atoi(buf);
		if((pointers->table2) != NULL)
                	print_hashtable2_timeyear(pointers->table2,my_args[0],time1,time2,year1,year2);
        }
}


void indist_function(char* caller1, char* caller2,myPointers* pointers){
	char** callers1= NULL;
	char** callees1= NULL;
	char** callers2= NULL;
	char** callees2= NULL;
	char** contacts1= NULL;
	char** contacts2= NULL;
	short found=1;
	int common = 0;
	int i,j,size1,size2,num;
	if(((pointers->table1) == NULL) || ((pointers->table2) == NULL)){
		printf("No indist found\n.");
		return;
	}
	num = hash1_function(pointers->table1->size,caller1);
	callers1 = callees_bucket_one(pointers->table1->buckets[num],caller1,caller2);
	num = hash2_function(pointers->table2->size,caller1);
        callees1 = callers_bucket_two(pointers->table2->buckets[num],caller1,caller2);
	num = hash1_function(pointers->table1->size,caller2);
        callers2 = callees_bucket_one(pointers->table1->buckets[num],caller2,caller1);
	num = hash2_function(pointers->table2->size,caller2);
        callees2 = callers_bucket_two(pointers->table2->buckets[num],caller2,caller1);

	/*
	if(callers1 != NULL){
		puts("Callers1:");
		i=0;
		while(callers1[i] != NULL){
			printf("%s\n",callers1[i]);
			i++;
		}
	}
	if(callees1 != NULL){
                puts("Callees1:");
                i=0;
                while(callees1[i] != NULL){
                        printf("%s\n",callees1[i]);
                        i++;
                }
        }
	if(callers2 != NULL){
                puts("Callers2:");
                i=0;
                while(callers2[i] != NULL){
                        printf("%s\n",callers2[i]);
                        i++;
                }
        }
        if(callees2 != NULL){
                puts("Callees2:");
                i=0;
                while(callees2[i] != NULL){
                        printf("%s\n",callees2[i]);
                        i++;
                }
        }
	*/

	if(((callers1 == NULL) && (callees1 == NULL)) || ((callers2 == NULL) && (callees2 == NULL)))
		found = 0;

	if(found){
		i=0;
		size1 = 0;
		if(callers1 != NULL)
		while(callers1[i] != NULL){
			size1++;
			i++;
		}
		i=0;
		if(callees1 != NULL)
		while(callees1[i] != NULL){
                        size1++;
                        i++;
                }
		i=0;
		size2=0;
		if(callers2 != NULL)
		while(callers2[i] != NULL){
                        size2++;
                        i++;
                }
		i=0;
		if(callees2 != NULL)
		while(callees2[i] != NULL){
                        size2++;
                        i++;
                }
		contacts1 = malloc((size1+1)*(sizeof(char*)));
		if(contacts1 == NULL){
			printf("Memory allocation error.\n");
			exit(EXIT_FAILURE);
		}
		contacts1[size1] = NULL;
		for(i=0;i<size1;i++){
			contacts1[i] = malloc(15*sizeof(char*));
			if(contacts1[i] == NULL){
				printf("Memory allocation error.\n");
				exit(EXIT_FAILURE);
			}
		}
		contacts2 = malloc((size2+1)*(sizeof(char*)));
                if(contacts2 == NULL){
                        printf("Memory allocation error.\n");
                        exit(EXIT_FAILURE);
                }
                contacts2[size2] = NULL;
                for(i=0;i<size2;i++){
                        contacts2[i] = malloc(15*sizeof(char*));
                        if(contacts2[i] == NULL){
                                printf("Memory allocation error.\n");
                                exit(EXIT_FAILURE);
                        }
                }
		i=0;
		j=0;
		if(callers1 != NULL)
			while(callers1[i] != NULL){
				strcpy(contacts1[j],callers1[i]);
				i++;
				j++;
			}
		i=0;
                if(callees1 != NULL)
                        while(callees1[i] != NULL){
                                strcpy(contacts1[j],callees1[i]);
                                i++;
				j++;
                        }
		i=0;
                j=0;
                if(callers2 != NULL)
                        while(callers2[i] != NULL){
                                strcpy(contacts2[j],callers2[i]);
                                i++;
                                j++;
                        }
                i=0;
                if(callees2 != NULL)
                        while(callees2[i] != NULL){
                                strcpy(contacts2[j],callees2[i]);
                                i++;
                                j++;
                        }
		qsort(contacts1,size1,sizeof(char*),cmpstringp);
		for(i=1;i<size1;i++)
			if(!strcmp(contacts1[i],contacts1[i-1]))
				strcpy(contacts1[i-1],"\0");
		qsort(contacts2,size2,sizeof(char*),cmpstringp);
		for(i=1;i<size2;i++)
                        if(!strcmp(contacts2[i],contacts2[i-1]))
                                strcpy(contacts2[i-1],"\0");
		for(i=0;i<size1;i++){
			if(strcmp(contacts1[i],"\0")){
				for(j=0;j<size2;j++)
					if(!strcmp(contacts1[i],contacts2[j])){
						common++;
						break;
					}
				if(j==size2)
					strcpy(contacts1[i],"\0");
			}
		}
		if(!common)
			printf("No indist found.\n");
		else{
			for(i=0;i<size1;i++)
				if(strcmp(contacts1[i],"\0"))
					printf("%s\n",contacts1[i]);
		}
	}
	else
		printf("No indist found.\n");

	if(callers1 != NULL){
		i=0;
		while(callers1[i] != NULL){
			free(callers1[i]);
			i++;
		}
		free(callers1);
	}
	if(callees1 != NULL){
                i=0;
                while(callees1[i] != NULL){
                        free(callees1[i]);
                        i++;
                }
                free(callees1);
        }
	if(callers2 != NULL){
                i=0;
                while(callers2[i] != NULL){
                        free(callers2[i]);
                        i++;
                }
                free(callers2);
        }
	if(callees2 != NULL){
                i=0;
                while(callees2[i] != NULL){
                        free(callees2[i]);
                        i++;
                }
                free(callees2);
        }
	if(contacts1 != NULL){
                i=0;
                while(contacts1[i] != NULL){
                        free(contacts1[i]);
                        i++;
                }
                free(contacts1);
        }
	if(contacts2 != NULL){
                i=0;
                while(contacts2[i] != NULL){
                        free(contacts2[i]);
                        i++;
                }
                free(contacts2);
        }
}


void topdest_function(char* caller,myPointers* pointers){
	if((pointers->table1) != NULL){
                topdest_hashtable1(pointers->table1,caller);
        }
	else
		puts("No calls found.");
}


void top_function(char* k,myPointers* pointers){
	int topk = atoi(k);
	if((pointers->heap) != NULL)
		heap_topk(pointers->heap,topk);
	else
		puts("No calls found.");
}


void bye_function(myPointers* pointers){
	if((pointers->table1) != NULL){
                destroy_hashtable1(pointers->table1);
		pointers->table1 = NULL;
	}
        if((pointers->table2) != NULL){
                destroy_hashtable2(pointers->table2);
		pointers->table2 = NULL;
	}
	if((pointers->heap) != NULL){
                heap_destroy(pointers->heap);
                pointers->heap = NULL;
        }

}


void print_function(char* hashtableX,myPointers* pointers){
	if(!strncmp(hashtableX,"hashtable1",10))
		if((pointers->table1) == NULL)
			printf("Hashtable1 is empty.\n");
		else
			print_hashtable1(pointers->table1);
	else if(!strncmp(hashtableX,"hashtable2",10))
		if((pointers->table2) == NULL)
                        printf("Hashtable2 is empty.\n");
                else
                        print_hashtable2(pointers->table2);
	else
		printf("No such hashtable\n");
        return;
}


void dump_function(char* hashtableX,char* filename,myPointers* pointers){
	FILE* fp;
	char buf[255];
	filename[strcspn(filename,"\r")]='\0';
	strcpy(buf,filename);
	if(!strcmp(hashtableX,"hashtable1")){
                if((pointers->table1) == NULL)
                        printf("Hashtable1 is empty.\n");
                else{
                        fp = fopen(buf,"w+");
			//fp = fopen("hash1.txt","w+");
		        if(fp == NULL){
                		printf("Error creating file\n");
                		return;
        		}
			dump_hashtable1(fp,pointers->table1);
			fclose(fp);
		}
	}
        else if(!strcmp(hashtableX,"hashtable2")){
                if((pointers->table2) == NULL)
                        printf("Hashtable2 is empty.\n");
                else{
                        fp = fopen(buf,"w+");
			//fp = fopen("hash2.txt","w+");
                        if(fp == NULL){
                                printf("Error creating file\n");
                                return;
                        }
                        dump_hashtable2(fp,pointers->table2);
                        fclose(fp);
                }
	}
        else{
                printf("No such hashtable\n");
		return;
	}
	fp = fopen(filename,"w+");
	if(fp == NULL){
		printf("Error creating file\n");
        	return;
	}
	fclose(fp);
}

