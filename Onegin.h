#include <stdio.h>

/**
 * @brief Структура для хранения инофрмации о строке
 * 
 * @param str - указатель на начало строки
 * @param len - длина строки
 * 
 */
struct OneginString {
    unsigned char *str;
    size_t len;
};

/**
 * @brief Считает количество байтов в файле
 * 
 * @param input_file - input file
 * 
 * @return size_t    - count of byte
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
size_t count_onegin_string(const unsigned char *onegin_buf, const size_t onegin_buf_size);

struct OneginString NewOneginString(const unsigned char *onegin_buf, const size_t onegin_buf_size,
                                    const size_t start_byte);
/**
 * @brief Create a Onegin String Arr object
 * 
 * @param onegin_buf          [in] - The buffer in which the file data is stored
 * @param onegin_buf_size     [in] - Size of file
 * @param onegin_string_count [in] - Count of onegin strings
 * @param onegin_string_arr   [in] - Arrive of string fot onegin
 */
void CreateOneginStringArr(const unsigned char *onegin_buf, const size_t onegin_buf_size, 
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
bool CheckIsRussianLyr_win1251(unsigned char lyr);

/**
 * @brief Check: is Lyr big Russia?
 * 
 * @param lyr 
 * @return true 
 * @return false 
 */
bool IsBigRussianLyr_win1251(unsigned char lyr);

/**
 * @brief Get the Russian Lyr New Enc object
 * 
 * @param lyr 
 * @return unsigned char 
 */
unsigned char GetRussianLyrNewEnc(unsigned char lyr);

/**
 * @brief Get the Low Letter Russian Lyr New Enc object
 * 
 * @param lyr 
 * @return unsigned char 
 */
unsigned char GetLowLetterRussianLyrNewEnc(unsigned char lyr);

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
int RussianLyrCmp(unsigned char first_lyr, unsigned char second_lyr);

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
int LRussianStringOneginCmp(unsigned char *first_string, size_t first_string_len,
                            unsigned char *second_string, size_t second_string_len);

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