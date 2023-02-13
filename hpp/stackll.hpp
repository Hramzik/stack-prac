

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

    Element* elements;
    size_t   size;
    size_t   capacity;

} Stack; const size_t STACK_SIZE = sizeof (Stack);



Return_code _stack_ctor          (Stack* stack, const char* name, const char* file, const char* func, int line);
Return_code  stack_dtor          (Stack* stack);
Return_code _stack_resize        (Stack* stack, size_t new_capacity);
Return_code  stack_push          (Stack* stack, Element_value new_element_value);
Element      stack_pop           (Stack* stack, Return_code* return_code_ptr = nullptr);


Return_code _stack_fill_with_poison (Stack* stack, size_t from, size_t to);

