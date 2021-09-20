#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Onegin.h"

size_t file_size(FILE* input_file) {
    assert(input_file != NULL);

    size_t size_of_file = 0;

    fseek(input_file, 0, SEEK_END);
    size_of_file = ftello(input_file);
    fseek(input_file, 0, SEEK_SET);

    return size_of_file;
}

size_t count_onegin_string(const unsigned char* onegin_buf, const size_t onegin_buf_size) {
    assert(onegin_buf);

    size_t count_onegin_str = 0;
    for(size_t i = 0; i < onegin_buf_size; ++i)
        if(onegin_buf[i] == '\n') count_onegin_str++;
    
    return count_onegin_str
            +1; //последняя строка
}

struct OneginString NewOneginString(const unsigned char* onegin_buf, const size_t onegin_buf_size,
                                    const size_t start_byte) {
    assert(onegin_buf != NULL);

    struct OneginString new_onegin_str;
    new_onegin_str.str = (unsigned char*)onegin_buf + start_byte;

    size_t len_new_onegin_str = 0;
    while(start_byte + len_new_onegin_str < onegin_buf_size &&
          new_onegin_str.str[len_new_onegin_str] != '\n') {
        len_new_onegin_str++;
    }

    new_onegin_str.len = len_new_onegin_str;

    return new_onegin_str;
}

void CreateOneginStringArr(const unsigned char* onegin_buf, const size_t onegin_buf_size, 
                           const size_t onegin_string_count, struct OneginString* onegin_string_arr) {
    assert(onegin_buf != NULL);
    assert(onegin_string_arr);

    size_t cur_byte = 0;

    for(size_t i = 0; i < onegin_string_count; ++i) {
        onegin_string_arr[i] = NewOneginString(onegin_buf, onegin_buf_size, cur_byte);
        cur_byte += onegin_string_arr[i].len
                    +1;// \0
    }   
}

void WriteOneginString(FILE* output_file, const struct OneginString onegin_str) {
    assert(output_file);

    for(size_t i = 0; i < onegin_str.len; ++i) {
        fprintf(output_file, "%c", onegin_str.str[i]);
    }
}

void WriteOneginArr(FILE* output_file, 
                    const struct OneginString* onegin_string_arr, const size_t onegin_string_count) {
    assert(output_file);
    assert(onegin_string_arr != NULL);

    for (size_t i = 0; i < onegin_string_count; ++i) {
        if((onegin_string_arr + i)->str[0] == '\n') continue;
        WriteOneginString(output_file, onegin_string_arr[i]);
        fprintf(output_file, "\n");
    }
}
 
bool CheckIsRussianLyr_win1251(unsigned char lyr) {
    if (lyr == BIG_YO_POS || lyr == LITTLE_YO_POS) {
        return true;
    }
 
    if (lyr >= BIG_A_POS && lyr <= BIG_YA_POS)
        return true;
 
    return lyr >= LITTLE_A_POS && lyr <= LITTLE_YA_POS;
}
 
bool IsBigRussianLyr_win1251(unsigned char lyr) {
    assert(CheckIsRussianLyr_win1251(lyr));
    
    return lyr == BIG_YO_POS || (lyr >= BIG_A_POS && lyr <= BIG_YA_POS);
}
 
unsigned char GetRussianLyrNewEnc(unsigned char lyr) {
    assert(CheckIsRussianLyr_win1251(lyr));
    
    if (IsBigRussianLyr_win1251(lyr)) {
        if (lyr == BIG_YO_POS)
        return BIG_YE_POS;
    
        if (lyr <= BIG_YE_POS)
        return lyr - 1;
    
        return lyr;
    }
    
    if (lyr == LITTLE_YO_POS)
        return LITTLE_YE_POS;
    
    if (lyr <= LITTLE_YE_POS)
        return lyr - 1;
    
    return lyr;
}
 
unsigned char GetLowLetterRussianLyrNewEnc(unsigned char lyr) {
    if (lyr >= BIG_A_POS-1 && lyr <= BIG_YA_POS)
        return lyr - (BIG_A_POS-1) + (LITTLE_A_POS-1);
    
    return lyr;
}
 
int RussianLyrCmp(unsigned char first_lyr, unsigned char second_lyr) {
    return (int)GetLowLetterRussianLyrNewEnc(GetRussianLyrNewEnc(first_lyr)) - 
            (int)GetLowLetterRussianLyrNewEnc(GetRussianLyrNewEnc(second_lyr));
}

int LRussianStringOneginCmp(unsigned char* first_string, size_t first_string_len,
                            unsigned char* second_string, size_t second_string_len) {

    assert(first_string && second_string);

    size_t min_len = first_string_len;  
    if (second_string_len < min_len)
        min_len = second_string_len;

    int first_string_it = 0,
        second_string_it = 0;

    while (first_string_it < min_len && second_string_it < min_len) {
        if (!CheckIsRussianLyr_win1251(first_string[first_string_it])) {
        first_string_it++;
        continue;
        }

        if (!CheckIsRussianLyr_win1251(second_string[second_string_it])) {
        second_string_it++;
        continue;
        }

        if (RussianLyrCmp(first_string[first_string_it], second_string[second_string_it]) != 0)
        return RussianLyrCmp(first_string[first_string_it], second_string[second_string_it]);

        first_string_it++;
        second_string_it++;
    }

    return (int)first_string_len - (int)second_string_len;
}

int LOneginStringCmp(const void* lhs, const void* rhs) {
    assert(lhs && rhs);

    struct OneginString first_onegin_str  = *(struct OneginString*)lhs,
                        second_onegin_str = *(struct OneginString*)rhs; 

    return LRussianStringOneginCmp(first_onegin_str.str, first_onegin_str.len,
                                    second_onegin_str.str, second_onegin_str.len);
}


int LRomeoStringCmp(const void *lhs, const void *rhs) {
    assert(lhs && rhs);

    struct OneginString first_romeo_string  = *(struct OneginString*)lhs,
                        second_romeo_string = *(struct OneginString*)rhs;

    while(*first_romeo_string.str)
    {
        if(*first_romeo_string.str != *second_romeo_string.str)
            break;
        
        first_romeo_string.str++;
        second_romeo_string.str++;
    }
    return *(const unsigned char*)first_romeo_string.str - 
           *(const unsigned char*)second_romeo_string.str;
}