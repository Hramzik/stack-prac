

// #include "../hpp/stack.hpp"


size_t  test1  (void) {

    Stack* stack = stack_ctor (1, INT_SIZE);


    clock_t start = clock ();

    fill_the_stack (stack);
    nine_iterations_transform (stack);

    clock_t end = clock ();


    stack_dtor (stack);


    return (end - start) * 1000 / CLOCKS_PER_SEC;
}


size_t  test2  (void) {

    Stack* stack = stack_ctor (1, INT_SIZE);


    clock_t start = clock ();

    fill_the_stack (stack);
    test2_special  (stack);
    nine_iterations_transform (stack);

    clock_t end = clock ();


    stack_dtor (stack);


    return (end - start) * 1000 / CLOCKS_PER_SEC;
}


size_t  test3  (void) {

    Stack* stack = stack_ctor (1, INT_SIZE);
    fill_the_stack (stack);


    clock_t start = clock ();

    test3_special  (stack);

    clock_t end = clock ();


    stack_dtor (stack);


    return (end - start) * 1000 / CLOCKS_PER_SEC;
}


void  test2_special  (Stack* stack) {

    assert (stack);


    int value = 1000;

    for (size_t i = 0; i < 100; i++) {

        for (size_t j = 0; j < 10000; j++) {

            stack_pop (stack);
        }

        for (size_t j = 0; j < 10000; j++) {

            stack_push (stack, &value);
        }
    }


    return;
}


void nine_iterations_transform  (Stack* stack) {

    assert (stack);

    int value = 1000;

    while (stack->size > 100000) {

        size_t n = stack->size;


        for (size_t i = 0; i < n / 2; i++) {

            stack_pop (stack);
        }


        for (size_t i = 0; i < n / 4; i++) {

            stack_push (stack, &value);
        }
    }


    return;
}


void fill_the_stack  (Stack* stack) {

    assert (stack);


    int value = 1000;

    for (size_t i = 0; i < 1000000; i++) {

        stack_push (stack, &value);
    }


    return;
}


void  test3_special  (Stack* stack) {

    assert (stack);


    int value = 1000;
    srand ((unsigned int) time (nullptr));

    for (size_t i = 0; i < 1000000; i++) {

        if (rand () % 2) {

            stack_push (stack, &value);
            continue;
        }

        stack_pop (stack);
    }


    return;
}

