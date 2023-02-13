

#include "../hpp/stack.hpp"
#include "../lib/logs.hpp"


Stack*  stack_ctor  (size_t size, size_t element_size) {

    Stack* stack = (Stack*) calloc (STACK_SIZE);


    stack->elements = (void*) calloc (size * element_size);
    stack->element_size = element_size;

    stack->size     = 0;
    stack->capacity = size;


    return stack;
}


Stack*  stack_dtor  (Stack* stack) {

    assert (stack);


    free (stack->elements);
    free (stack);


    return nullptr;
}


int  stack_resize  (Stack* stack, size_t new_capacity) {

    assert (stack);


    stack->elements = (void*) realloc (stack->elements, sizeof (void*) * new_capacity);
    if (stack->elements == nullptr && new_capacity != 0) { LOG_ERROR (MEMORY_ERR); return 1; }


    stack->capacity = new_capacity;


    if (stack->size > new_capacity) { stack->size = new_capacity; }


    return 0;
}


int  stack_push  (Stack* stack, void* buffer) {

    assert (stack);
    assert (buffer);


    if (stack->size == stack->capacity) {

        int resize_code = 1;

        if (!stack->capacity) {

            resize_code = stack_resize (stack, 1);
        }
        else {

            resize_code = STACK_PUSH_RESIZE (stack);
        }

        if (resize_code) { return resize_code; }
    }


    stack->size += 1;
    memcpy (&stack->elements [stack->size - 1], buffer, stack->element_size);


    return 0;
}


int  stack_pop  (Stack* stack) {

    assert (stack);


    if (stack->size != 0) {

        stack->size -= 1;
    }


    if ( (double) stack->size * pow (stack_resize_coefficient, 2) <= (double) stack->capacity) {

        int resize_code = STACK_POP_RESIZE (stack);

        if (resize_code) {

            return resize_code;
        }
    }


    return 0;
}

