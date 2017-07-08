#ifndef LIST1
#define LIST1

#define MAX_LENGTH 20

typedef struct{
	char call_id[MAX_LENGTH];
	char callee_num[15];
	char date[9];
	char time[6];
	int  duration;
	short type;
	short tarrif;
	int fault_condition;
}callerInfo;

typedef struct callerList callerList;

struct callerList{
	callerInfo* caller_array;
	int array_size;
	int in_array;
	callerList* next;
};

static int cmpstringp(const void * p1, const void * p2){
        return strcmp(* (char * const *) p1,*(char * const *) p2);
}

void print_caller_info(callerInfo caller);

void dump_caller_info(FILE* fp,callerInfo caller);

callerList* create_caller_list(int size);

void add_caller_list(callerList* head,callerInfo entry);

void delete_caller_list(callerList* list,char* cdr_id);

void destroy_caller_list(callerList* list);

void print_caller_list(callerList* list);

void dump_caller_list(FILE* fp,callerList* list);

void printtime_caller_list(callerList* list,int time1, int time2);

void printyear_caller_list(callerList* list,int year1, int year2);

void printtimeyear_caller_list(callerList* list,int time1, int time2,int year1,int year2);

void topdest_caller_list(callerList* list);

char** get_callees(callerList* list,char* other_caller);

#endif
