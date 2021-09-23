#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "Onegin.h"

void FileSize(FILE *input_file, Text *Onegin) {
    assert(input_file != NULL);

    fseek(input_file, 0, SEEK_END);
    Onegin->onegin_size_of_file = ftello(input_file);
    fseek(input_file, 0, SEEK_SET);
}

size_t CountOneginString(Text *Onegin) {
    assert(Onegin->onegin_buf);

    for(size_t i = 0; i < Onegin->onegin_size_of_file; ++i)
        if(Onegin->onegin_buf[i] == '\n') Onegin->onegin_string_count++;
    
    return Onegin->onegin_string_count
            +1; //последняя строка
}

struct OneginString NewOneginString(const size_t start_byte, Text *Onegin) {
    assert(Onegin->onegin_buf);

    struct OneginString new_onegin_str;
    new_onegin_str.str = (char*)Onegin->onegin_buf + start_byte;

    size_t len_new_onegin_str = 0;
    while(start_byte + len_new_onegin_str < Onegin->onegin_size_of_file &&
          new_onegin_str.str[len_new_onegin_str] != '\n') {
        if (new_onegin_str.str[len_new_onegin_str] == 'I'  ||
            new_onegin_str.str[len_new_onegin_str] == 'V'  ||
            new_onegin_str.str[len_new_onegin_str] == 'X'  ||
            new_onegin_str.str[len_new_onegin_str] == 'L'  ||
            new_onegin_str.str[len_new_onegin_str] == ']'  ||
            isdigit(new_onegin_str.str[len_new_onegin_str])) {
            
            new_onegin_str.len = 0;
            return new_onegin_str;
        }
        len_new_onegin_str++;
    }

    new_onegin_str.len = len_new_onegin_str;

    return new_onegin_str;
}

void CreateOneginStringArr(Text *Onegin) {
    assert(Onegin->onegin_buf);
    assert(Onegin->onegin_string_arr);

    size_t cur_byte = 0;

    for(size_t i = 0; i < Onegin->onegin_string_count; ++i) {
        Onegin->onegin_string_arr[i] = NewOneginString(cur_byte, Onegin);
        cur_byte += Onegin->onegin_string_arr[i].len
                    +1;// \0
    }   
}

void WriteOneginString(FILE *output_file, const struct OneginString onegin_str,
                       Text *Onegin) {
    assert(output_file);

    for(size_t i = 0; i < onegin_str.len; ++i) {
        fprintf(output_file, "%c", onegin_str.str[i]);
    }
}

void WriteOneginArr(FILE *output_file, Text *Onegin) {
    assert(output_file);
    assert(Onegin->onegin_string_arr);

    for (size_t i = 0; i < Onegin->onegin_string_count; ++i) {
        if((Onegin->onegin_string_arr + i)->str[0] == '\n') continue;
        if(Onegin->onegin_string_arr[i].len == 0) continue;
        WriteOneginString(output_file, Onegin->onegin_string_arr[i], Onegin);
        fprintf(output_file, "\n");
    }
}
 
bool CheckIsRussianLyr_win1251(char lyr) {
    if (lyr == BIG_YO_POS || lyr == LITTLE_YO_POS) {
        return true;
    }
 
    if (lyr >= BIG_A_POS && lyr <= BIG_YA_POS)
        return true;
 
    return lyr >= LITTLE_A_POS && lyr <= LITTLE_YA_POS;
}
 
bool IsBigRussianLyr_win1251(char lyr) {
    assert(CheckIsRussianLyr_win1251(lyr));
    
    return lyr == BIG_YO_POS || (lyr >= BIG_A_POS && lyr <= BIG_YA_POS);
}
 
char GetRussianLyrNewEnc(char lyr) {
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
 
char GetLowLetterRussianLyrNewEnc(char lyr) {
    if (lyr >= BIG_A_POS-1 && lyr <= BIG_YA_POS)
        return lyr - (BIG_A_POS-1) + (LITTLE_A_POS-1);
    
    return lyr;
}
 
int RussianLyrCmp(char first_lyr, char second_lyr) {
    return (int)GetLowLetterRussianLyrNewEnc(GetRussianLyrNewEnc(first_lyr)) - 
            (int)GetLowLetterRussianLyrNewEnc(GetRussianLyrNewEnc(second_lyr));
}

int LRussianStringOneginCmp(char *first_string, size_t first_string_len,
                            char *second_string, size_t second_string_len) {

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

int LOneginStringCmp(const void *lhs, const void *rhs) {
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

    while(*first_romeo_string.str && *second_romeo_string.str) {
        if(*first_romeo_string.str != *second_romeo_string.str)
            break;
        
        first_romeo_string.str++;
        second_romeo_string.str++;
    }
    return *(const char*)first_romeo_string.str - 
           *(const char*)second_romeo_string.str;
}

int RRomeoStringCmp(const void *lhs, const void *rhs) {
    assert(lhs && rhs);

    struct OneginString first_romeo_string  = *(struct OneginString*)lhs,
                        second_romeo_string = *(struct OneginString*)rhs;

    first_romeo_string.str += first_romeo_string.len;
    second_romeo_string.str += second_romeo_string.len;

    while(*first_romeo_string.str && *second_romeo_string.str)
    {
        if(*first_romeo_string.str != *second_romeo_string.str)
            break;
        
        first_romeo_string.str--;
        second_romeo_string.str--;
    }
    return *(const char*)first_romeo_string.str - 
           *(const char*)second_romeo_string.str;
}

void Myqsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) {
    assert(base);
    QsortImpl(base, 0u, size - 1, compar);
}

void QsortImpl(void *base, size_t low, size_t high, int (*compar)(const void *, const void *)) {
  assert(base);
  
  if (low >= high) return;
  size_t pi = Partition(base, low, high, compar);
  if (pi > low) QsortImpl(base, low, pi - 1, compar);
  QsortImpl(base, pi + 1, high, compar);
}

size_t Partition (void *base, size_t low, size_t high, int (*compar)(const void *, const void *)) {
    assert(base);
    struct OneginString* onegin_string_arr = (OneginString*)base;

    size_t ind_l = low, 
           ind_r = high;
    while(ind_l < ind_r) {
        if(compar(&onegin_string_arr[ind_l], &onegin_string_arr[ind_r]) < 0) ind_r--;
        else {
            swap(&onegin_string_arr[ind_l], &onegin_string_arr[ind_r]);
            ind_l++;
            while(ind_l < ind_r) {
                if((compar(&onegin_string_arr[ind_r], &onegin_string_arr[ind_l]) > 0)) ind_l++;
                else {
                    swap(&onegin_string_arr[ind_l], &onegin_string_arr[ind_r]);
                    ind_r--;
                    break;
                }
            }
        } 
    } 
    return ind_l;
}

void swap(void *v1, void *v2)
{
    struct OneginString tmp = *(OneginString*)v1;
    *(OneginString*)v1 = *(OneginString*)v2;
    *(OneginString*)v2 = tmp;
}

void OneginArrStructCopy(const  size_t onegin_string_count,
                         struct OneginString *onegin_string_arr, 
                         struct OneginString *onegin_string_arr_copy) {
    assert(onegin_string_arr);
    assert(onegin_string_arr_copy);

    for(int it = 0; it < onegin_string_count; ++it) {
        onegin_string_arr_copy[it].len = onegin_string_arr[it].len;

        strcpy(onegin_string_arr_copy[it].str,
                onegin_string_arr[it].str);
    }
}

void DistructOnegin(Text *Onegin) {
    free(Onegin->onegin_buf);
    free(Onegin->onegin_string_arr);
    Onegin->onegin_string_arr = (OneginString *)(13);
    Onegin->onegin_buf        = (char *)(13);
}   