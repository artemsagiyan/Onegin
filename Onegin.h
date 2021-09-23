#include <stdio.h>

/**
 * @brief Struct for saving data about onegin string
 * 
 * @param str - ptr on begin of string
 * @param len - length of string
 * 
 */
struct OneginString {
    char *str;
    size_t len;
};

/**
 * @brief Text - struct for all file (text)
 * 
 * @param onegin_buf          - Buffer for all file
 * @param onegin_string_count - Count of onegin strings
 * @param onegin_size_of_file - Count bytes of file
 * @param onegin_string_arr   - Arrive of string for onegin
 */
typedef struct OneginStringArr {
     char * onegin_buf;
     size_t onegin_string_count;
     size_t onegin_size_of_file;
     struct OneginString *onegin_string_arr;
}Text;

/**
 * @brief Count of byte 
 * 
 * @param input_file [in] - Input file
 * @param Onegin     [in] - Struct for all file
 */
void FileSize(FILE *input_file, Text *Onegin);
/**
 * @brief Calculate count of onegin strings
 * 
 * @param Onegin  [in]  - Struct for all file
 *
 * @return size_t [out] - Size of file
 */
size_t CountOneginString(Text *Onegin);

/**
 * @brief Take one onegin_string
 * 
 * @param start_byte [in] - Ptr of begin string
 * @param Onegin     [in] - Struct for all file
 * @return struct OneginString 
 */
struct OneginString NewOneginString(const size_t start_byte, Text *Onegin);

/**
 * @brief Create a Onegin String Arr object
 * 
 * @param Onegin [in] - Struct for all file
 */
void CreateOneginStringArr(Text *Onegin);

/**
 * @brief Write string to file
 * 
 * @param output_file [in] - Output file
 * @param onegin_str  [in] - Arrive of string fot onegin
 * @param Onegin      [in] - Struct for all file
 */
void WriteOneginString(FILE *output_file, const struct OneginString onegin_str, 
                       Text *Onegin);

/**
 * @brief Write to file all strings
 * 
 * @param output_file         [in] - Output file
 * @param Onegin [in] - Struct for all file
 */
void WriteOneginArr(FILE *output_file, Text *Onegin);

/**
 * @brief Variables for changing the encoding in favor of the letter YO
 */
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

/**
 * @brief Check: is Lyr Russia?
 * 
 * @param lyr   
 * @return true 
 * @return false 
 */
bool CheckIsRussianLyr_win1251(char lyr);

/**
 * @brief Check: is Lyr big Russia?
 * 
 * @param lyr 
 * @return true 
 * @return false 
 */
bool IsBigRussianLyr_win1251(char lyr);

/**
 * @brief Get the Russian Lyr New Enc object
 * 
 * @param lyr 
 * @return unsigned char 
 */
char GetRussianLyrNewEnc(char lyr);

/**
 * @brief Get the Low Letter Russian Lyr New Enc object
 * 
 * @param lyr 
 * @return unsigned char 
 */
char GetLowLetterRussianLyrNewEnc(char lyr);

/**
 * @brief Compare 2 russian lyr
 * 
 * @param first_lyr 
 * @param second_lyr 
 * 
 * @return int < 0 - first, 
 *             > 0 - second, 
 *             = 0 - equal
 */
int RussianLyrCmp(char first_lyr, char second_lyr);

/**
 * @brief Compare 2 russian strings
 * 
 * @param first_string      [in] - pointer to the beginning first string
 * @param first_string_len  [in] - len of first string
 * @param second_string     [in] - pointer to the beginning second string
 * @param second_string_len [in] - len of second string
 * 
 * @return int < 0 - first, 
 *             > 0 - second, 
 *             = 0 - equal
 */
int LRussianStringOneginCmp(char *first_string, size_t first_string_len,
                            char *second_string, size_t second_string_len);

/**
 * @brief Compare 2 onegin_string
 * 
 * @param lhs [in] - pointer to the beginning first onegin_string
 * @param rhs [in] - pointer to the beginning second onegin_string
 * 
 * @return int < 0 - first, 
 *             > 0 - second, 
 *             = 0 - equal
 */
int LOneginStringCmp(const void *lhs, const void *rhs);

/**
 * @brief Compare 2 L_romeo_string
 * 
 * @param lhs [in] - pointer to the beginning first onegin_string
 * @param rhs [in] - pointer to the beginning second onegin_string
 * 
 * @return int < 0 - first, 
 *             > 0 - second, 
 *             = 0 - equal
 */
int LRomeoStringCmp(const void *lhs, const void *rhs);

/**
 * @brief Compare 2 R_onegin_string
 * 
 * @param lhs [in] - pointer to the beginning first onegin_string
 * @param rhs [in] - pointer to the beginning second onegin_string
 * 
 * @return int < 0 - first, 
 *             > 0 - second, 
 *             = 0 - equal
 */
int RRomeoStringCmp(const void *lhs, const void *rhs);

/**
 * @brief Sort of arr with quick sort
 * 
 * @param base   [in] - arr
 * @param nmemb  [in] - count memery for 1 element 
 * @param size   [in] - count numbers of arr for sorting
 * @param compar [in] - comparator for sorting
 */
void Myqsort(void *base, size_t nmemb, size_t size, 
              int (*compar)(const void *, const void *));
/**
 * @brief Change means of 2 var
 * 
 * @param v1 
 * @param v2 
 */
void swap(void *v1, void *v2);

/**
 * @brief Sorting with method quick_sort
 * 
 * @param base   [in] - sorting arrive
 * @param low    [in] - low position of sorting
 * @param high   [in] - high position for sorting
 * @param compar [in] - comporator fot sorting
 */
void QsortImpl(void *base, size_t low, size_t high, int (*compar)(const void *, const void *));

/**
 * @brief Div massiv on low and high parts
 * 
 * @param base    [in]  - sorting arrive
 * @param low     [in]  - low position of sorting
 * @param high    [in]  - high position for sorting
 * @param compar  [in]  - comporator fot sorting
 * 
 * @return size_t [out] - need position for div
 */
size_t Partition(void *base, size_t low, size_t high, int (*compar)(const void *, const void *));

/**
 * @brief Clear mem of Text
 * 
 * @param Onegin [in] - struct Text
 */
void DistructOnegin(Text *Onegin);