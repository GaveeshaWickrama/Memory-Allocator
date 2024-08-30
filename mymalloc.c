#include <stdio.h>
#include <stddef.h>
#include "mymalloc.h"

char memory[25000];
struct metadata* freeblock =(struct metadata*)memory;


void initialise(){
    freeblock->size = 25000-sizeof(struct metadata);
    freeblock->flag = 1;
    freeblock->next = NULL;
}

void split(struct metadata* ptr,size_t bytes){
    struct metadata * new = (void*)((char*)ptr + sizeof(struct metadata) + bytes);
    new->size = ptr->size-bytes-sizeof(struct metadata);
    new->next = ptr->next;
    new->flag = 1;
    ptr->next = new;
    ptr->size = bytes;
    ptr->flag = 0;
}

void* mymalloc(size_t bytes){
    if(!(freeblock->size)){
        initialise();
    }
    struct metadata* cur = freeblock;
    void * result;

    while((cur->next!=NULL)&&(cur->size<bytes||cur->flag==0)){
        cur = cur->next;
    }

    if(cur->size==bytes){
        cur->flag = 0;
        result =(void *)++cur;
        return result;
    }
    else if(cur->size>=(bytes+sizeof(struct metadata))){
        split(cur,bytes);
        result = (void*)++cur;
        return result;
    }
    else if(cur->size>bytes && cur->size<bytes+sizeof(struct metadata)){
        cur->flag = 0;
        result = (void*)++cur;
        return result;
    }
    else{
        result = NULL;
        return result;
    }
}

void merge(){
    struct metadata* cur = freeblock;
    while(cur->next!=NULL){
        if(cur->next->flag==1 && cur->flag==1){
            cur->size += cur->next->size+sizeof(struct metadata);
            cur->next = cur->next->next; 
            continue;
        }
        cur = cur->next;
    }
}

void myfree(void* ptr)
{
    if(ptr>=(void*)memory && ptr<=(void*)memory+25000){
        struct metadata* cur = ptr;
        cur--;
        cur->flag = 1;
        merge();
    }
    else{
        printf("error\n");
    }
};