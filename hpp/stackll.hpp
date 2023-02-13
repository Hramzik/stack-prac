

#include <sys\stat.h>
#include <locale.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <time.h>


//-------------------- SETTINGS --------------------
#define ON_STACK_ERROR_DUMPING
#define ON_STACK_AFTER_OPERATION_DUMPIN
#define ON_CANARY_PROTECTION
#define ON_HASH_PROTECTION

#define  log_file_name "logs.txt"
#define dump_file_name "dump.txt"

const double stack_resize_coefficient = 1.2;
//--------------------------------------------------


#define COMMA ,


#define LOG_ERROR(code) _log_error (code, __FILE__, __PRETTY_FUNCTION__, __LINE__)

#define  STACK_CTOR(x)  _stack_ctor (x, #x + (#x[0] == '&'), __FILE__, __PRETTY_FUNCTION__, __LINE__)
#define  STACK_DUMP(x) _fstack_dump (x, nullptr,             __FILE__, __PRETTY_FUNCTION__, __LINE__)
#define FSTACK_DUMP(x) _fstack_dump (x, dump_file_name,      __FILE__, __PRETTY_FUNCTION__, __LINE__)

#define STACK_POP_RESIZE(x)   stack_resize (x, (size_t) fmin ( ceil ( (double) x->capacity / stack_resize_coefficient), x->capacity - 1) )
#define STACK_PUSH_RESIZE(x)  stack_resize (x, (size_t) fmax ( ceil ( (double) x->capacity * stack_resize_coefficient), x->capacity + 1) )

#ifdef ON_STACK_ERROR_DUMPING

    #define ASSERT_STACK_OK(x) if (stack_damaged (x)) { FSTACK_DUMP (x); LOG_ERROR (BAD_ARGS); return BAD_ARGS; }

    #define ASSERT_STACK_OK_FOR_STACK_POP(x)\
            if (stack_damaged (x)) { FSTACK_DUMP (x); LOG_ERROR (BAD_ARGS); if (return_code_ptr) { *return_code_ptr = BAD_ARGS; } return Element {NAN, true}; }

    #define STACK_ERROR_DUMP(x) FSTACK_DUMP(x)

#else

    #define ASSERT_STACK_OK(x)\
    if (stack_damaged (x)) {                 LOG_ERROR (BAD_ARGS); return BAD_ARGS; }

    #define ASSERT_STACK_OK_FOR_STACK_POP(x)\
            if (stack_damaged (x)) {                  LOG_ERROR (BAD_ARGS); if (return_code_ptr) { *return_code_ptr = BAD_ARGS; } return Element {NAN, true}; }

    #define STACK_ERROR_DUMP(x)

#endif


#ifdef ON_STACK_AFTER_OPERATION_DUMPING
    #define STACK_AFTER_OPERATION_DUMPING(x) FSTACK_DUMP (x)
#else
    #define STACK_AFTER_OPERATION_DUMPING(x)
#endif


#ifdef ON_CANARY_PROTECTION

    #define IF_CANARY_PROTECTED(x) x;
    #define CANARY_SIZE sizeof (canary_t)
    #define FIRST_CANARY_VALUE  0xDEADBEEF
    #define SECOND_CANARY_VALUE 0xDEADBEEF
    #define stack_resize(x,y)         _stack_canary_resize       (x, y)

#else

    #define IF_CANARY_PROTECTED(x)  ;
    #define stack_resize(x,y)     _stack_resize       (x, y)

#endif


#ifdef ON_HASH_PROTECTION
    #define IF_HASH_PROTECTED(x) x;
    #define HASH_SIZE sizeof (hash_t)
    #define HASH_MAX  ( (hash_t) -1)
    #define HASH_SALT ( (hash_t) 0xD1E2A3D4B5E6E7F )
#else
    #define IF_HASH_PROTECTED(x)  ;
#endif


enum  Return_code  {

    SUCCESS    = 0,
    MEMORY_ERR = 1,
    BAD_ARGS   = 2,
    FILE_ERR   = 3,
};

enum Stack_state_flags {

    OK                            = 0,
    NULLPTR_STACK                 = 1,
    SIZE_GREATER_THAN_CAPACITY    = 2,
    NULLPTR_ELEMENTS              = 4,
    INCORRECT_POISON_DISTRIBUTION = 8,
    STACK_CANARY_CORRUPTED        = 16,
    DATA_CANARY_CORRUPTED         = 32,
    INCORRECT_HASH                = 64,
};

typedef int Stack_state;

typedef struct Stack_structure      Stack;
typedef double                      Element_value;
typedef struct Element_structure    Element;
typedef struct Stack_info_structure Stack_info;
IF_CANARY_PROTECTED (typedef unsigned long long canary_t);
IF_HASH_PROTECTED   (typedef unsigned long long   hash_t);


struct  Stack_info_structure  {

    const  char*  name;
    Stack*        adress;
    const  char*  birth_file;
    const  char*  birth_func;
    int           birth_line;
};

struct  Stack_structure  {

    IF_CANARY_PROTECTED (canary_t FIRST_CANARY);


    Element* elements;
    size_t   size;
    size_t   capacity;

    Stack_info debug_info;

    IF_HASH_PROTECTED (hash_t hash;);


    IF_CANARY_PROTECTED (canary_t SECOND_CANARY);
};

struct  Element_structure  {

    Element_value value;
    bool          poisoned;
};


const size_t   STACK_SIZE             = sizeof (Stack);
const size_t ELEMENT_SIZE             = sizeof (Element);
const size_t time_str_len             = 40;


Return_code _stack_ctor          (Stack* stack, const char* name, const char* file, const char* func, int line);
Return_code  stack_dtor          (Stack* stack);
Return_code _stack_resize        (Stack* stack, size_t new_capacity);
Return_code _stack_canary_resize (Stack* stack, size_t new_capacity);
Return_code  stack_push          (Stack* stack, Element_value new_element_value);
Element      stack_pop           (Stack* stack, Return_code* return_code_ptr = nullptr);

Stack_state  stack_damaged       (Stack* stack);
void       _fstack_dump          (Stack* stack, const char* file_name, const char* file, const char* function, int line);

Return_code _stack_fill_with_poison (Stack* stack, size_t from, size_t to);

IF_HASH_PROTECTED (

    hash_t        hash300                      (void* _data_ptr, size_t size);
    Return_code   stack_recount_hash           (Stack* stack);
);






void       _log_error              (Return_code, const char*, const char*, int);
void        log_message            (const char* message);
void        log_start              (void);
void        log_end                (void);
void        print_log_time         (void);
char*       tm_to_str              (struct tm* time_structure);

