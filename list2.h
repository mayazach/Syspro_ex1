#ifndef LIST2
#define LIST2

#define MAX_LENGTH 20

typedef struct{
        char call_id[MAX_LENGTH];
        char caller_num[15];
        char date[9];
        char time[6];
        int  duration;
        short type;
        short tarrif;
        int fault_condition;
}calleeInfo;

typedef struct calleeList calleeList;

struct calleeList{
        calleeInfo* callee_array;
        int array_size;
	int in_array;
        calleeList* next;
};


void print_callee_info(calleeInfo callee);

void dump_callee_info(FILE* fp,calleeInfo callee);

calleeList* create_callee_list(int size);

void add_callee_list(calleeList* head,calleeInfo entry);

void destroy_callee_list(calleeList* list);

void print_callee_list(calleeList* list);

void dump_callee_list(FILE* fp,calleeList* list);

void printtime_callee_list(calleeList* list,int time1, int time2);

void printyear_callee_list(calleeList* list,int year1, int year2);

void printtimeyear_callee_list(calleeList* list,int time1, int time2,int year1,int year2);

char** get_callers(calleeList* list,char* other_callee);

#endif

