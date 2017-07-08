#ifndef HEAP
#define HEAP

typedef struct{
	char caller_id[15];
	float spent;
}heapData;

typedef struct heapNode heapNode;

struct heapNode{
	heapData caller_entry;
	heapNode* left;
	heapNode* right;
	heapNode* parent;
};

typedef struct frontierNode frontierNode;

struct frontierNode{
	heapNode* elem;
	heapNode* parent;
	char dir;
	frontierNode* next;
};

float calculate_cost(float config[5][3],int type,int tarrif,int duration);

frontierNode* create();

short empty(frontierNode* head);

void destroy(frontierNode* head);

void push(heapNode* leaf,heapNode* parent,char dir,frontierNode* head);

heapNode* pop(frontierNode** head);

heapNode* pop_max(frontierNode** head);

heapNode* heap_create();

void heap_destroy(heapNode* head);

void max_heapify(heapNode* leaf);

void heap_add(heapNode* root,heapData call);

float heap_total(heapNode* root);

void heap_print(heapNode* root);

void heap_topk(heapNode* root,int k);

#endif
