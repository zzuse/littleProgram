#include <stdio.h>    
#include <stdlib.h> 
#include "mylib.h"      
void foo(void * p)  {
    printf("foo in main, %dn", *((int*)p));
}
int main()  {
    bar();
    return 0;
}
