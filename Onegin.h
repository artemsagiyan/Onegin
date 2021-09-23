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

typedef struct OneginStringArr {
     size_t onegin_string_count;
     char * onegin_buf;
     struct OneginString *onegin_string_arr;
}Text;

/**
 * @brief Count of byte 
 * 
 * @param input_file [in]  - input file
 * 
 * @return size_t    [out] - count of byte
 */
size_t file_size(FILE *input_file);
/**
 * @brief Calculate count of onegin strings
 * 
 * @param onegin_buf      [in]  - The buffer in which the file data is stored
 * @param onegin_buf_size [in]  - Size of file
 *
 * @return size_t         [out] - Size of file
 */
size_t count_onegin_string(const char *onegin_buf, const size_t onegin_buf_size);

struct OneginString NewOneginString(const char *onegin_buf, const size_t onegin_buf_size,
                                    const size_t start_byte);
/**
 * @brief Create a Onegin String Arr object
 * 
 * @param onegin_buf          [in] - The buffer in which the file data is stored
 * @param onegin_buf_size     [in] - Size of file
 * @param onegin_string_count [in] - Count of onegin strings
 * @param onegin_string_arr   [in] - Arrive of string fot onegin
 */
void CreateOneginStringArr(const char *onegin_buf, const size_t onegin_buf_size, 
                           const size_t onegin_string_count, struct OneginString *onegin_string_arr);
/**
 * @brief Write string to file
 * 
 * @param output_file [in] - Output file
 * @param onegin_str  [in] - Arrive of string fot onegin
 */
void WriteOneginString(FILE *output_file, const struct OneginString onegin_str);

/**
 * @brief Write to file all strings
 * 
 * @param output_file         [in] - Output file
 * @param onegin_string_arr   [in] - Arrive of string fot onegin
 * @param onegin_string_count [in] - Count of onegin strings
 */
void WriteOneginArr(FILE *output_file, 
                    const struct OneginString *onegin_string_arr, const size_t onegin_string_count);

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
 * @brief Copy first_arr to second_arr
 * 
 * @param onegin_string_arr      [in] - first arr
 * @param onegin_string_arr_copy [in] - second arr
 */
void OneginArrStructCopy(const  size_t onegin_string_count,
                         struct OneginString *onegin_string_arr, 
                         struct OneginString *onegin_string_arr_copy);