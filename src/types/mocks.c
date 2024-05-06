#include "mocks.h"
#include "stdlib.h"

void * failing_calloc_f(__attribute__((unused)) size_t count, __attribute__((unused)) size_t size) {
    return NULL;
}

calloc_f failing_calloc(void) {
    return &failing_calloc_f;
}

void * failing_realloc_f(__attribute__((unused)) void * ptr, __attribute__((unused)) size_t size) {
    return NULL;
}
realloc_f failing_realloc(void) {
    return &failing_realloc_f;
}


FILE * failing_str_str(__attribute__((unused)) const char * str1, __attribute__((unused)) const char *str2) {
    return NULL;
}

fopen_f failing_fopen(void) {
    return &failing_str_str;
}

FILE * memory_fopen_f(__attribute__((unused)) const char * filename, const char * mode) {
    // create a FILE * from a buffer
    // POSIX => not Windows friendly
    static char buffer[16] = "buffer\0";
    return fmemopen(&buffer, 16, mode);
}

fopen_f memory_fopen(void) {
    return &memory_fopen_f;
}

popen_f failing_popen(void) {
    return &failing_str_str;
}

popen_f memory_popen(void) {
    return &memory_fopen_f;
}



int failing_pclose_f(FILE *stream) {
    pclose(stream);
    return EXIT_FAILURE;
}

pclose_f failing_pclose(void) {
    return &failing_pclose_f;
}

int success_pclose_f(FILE *stream) {
    pclose(stream);
    return EXIT_SUCCESS;
}


pclose_f success_pclose(void) {
    return &success_pclose_f;
}
