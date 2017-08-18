#include "mylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "mylib_i.h"
__attribute ((visibility("default")))
void bar() {
    int i = 9;
    foo((void*)&i);
}
