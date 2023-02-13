

#include <sys\stat.h>
#include <locale.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include "common.hpp"


//-------------------- SETTINGS --------------------

#define  log_file_name "logs.txt"

const double stack_resize_coefficient = 2;
//--------------------------------------------------


#define STACK_POP_RESIZE(x)   stack_resize (x, (size_t) fmin ( ceil ( (double) x->capacity / stack_resize_coefficient), x->capacity - 1) )
#define STACK_PUSH_RESIZE(x)  stack_resize (x, (size_t) fmax ( ceil ( (double) x->capacity * stack_resize_coefficient), x->capacity + 1) )


typedef struct  Stack_structure  {

    void*  elements;
    size_t element_size;

    size_t size;
    size_t capacity;

} Stack; const size_t STACK_SIZE = sizeof (Stack);



Stack*  stack_ctor   (size_t size, size_t element_size);
Stack*  stack_dtor   (Stack* stack);
int     stack_resize (Stack* stack, size_t new_capacity);
int     stack_push   (Stack* stack, void* buffer);
int     stack_pop    (Stack* stack);


