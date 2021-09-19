#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Onegin.h"

int main(int argc, char **argv) {
    assert(argc == 3);

    const char* ONEGIN_FILE_INPUT  = argv[1];
    const char* ONEGIN_FILE_OUTPUT = argv[2];

    FILE* input_file  = fopen(ONEGIN_FILE_INPUT, "rb");
    FILE* output_file = fopen(ONEGIN_FILE_OUTPUT, "wb");

    assert(input_file);
    assert(output_file);

    size_t buf_size = file_size(input_file);
    assert(buf_size != 0);

    unsigned char* input_buf = (unsigned char*)calloc(buf_size, sizeof(unsigned char));
    assert(input_buf != NULL);

    fread(input_buf, sizeof(unsigned char), buf_size, input_file);

    size_t onegin_string_count = count_onegin_string(input_buf, buf_size);

    struct OneginString* onegin_string_arr = (struct OneginString*) calloc(onegin_string_count, 
                                                                         sizeof(struct OneginString));

    CreateOneginStringArr(input_buf, buf_size, onegin_string_count, onegin_string_arr);
 
    qsort(onegin_string_arr, onegin_string_count, sizeof(struct OneginString), LOneginStringCmp);
 
    WriteOneginArr(output_file, onegin_string_arr, onegin_string_count);

    free(input_buf);
    free(onegin_string_arr);
}