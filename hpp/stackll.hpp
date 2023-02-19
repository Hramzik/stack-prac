#ifndef STACKLL_HPP_INCLUDED
#define STACKLL_HPP_INCLUDED


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

//--------------------------------------------------



typedef struct  Node  {

    void* value;
    Node* next;

} Node; const size_t NODE_SIZE = sizeof (Node);


typedef struct  Stack_structure  {

    Node*    top;
    size_t   element_size;
    size_t   size;

} Stack; const size_t STACK_SIZE = sizeof (Stack);



Stack*  stack_ctor   (size_t size, size_t element_size);
Stack*  stack_dtor   (Stack* stack);
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

