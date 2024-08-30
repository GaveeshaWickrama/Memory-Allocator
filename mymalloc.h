#include <stdio.h>
#include <stddef.h>

struct metadata
{
    size_t size;
    int flag;
    /*flag==1 means data block referred to by this metadata block is not yet allocated 
    and flag is set to zero otherwise.*/
    struct metadata * next;
};

void initialise();
void* mymalloc(size_t bytes);
void myfree(void* ptr);
void merge();



