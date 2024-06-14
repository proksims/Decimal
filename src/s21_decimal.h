#ifndef SRC_s21_DECIMAL_H
#define SRC_s21_DECIMAL_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_DEC 79228162514264337593543950335.0
#define MIN_DEC 1e-28

//   0        1          2         3
// [LOW]    [MID]     [HIGH]    [SCALE]
// [31...0] [63...32] [95...64]
typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  bool bits[192];
  bool sign;
  int degree;
} s21_big_decimal;

enum res_code { OK, INF, N_INF, DIV_ZERO };

// ========================== MAIN FUNCTIONS =============================
// arithmetic
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// comparison
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

// converters
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// other functions
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// ===================== SECONDARY FUNCTIONS =============================

void initDecimal(s21_decimal *bit);
bool is_null(s21_big_decimal value);
bool is_decimal(s21_big_decimal result);
int getBit(s21_decimal bit, int i);
void setBit(s21_decimal *bit, int i);
void clearBit(s21_decimal *bit, int i);
int getSign(s21_decimal bit);
void setNegSign(s21_decimal *bit);
void setPosSign(s21_decimal *bit);
int getDegree(s21_decimal bit);
void setDegree(s21_decimal *bit, int degree);
void bit_shift(s21_big_decimal *bit);

#endif  // SRC_s21_DECIMAL_H_