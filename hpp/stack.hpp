#ifndef STACK_HPP_INCLUDED
#define STACK_HPP_INCLUDED


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

const double stack_resize_coefficient = 2;

//--------------------------------------------------


#define STACK_POP_RESIZE(x)   stack_resize (x, (size_t) fmin ( ceil ( (double) x->capacity / stack_resize_coefficient), x->capacity - 1) )
#define STACK_PUSH_RESIZE(x)  stack_resize (x, (size_t) fmax ( ceil ( (double) x->capacity * stack_resize_coefficient), x->capacity + 1) )


typedef struct Stack {

    void*  elements;
    size_t element_size;

    size_t size;
    size_t capacity;

} Stack; const size_t STACK_SIZE = sizeof (Stack);



Stack*  stack_ctor   (size_t size, size_t element_size);
Stack*  stack_dtor   (Stack* stack);
int     stack_resize (Stack* stack, size_t new_capacity);
int     stack_push   (Stack* stack, void* buffer);
int     stack_top    (Stack* stack, void* buffer);
int     stack_pop    (Stack* stack);

size_t test1 (void);
size_t test2 (void);
size_t test3 (void);

void fill_the_stack             (Stack* stack);
void nine_iterations_transform  (Stack* stack);
void test2_special              (Stack* stack);
void test3_special              (Stack* stack);


#endif