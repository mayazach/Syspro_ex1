#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "hash1.h"
#include "hash2.h"
#include "heap.h"

void parse_input(char* line,float config[5][3],int* sizes,myPointers* pointers);

int main(int argc, char** argv){

	char* opfile;
	char* cfile;
	char line[255];
	int table1_entries,table2_entries,bucket_size,bucket_entries,i,found;
	short oflag=0,cflag=0;
	FILE *fp;
	FILE *cfp;

	float config[5][3] = {{0,0,0.1},{1,1,0.5},{1,2,0.8},{2,1,0.2},{2,2,0.4}};
	int sizes[3];//sizes[0] = h1, sizes[1] = h2, sizes[2] = s
	myPointers pointers;
	pointers.table1 = NULL;
	pointers.table2 = NULL;
	pointers.heap = NULL;

	switch(argc){
		case 11:
		case 9:
		case 7: for(i=1;i<(argc-1);i++){
				if(!strcmp(argv[i],"-h1")){
					found = 1;
					if(argv[i+1][0] == '-'){
						printf("All flags must have a value.\n");
						return 0;
					}
					table1_entries = atoi(argv[i+1]);
					break;
				}
			}
			if(!found){
				printf("-h1 flag and its value are required.\n");
				return 0;
			}
			found = 0;
			for(i=1;i<(argc-1);i++){
                                if(!strcmp(argv[i],"-h2")){
                                        found = 1;
					if(argv[i+1][0] == '-'){
                                                printf("All flags must have a value.\n");
                                                return 0;
                                        }
					table2_entries = atoi(argv[i+1]);
                                        break;
                                }
                        }
			if(!found){
                                printf("-h2 flag and its value are required.\n");
                                return 0;
                        }
			found = 0;
                        for(i=1;i<(argc-1);i++){
                                if(!strcmp(argv[i],"-s")){
                                        found = 1;
					if(argv[i+1][0] == '-'){
                                                printf("All flags must have a value.\n");
                                                return 0;
                                        }
					bucket_size = atoi(argv[i+1]);
                                        break;
                                }
                        }
                        if(!found){
                                printf("-s flag and its value are required.\n");
                                return 0;
                        }
			break;
		default:printf("Wrong number of arguments.\n");
			return 0;
	}

	if(argc > 7){
		for(i=1;i<(argc-1);i++){
			if(!strcmp(argv[i],"-o")){
				oflag = 1;
				if(argv[i+1][0] == '-'){
                       			printf("All flags must have a value.\n");
                               		return 0;
                        	}
				opfile = argv[i+1];
			}
			if(!strcmp(argv[i],"-c")){
				cflag = 1;
				if(argv[i+1][0] == '-'){
                                        printf("All flags must have a value.\n");
                                        return 0;
                                }
				cfile = argv[i+1];
                        }
		}
		if((!oflag) && (!cflag)){
			printf("Unknown arguments.\n");
			return 0;
		}
		if((argc == 11) && !(oflag && cflag)){
			printf("Optional flags must be -o and -c\n");
			return 0;
		}
	}

	bucket_entries = bucket_size/sizeof(bucket1Entry);
	if(bucket_entries <= 1){
		printf("Not enough bytes per bucket.\n");
		exit(EXIT_FAILURE);
	}
	sizes[0] = table1_entries;
	sizes[1] = table2_entries;
	sizes[2] = bucket_entries;

	if(cflag){
		cfp = fopen(cfile,"r");
		if(cfp==NULL){
                        printf("Error opening file\n");
                        return 0;
                }
		fgets(line,255,cfp);
		for(i=0;i<5;i++){
			if(fgets(line,255,cfp)){
				config[i][0] = atoi(strtok(line,";"));
				config[i][1] = atoi(strtok(NULL,";"));
				config[i][2] = atoi(strtok(NULL,";"));
			}
		}
		fclose(cfp);
	}

	if(oflag){
		fp=fopen(opfile,"r");
		if(fp==NULL){
			printf("Error opening file\n");
			return 0;
		}
		while(fgets(line,255,fp)){
			parse_input(line,config,sizes,&pointers);
		}
		fclose(fp);
	}

	while(1){
		printf("Type a command here. Enter Q to quit, H for help.\n");
		fgets(line,255,stdin);
		line[strcspn(line,"\n")]='\0';
		if(!strcmp(line,"Q") || !strcmp(line,"q"))
			break;
		else if(!strcmp(line,"H") || !strcmp(line,"h"))
			printf("You can enter one of the following commands:\n\n1.insert [cdr-record]\n2.delete [caller-cdr-id]\n3.find [caller]\n  find [caller] [time1] [time2]\n  find [caller] [year1] [year2]\n  find [caller] [time1] [year1] [time2] [year2]\n4.lookup [callee]\n  lookup [callee] [time1] [time2]\n  lookup [callee] [year1] [year2]\n  lookup [callee] [time1] [year1] [time2] [year2]\n5.indist [caller1] [caller2]\n6.topdest [caller]\n7.top [k]\n8.bye\n9.print [hashttableX]\n10.dump [hashttableX] [filename]\n\n");
		else{
			parse_input(line,config,sizes,&pointers);
		}
	}

	if((pointers.table1) != NULL)
		destroy_hashtable1(pointers.table1);
	if((pointers.table2) != NULL)
                destroy_hashtable2(pointers.table2);
	if((pointers.heap) != NULL)
		heap_destroy(pointers.heap);

	return 0;
}

void parse_input(char* line,float config[5][3],int* sizes,myPointers* pointers){
	char *word = strtok(line," ");
	int i,option,argnum = 0;
	const char* options[]={"insert","delete","find","lookup","indist","topdest","top","bye","print","dump"};
	char* args[5];
	for(i=0;i<10;i++){
		if(!strcmp(word,options[i])){
			option=i;
			break;
		}
	}
	if(i >= 10){
		if(!strncmp(word,"bye",3))
			option = 7;
		else{
			printf("No '%s' command known.\n",word);
			return;
		}
	}
	while((word = strtok(NULL, " "))){
		argnum++;
		if(argnum > 5){
			printf("Too many arguments in '%s'\n",line);
			return;
		}
		args[argnum-1] = word;
	}

	switch(option){
		case 0:if(argnum != 1)
			printf("'%s' takes one argument\n",options[option]);
			else
				insert_function(args[0],config,sizes,pointers);
			break;
		case 1:if(argnum != 2)
			printf("'%s' takes 2 arguments\n",options[option]);
			else
				delete_function(args[0],args[1],pointers);
			break;
		case 2:if((argnum != 1) && (argnum != 3) && (argnum != 5))
			printf("Wrong number of arguments. See help\n");
			else
				find_function(argnum,args,pointers);
                        break;
                case 3:if((argnum != 1) && (argnum !=3) && (argnum != 5))
                        printf("Wrong number of arguments. See help\n");
			else
				lookup_function(argnum,args,pointers);
                        break;
		case 4:if(argnum != 2)
                        printf("%s takes 2 arguments\n",options[option]);
			else
				indist_function(args[0],args[1],pointers);
                        break;
                case 5:if(argnum != 1)
                        printf("%s takes one argument\n",options[option]);
			else
				topdest_function(args[0],pointers);
                        break;
		case 6:if(argnum != 1)
                        printf("%s takes one argument\n",options[option]);
			else
				top_function(args[0],pointers);
                        break;
                case 7:if(argnum)
                        printf("%s does not take arguments\n",options[option]);
			else
				bye_function(pointers);
                        break;
		case 8:if(argnum != 1)
                        printf("%s takes one argument\n",options[option]);
			else
				args[0][strcspn(args[0],"\n")]='\0';
				print_function(args[0],pointers);
                        break;
                case 9:if(argnum != 2)
                        printf("%s takes 2 arguments\n",options[option]);
			else
				dump_function(args[0],args[1],pointers);
                        break;
		default: printf("Invalid command.\n");
	}
}
