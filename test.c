#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list2.c"
#include "hash1.h"

int main(){

	calleeInfo test;
	char* filename = "input1.txt";
	FILE* fp = fopen(filename,"r");
	char* word;
	char line[255];
	int i;
	calleeList* mylist;
        mylist = create_callee_list(3);
	char** indist;
	char number[15];
	//Hash1* mytable = create_hashtable1(5,3);

	while(fgets(line,255,fp)){
		word = strtok(line," ");
		if(!strcmp(word,"insert")){
			word = strtok(NULL," ");
			strcpy(test.call_id,strtok(word,";"));
			strcpy(number,strtok(NULL,";"));
			strcpy(test.caller_num,strtok(NULL,";"));
			strcpy(test.date,strtok(NULL,";"));
			strcpy(test.time,strtok(NULL,";"));
			test.duration = atoi(strtok(NULL,";"));
			test.type = atoi(strtok(NULL,";"));
			test.tarrif = atoi(strtok(NULL,";"));
			test.fault_condition = atoi(strtok(NULL," "));
			add_callee_list(mylist,test);
		}
	}
	fclose(fp);
//	topdest_bucket_one(mylist,"030-2953544656");
	indist = get_callers(mylist,"030-2953544656");
	i = 0;
	while(indist[i] != NULL){
		printf("%s\n",indist[i]);
		free(indist[i]);
		i++;
	}
	free(indist);
//	strcpy(number,"030-2953544656");
//	print_bucket_caller(mylist,"030-2953544656");
	//print_timeyear_caller(mylist,number,1200,2000,19800101,19900101);
//	indist = get_callers(mylist,"053-2041182470");
//	size = 0;
//	while(indist[size] != NULL){
//		size++;
//	}
//	for(i=0;i<(size-1);i++)
//		free(indist[i]);
//	free(indist);
//	print_callee_list(mylist);
//	topdest_caller_list(mylist);
//	delete_caller_list(mylist,"BD0D7075BC");
//	delete_caller_list(mylist,"D87BFDF0F1");
//	printf("After delete:\n");
//	print_caller_list(mylist);
//	printtimeyear_callee_list(mylist,700,1000,19800101,19950101);
//	destroy_hashtable1(mytable);
	destroy_callee_list(mylist);
	return 0;
}
