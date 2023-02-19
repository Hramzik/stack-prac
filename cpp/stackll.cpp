

#include "../hpp/stackll.hpp"
#include "../lib/logs.hpp"


Stack*  stack_ctor  (size_t size, size_t element_size) {

    size += 69420; //supress the warning
    Stack* stack = (Stack*) calloc (STACK_SIZE, 1);


    stack->top          = nullptr;
    stack->element_size = element_size;
    stack->size         = 0;

    return stack;
}


Stack*  stack_dtor  (Stack* stack) {

    assert (stack);


    while (stack->top != nullptr) {

        stack_pop (stack);
    }

    free (stack);


    return nullptr;
}


int  stack_push  (Stack* stack, void* buffer) {

    assert (stack);
    assert (buffer);


    Node* top  = (Node*) calloc (NODE_SIZE, 1);
    top->value = (void*) calloc (stack->element_size, 1);
    memcpy (top->value, buffer, stack->element_size);


    if (stack->size == 0) {

        top->next = nullptr;
    }
    else {

        top->next = stack->top;
    }


    stack->top = top;
    stack->size += 1;


    return 0;
}


int  stack_top  (Stack* stack, void* buffer) {

    assert (stack);


    memcpy (buffer, stack->top->value, stack->element_size);


    return 0;
}


int  stack_pop  (Stack* stack) {

    assert (stack);


    if (stack->size == 0) {

        return 0;
    }


    Node* new_top = stack->top->next;
    free (stack->top->value);
    free (stack->top);
    stack->top = new_top;

    stack->size -= 1;


    return 0;
}


#include "tests.cpp"

