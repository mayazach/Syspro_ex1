#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

float calculate_cost(float config[5][3],int type,int tarrif,int duration){
	int i;
	if((config[0][0] == type) && (config[0][1] == tarrif))
		return config[0][2];
	for(i=1;i<5;i++)
		if((config[i][0] == type) && (config[i][1] == tarrif))
			return (config[i][2] * duration);
}

frontierNode* create(){
        frontierNode* head = NULL;
        head = malloc(sizeof(frontierNode));
        if(head == NULL){
                printf("Memory allocation error.\n");
                exit(EXIT_FAILURE);
        }
        head->next = NULL;
	head->parent = NULL;
        head->elem = NULL;
        return head;
}

short empty(frontierNode* head){
	if(((head->elem) == NULL) && ((head->parent) == NULL))
		return 1;
	else
		return 0;
}

void destroy(frontierNode* head){
	frontierNode* temp;
        while(head != NULL){
                temp = head->next;
                free(head);
                head = temp;
        }
}

void push(heapNode* leaf,heapNode* parent,char dir,frontierNode* head){
	frontierNode* temp=head;
	if((head->elem) == NULL){
		head->elem = leaf;
		head->parent = parent;
		head->dir=dir;
		return;
	}
	while(temp->next != NULL)
		temp=temp->next;
	temp->next=malloc(sizeof(frontierNode));
	if((temp->next) == NULL){
                printf("Memory allocation error.\n");
                exit(EXIT_FAILURE);
        }

	temp->next->elem = leaf;
	temp->next->parent = parent;
	temp->next->dir = dir;
	temp->next->next = NULL;
}

heapNode* pop(frontierNode** head){
	heapNode* leaf = NULL;
	frontierNode* temp;
	if(*head == NULL)
		return NULL;
	if(((*head)->next) == NULL){
		leaf = (*head)->elem;
		(*head)->elem = NULL;
		return leaf;
	}
	else{
		temp = (*head)->next;
		leaf = (*head)->elem;
		leaf->parent = (*head)->parent;
		free(*head);
		*head = temp;
		return leaf;
	}
}

heapNode* pop_max(frontierNode** head){
	float max = 0;
	heapNode* leaf = NULL;
        frontierNode* temp = *head;
	frontierNode* temp2 = NULL;
        if(*head == NULL)
                return NULL;
	if(((*head)->next) == NULL){
                leaf = (*head)->elem;
                (*head)->elem = NULL;
                return leaf;
        }
	else{
		max = (*head)->elem->caller_entry.spent;
                while(temp->next != NULL){
                	temp=temp->next;
			if(temp->elem->caller_entry.spent > max)
				max = temp->elem->caller_entry.spent;
		}
		temp = *head;
		if(temp->elem->caller_entry.spent == max){
			temp = (*head)->next;
                	leaf = (*head)->elem;
                	leaf->parent = (*head)->parent;
                	free(*head);
                	*head = temp;
                	return leaf;
		}
		while(temp->next != NULL){
                        if(temp->next->elem->caller_entry.spent == max){
                                temp2 = temp;
				temp = temp2->next;
				leaf = temp->elem;
				temp2->next = temp->next;
				free(temp);
				return leaf;
			}
                }
                return leaf;
        }
}

heapNode* heap_create(){
	heapNode* root = NULL;
	root = malloc(sizeof(heapNode));
	if(root == NULL){
		printf("Memory allocation error.\n");
                exit(EXIT_FAILURE);
	}
	root->parent = NULL;
	root->left = NULL;
	root->right = NULL;
	strcpy(root->caller_entry.caller_id,"\0");
	return root;
}

void heap_destroy(heapNode* head){
	if((head->left) != NULL)
		heap_destroy(head->left);
	if((head->right) != NULL)
                heap_destroy(head->right);
	free(head);
}

void max_heapify(heapNode* leaf){
	heapNode* temp = leaf;
	heapData temp1;
	while(((temp->parent) != NULL) && (temp->caller_entry.spent > temp->parent->caller_entry.spent)){
		strcpy(temp1.caller_id,temp->caller_entry.caller_id);
		temp1.spent = temp->caller_entry.spent;
		strcpy(temp->caller_entry.caller_id,temp->parent->caller_entry.caller_id);
		temp->caller_entry.spent = temp->parent->caller_entry.spent;
		strcpy(temp->parent->caller_entry.caller_id,temp1.caller_id);
		temp->parent->caller_entry.spent = temp1.spent;
		temp = temp->parent;
	}
}

void heap_add(heapNode* root,heapData call){
	heapNode* leaf;
	heapNode* parent;
	char dir;
	if(!strcmp(root->caller_entry.caller_id,"\0")){
		strcpy(root->caller_entry.caller_id,call.caller_id);
		root->caller_entry.spent = call.spent;
		return;
	}
	if(!strncmp(root->caller_entry.caller_id,call.caller_id,14)){
		root->caller_entry.spent += call.spent;
		return;
	}
	frontierNode* frontier = create();
	push(root->left,root,'l',frontier);
	push(root->right,root,'r',frontier);
	while(!empty(frontier)){
		parent = frontier->parent;
		dir = frontier->dir;
		leaf = pop(&frontier);
		if(leaf == NULL){
			leaf = malloc(sizeof(heapNode));
			if(leaf == NULL){
				printf("Error allocating memory.");
				exit(EXIT_FAILURE);
			}
	                strcpy(leaf->caller_entry.caller_id,call.caller_id);
        	        leaf->caller_entry.spent = call.spent;
			leaf->left = NULL;
			leaf->right = NULL;
			leaf->parent = parent;
			if(dir == 'l')
				leaf->parent->left = leaf;
			else
				leaf->parent->right = leaf;
			max_heapify(leaf);
                	break;
        	}
		if(!strncmp(leaf->caller_entry.caller_id,call.caller_id,14)){
			leaf->caller_entry.spent += call.spent;
			max_heapify(leaf);
                	break;
		}
		push(leaf->left,leaf,'l',frontier);
		push(leaf->right,leaf,'r',frontier);
	}
	destroy(frontier);
}

float heap_total(heapNode* root){
	float total = 0;
	total += root->caller_entry.spent;
	if((root->left) != NULL)
                total += heap_total(root->left);
        if((root->right) != NULL)
                total += heap_total(root->right);
	return total;
}

void heap_print(heapNode* root){
	printf("%s: %f\n",root->caller_entry.caller_id,root->caller_entry.spent);
	if((root->left) != NULL)
                heap_print(root->left);
        if((root->right) != NULL)
                heap_print(root->right);
}

void heap_topk(heapNode* root,int k){
        if(root == NULL){
		puts("No calls found.");
                return;
	}
        heapNode* temp;
        float total = heap_total(root);
        float percent = 0;
	float last_percent;
        if(k > 0){
		printf("Top %d percent of income comes from these numbers:\n",k);
		percent += (root->caller_entry.spent)*100/total;
                printf("%s: %.2f%%\n",root->caller_entry.caller_id,percent);
        }
        else
                return;
        frontierNode* max_queue = create();
        if((root->left) != NULL)
                push(root->left,NULL,'l',max_queue);//arguments 2 and 3 will not be used in this function
        if((root->right) != NULL)
                push(root->right,NULL,'l',max_queue);
        while((percent < k) && !empty(max_queue)){
		last_percent = percent;
                temp = pop_max(&max_queue);
		percent += (temp->caller_entry.spent)*100/total;
                printf("%s: %.2f%%\n",temp->caller_entry.caller_id,percent - last_percent);
                if((temp->left) != NULL)
                        push(temp->left,NULL,'l',max_queue);//arguments 2 and 3 will not be used in this function
                if((temp->right) != NULL)
                        push(temp->right,NULL,'l',max_queue);
        }
        destroy(max_queue);
}

