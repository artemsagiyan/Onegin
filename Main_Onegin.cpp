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

    Text Onegin{
        .onegin_buf = NULL,
        .onegin_string_count = 0,
        .onegin_size_of_file = 0,
        .onegin_string_arr = NULL
    };

    FileSize(input_file, &Onegin);
    assert(Onegin.onegin_size_of_file != 0);

    Onegin.onegin_buf = (char*)calloc(Onegin.onegin_size_of_file, sizeof(char));
    assert(Onegin.onegin_buf != NULL);

    fread(Onegin.onegin_buf, sizeof(char), Onegin.onegin_size_of_file, input_file);

    Onegin.onegin_string_count = CountOneginString(&Onegin);

    Onegin.onegin_string_arr = (struct OneginString*) calloc(Onegin.onegin_string_count, 
                                                                         sizeof(struct OneginString));
    
    CreateOneginStringArr(&Onegin);
 
    printf("SORT STARTING...\n");
 
    Myqsort(Onegin.onegin_string_arr, sizeof(struct OneginString), Onegin.onegin_string_count, LRomeoStringCmp);

    printf("SORT in L side is finished\n");

    fprintf(output_file,
    "___________________________________SORT on LEFT side___________________________________\n\n\n");
    WriteOneginArr(output_file, &Onegin);

    Myqsort(Onegin.onegin_string_arr, sizeof(struct OneginString), Onegin.onegin_string_count, RRomeoStringCmp);

    printf("SORT in R side is finished\n");

    fprintf(output_file,
    "\n\n___________________________________SORT on RIGHT side___________________________________\n\n\n");
    WriteOneginArr(output_file, &Onegin);

    DistructOnegin(&Onegin);
}