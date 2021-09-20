#include <stdio.h>

struct OneginString {
    unsigned char *str;
    size_t len;
};

size_t file_size(FILE* input_file);

size_t count_onegin_string(const unsigned char* onegin_buf, const size_t onegin_buf_size);

struct OneginString NewOneginString(const unsigned char* onegin_buf, const size_t onegin_buf_size,
                                    const size_t start_byte);

void CreateOneginStringArr(const unsigned char* onegin_buf, const size_t onegin_buf_size, 
                           const size_t onegin_string_count, struct OneginString* onegin_string_arr);

void WriteOneginString(FILE* output_file, const struct OneginString onegin_str);

void WriteOneginArr(FILE* output_file, 
                    const struct OneginString* onegin_string_arr, const size_t onegin_string_count);

enum Russian_win1251_pos {
  BIG_YO_POS = 168,
  LITTLE_YO_POS = 184,
 
  BIG_A_POS = 192,
  LITTLE_A_POS = 224,
 
  BIG_YA_POS = 223,
  LITTLE_YA_POS = 255,
 
  BIG_YE_POS = 197,
  LITTLE_YE_POS = 229
};

bool CheckIsRussianLyr_win1251(unsigned char lyr);

bool IsBigRussianLyr_win1251(unsigned char lyr);

unsigned char GetRussianLyrNewEnc(unsigned char lyr);

unsigned char GetLowLetterRussianLyrNewEnc(unsigned char lyr);

int RussianLyrCmp(unsigned char first_lyr, unsigned char second_lyr);

int LRussianStringOneginCmp(unsigned char* first_string, size_t first_string_len,
                            unsigned char* second_string, size_t second_string_len);

int LOneginStringCmp(const void* lhs, const void* rhs);

int LRomeoStringCmp(const void* lhs, const void* rhs);