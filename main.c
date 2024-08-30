#include <stdio.h>
#include "mymalloc.h"

int main(){
    int* p= (int*)mymalloc(100*sizeof(int));
    char* q=(char*)mymalloc(250*sizeof(char));
    int *r=(int*)mymalloc(1000*sizeof(int));
    myfree(p);
    char *w=(char*)mymalloc(700);
    myfree(r);
    int *k=(int*)mymalloc(500*sizeof(int));
    printf("Allocation and deallocation is done successfully!");
    return 0;
}
