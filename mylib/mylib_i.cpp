#include "mylib_i.h"   
#include <stdio.h>   
#include <stdlib.h>   

extern "C" void foo() {   
    printf("foo in lib/n");   
}
