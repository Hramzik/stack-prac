

#include "../hpp/stackll.hpp"


int main (void) {

    size_t time1 = 0;
    size_t time2 = 0;
    size_t time3 = 0;


    printf ("\ntesting linked list-based stack...\n");

    printf ("test1: %zd ms, %zd ms, %zd ms\n", time1 = test1 (), time2 = test1 (), time3 = test1 ());
    printf ("  avg: %zd ms\n", (time1 + time2 + time3) / 3);

    printf ("test2: %zd ms, %zd ms, %zd ms\n", time1 = test2 (), time2 = test2 (), time3 = test2 ());
    printf ("  avg: %zd ms\n", (time1 + time2 + time3) / 3);

    printf ("test3: %zd ms, %zd ms, %zd ms\n", time1 = test3 (), time2 = test3 (), time3 = test3 ());
    printf ("  avg: %zd ms\n", (time1 + time2 + time3) / 3);

    printf ("\ngoodbye!\n");


    return 0;
}

