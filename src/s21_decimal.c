#include "s21_decimal.h"

// ================== SECONDARY FUNCTIONS ==================
void initDecimal(s21_decimal *bit) {
  for (int i = 0; i < 4; i++) bit->bits[i] = 0;
}

bool is_null(s21_big_decimal value) {
  bool flag = 1;

  for (int i = 0; i < 192; i++) {
    if (value.bits[i]) {
      flag = 0;
      break;
    }
  }

  return flag;
}

bool is_decimal(s21_big_decimal result) {
  bool flag = 1;

  for (int i = 96; i < 192; i++) {
    if (result.bits[i]) {
      flag = 0;
      break;
    }
  }

  return flag;
}

int getBit(s21_decimal bit, int i) {
  // make mask 000...001 << (index < 32)
  int mask = 1 << (i % 32);
  int res = bit.bits[i / 32] & mask;
  if (res != 0) {
    res = 1;
  }
  return res;
}

void setBit(s21_decimal *bit, int i) {
  int mask = 1 << (i % 32);
  bit->bits[i / 32] = bit->bits[i / 32] | mask;
}

// void clearBit(s21_decimal *bit, int i) {
//   int mask = ~(1 << (i % 32));
//   bit->bits[i / 32] = bit->bits[i / 32] & mask;
// }

int getSign(s21_decimal bit) {
  // 0:pos+ 1:neg-
  int mask = 1 << 31;
  int res = bit.bits[3] & mask;
  if (res != 0) {
    res = 1;
  }
  return res;
}

void setNegSign(s21_decimal *bit) {
  int mask = 1 << 31;
  bit->bits[3] = bit->bits[3] | mask;
}

void setPosSign(s21_decimal *bit) {
  int mask = ~(1 << 31);
  bit->bits[3] = bit->bits[3] & mask;
}

int getDegree(s21_decimal bit) {
  int mask = 1;
  int res = 0;
  int prom_bit = 0;
  int count = 0;

  for (int i = 16; i <= 23; i++) {
    mask = 1 << i;
    prom_bit = bit.bits[3] & mask;
    if (prom_bit != 0) {
      prom_bit = 1;
    }

    // перевод из двоичной в десятичную си
    res = res + pow(2, count) * prom_bit;
    count++;
  }
  return res;
}

void setDegree(s21_decimal *bit, int degree) {
  s21_decimal tmp = {{degree, 0, 0, 0}};

  for (int i = 112; i <= 119; i++) {
    if (getBit(tmp, i - 112)) {
      setBit(bit, i);
    }
  }
}

void bit_shift(s21_big_decimal *bit) {
  for (int i = 191; i >= 1; i--) {
    bit->bits[i] = bit->bits[i - 1];
  }

  bit->bits[0] = 0;
}

// =======================   BIG DECIMAL UTILITIES   =======================

s21_big_decimal to_big_decimal(s21_decimal bit) {
  s21_big_decimal result = {{0}, 0, 0};

  for (int i = 0; i <= 95; i++) {
    if (getBit(bit, i)) {
      result.bits[i] = 1;
    }
  }

  result.degree = getDegree(bit);
  result.sign = getSign(bit);

  return result;
}

bool is_big_greater(s21_big_decimal a, s21_big_decimal b) {
  bool res = 1;

  for (int i = 191; i >= 0; i--) {
    if (a.bits[i] > b.bits[i]) {
      res = 1;
      break;
    } else if (a.bits[i] < b.bits[i]) {
      res = 0;
      break;
    }
  }

  return res;
}

void big_cpy(s21_big_decimal *value_1, s21_big_decimal value_2) {
  for (int i = 0; i < 192; i++) {
    value_1->bits[i] = value_2.bits[i];
  }

  value_1->degree = value_2.degree;
  value_1->sign = value_2.sign;
}

// ========================   OUTPUT UTILITIES   ========================

void printf_in_ld(s21_big_decimal d) {
  long double res = 0;

  for (int i = 0; i < 192; i++) {
    if (d.bits[i]) {
      res += pow(2, i);
    }
  }

  printf("%Lf\n", res);
}

void printf_bit(s21_decimal d) {
  printf("bits[0]:  ");
  for (int i = 31; i >= 0; i--) {
    printf("%d", getBit(d, i));
  }
  printf("\nbits[1]:  ");
  for (int i = 63; i >= 32; i--) {
    printf("%d", getBit(d, i));
  }
  printf("\nbits[2]:  ");
  for (int i = 95; i >= 64; i--) {
    printf("%d", getBit(d, i));
  }

  printf("\nbits[3]:\n");
  printf("31:    %d", getBit(d, 127));

  printf("\n30-24: ");
  for (int i = 126; i >= 120; i--) {
    printf("%d", getBit(d, i));
  }

  printf("\n23-16: ");
  for (int i = 119; i >= 112; i--) {
    printf("%d", getBit(d, i));
  }

  printf("\n15-0:  ");
  for (int i = 111; i >= 96; i--) {
    printf("%d", getBit(d, i));
  }
  printf("\n\n");
}

void printf_big_bit(s21_big_decimal d) {
  printf("bits[0]:  ");
  for (int i = 31; i >= 0; i--) {
    printf("%d", d.bits[i]);
  }
  printf("\nbits[1]:  ");
  for (int i = 63; i >= 32; i--) {
    printf("%d", d.bits[i]);
  }
  printf("\nbits[2]:  ");
  for (int i = 95; i >= 64; i--) {
    printf("%d", d.bits[i]);
  }
  printf("\nbits[3]:  ");
  for (int i = 127; i >= 96; i--) {
    printf("%d", d.bits[i]);
  }
  printf("\nbits[4]:  ");
  for (int i = 159; i >= 128; i--) {
    printf("%d", d.bits[i]);
  }
  printf("\nbits[5]:  ");
  for (int i = 191; i >= 160; i--) {
    printf("%d", d.bits[i]);
  }
  printf("\n");
  printf("Sign: %d\n", d.sign);
  printf("Scale: %d\n", d.degree);
  printf("Long double representation: ");

  printf_in_ld(d);
  printf("\n\n");
}

// =============================   ARITHMETIC   =============================

void to_decimal(s21_big_decimal value, s21_decimal *result) {
  initDecimal(result);
  for (int i = 0; i < 96; i++) {
    if (value.bits[i]) {
      setBit(result, i);
    }
  }

  setDegree(result, value.degree);
  if (value.sign) {
    setNegSign(result);
  }
}

void add_func(s21_big_decimal *value_1, s21_big_decimal value_2,
              int is_invert) {
  int i = 0, tmp = 0;

  for (; i < 192; i++) {
    if (value_1->bits[i] & value_2.bits[i]) {
      value_1->bits[i] = 0;
      if (tmp) value_1->bits[i] = 1;
      tmp = 1;
    } else if (value_1->bits[i] ^ value_2.bits[i]) {
      if (!tmp) {
        value_1->bits[i] = 1;
      } else {
        value_1->bits[i] = 0;
        tmp = 1;
      }
    } else {
      if (tmp) value_1->bits[i] = 1;
      tmp = 0;
    }
  }

  if (tmp && !is_invert) value_1->bits[i] = 1;
}

void to_additional_code(s21_big_decimal *value) {
  s21_big_decimal tmp = {{0}, 0, 0};
  tmp.bits[0] = 1;

  for (int i = 0; i < 192; i++) {
    value->bits[i] = !value->bits[i];
  }

  add_func(value, tmp, 0);
}

void sign_handler_sub(s21_big_decimal *value_1, s21_big_decimal value_2) {
  if (!value_1->sign && !value_2.sign) {
    if (is_big_greater(*value_1, value_2)) {
      to_additional_code(&value_2);

      add_func(value_1, value_2, 1);
    } else {
      value_1->sign = 1;
      to_additional_code(value_1);

      add_func(value_1, value_2, 1);
    }
  } else if (value_1->sign && !value_2.sign) {
    add_func(value_1, value_2, 0);
  } else if (!value_1->sign && value_2.sign) {
    add_func(value_1, value_2, 0);
  } else if (value_1->sign && value_2.sign) {
    if (is_big_greater(*value_1, value_2)) {
      to_additional_code(&value_2);

      add_func(value_1, value_2, 1);
    } else {
      value_1->sign = 0;
      to_additional_code(value_1);

      add_func(value_1, value_2, 1);
    }
  }
}

s21_big_decimal div_func(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *result) {
  s21_big_decimal mod = {{0}, 0, 0};

  for (int i = 191; i >= 0; i--) {
    bit_shift(&mod);
    bit_shift(result);

    if (value_1.bits[i]) {
      mod.bits[0] = 1;
    }

    if (is_big_greater(mod, value_2)) {
      sign_handler_sub(&mod, value_2);

      result->bits[0] = 1;
    }
  }

  return mod;
}

void scale_decrease(s21_big_decimal *value) {
  s21_decimal divider = {{10, 0, 0, 0}};
  s21_big_decimal tmp = to_big_decimal(divider);

  s21_big_decimal div_res = {{0}, value->sign, value->degree};

  div_func(*value, tmp, &div_res);
  big_cpy(value, div_res);

  value->degree--;
}

void scale_increase(s21_big_decimal *value) {
  s21_big_decimal tmp = {{0}, 0, 0};
  big_cpy(&tmp, *value);

  for (int i = 0; i < 9; i++) {
    add_func(value, tmp, 0);
  }

  value->degree++;
}

void scale_normalization(s21_big_decimal *value_1, s21_big_decimal *value_2) {
  while (value_1->degree < value_2->degree) {
    scale_increase(value_1);
  }

  while (value_1->degree > value_2->degree) {
    scale_increase(value_2);
  }
}

void result_with_scale(s21_big_decimal result, int *code) {
  s21_big_decimal tmp = {{0}, 0, 0};
  big_cpy(&tmp, result);
  int degree = result.degree;

  for (int i = 0; i < degree; i++) {
    scale_decrease(&tmp);
  }

  if (!is_decimal(tmp) && tmp.sign) {
    *code = N_INF;
  } else if (!is_decimal(tmp)) {
    *code = INF;
  }
}

void reduce_to_decimal(s21_big_decimal *result) {
  int digit_count = 0, c = 0;

  s21_big_decimal tmp = {{0}, result->sign, result->degree};
  big_cpy(&tmp, *result);

  while (!is_null(tmp)) {
    scale_decrease(&tmp);
    digit_count++;
  }

  if (result->degree >= digit_count) {
    c = result->degree + 1;
  }
  if (c) {
    for (int i = 0; i < c - 29; i++) {
      scale_decrease(result);
    }
  } else {
    while (!is_decimal(*result)) {
      scale_decrease(result);
    }
  }
}

void sign_handler_add(s21_big_decimal *value_1, s21_big_decimal value_2) {
  if (!value_1->sign && !value_2.sign) {
    add_func(value_1, value_2, 0);
  } else if (value_1->sign && !value_2.sign) {
    if (is_big_greater(*value_1, value_2)) {
      to_additional_code(&value_2);

      add_func(value_1, value_2, 1);
    } else {
      value_1->sign = 0;
      to_additional_code(value_1);

      add_func(value_1, value_2, 1);
    }
  } else if (!value_1->sign && value_2.sign) {
    if (is_big_greater(*value_1, value_2)) {
      to_additional_code(&value_2);

      add_func(value_1, value_2, 1);
    } else {
      value_1->sign = 1;
      to_additional_code(value_1);

      add_func(value_1, value_2, 1);
    }
  } else if (value_1->sign && value_2.sign) {
    add_func(value_1, value_2, 0);
  }
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  initDecimal(result);
  int code = OK;

  s21_big_decimal big_value_1 = to_big_decimal(value_1);
  s21_big_decimal big_value_2 = to_big_decimal(value_2);

  scale_normalization(&big_value_1, &big_value_2);
  sign_handler_add(&big_value_1, big_value_2);

  result_with_scale(big_value_1, &code);

  if (!code) {
    reduce_to_decimal(&big_value_1);
    to_decimal(big_value_1, result);
  }

  return code;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  initDecimal(result);
  int code = OK;

  s21_big_decimal big_value_1 = to_big_decimal(value_1);
  s21_big_decimal big_value_2 = to_big_decimal(value_2);

  scale_normalization(&big_value_1, &big_value_2);
  sign_handler_sub(&big_value_1, big_value_2);

  result_with_scale(big_value_1, &code);

  if (!code) {
    reduce_to_decimal(&big_value_1);
    to_decimal(big_value_1, result);
  }

  return code;
}

void mul_func(s21_big_decimal *value_1, s21_big_decimal value_2) {
  s21_big_decimal res = {{0}, 0, 0};

  if (value_1->sign ^ value_2.sign) {
    res.sign = 1;
  }
  res.degree = value_1->degree + value_2.degree;

  for (int i = 0; i < 192; i++) {
    if (value_2.bits[i]) {
      add_func(&res, *value_1, 0);
    }

    bit_shift(value_1);
  }

  big_cpy(value_1, res);
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  initDecimal(result);
  int code = OK;

  s21_big_decimal big_value_1 = to_big_decimal(value_1);
  s21_big_decimal big_value_2 = to_big_decimal(value_2);

  mul_func(&big_value_1, big_value_2);

  result_with_scale(big_value_1, &code);

  if (!code) {
    reduce_to_decimal(&big_value_1);
    to_decimal(big_value_1, result);
  }

  return code;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  initDecimal(result);
  int code = OK;

  if (value_2.bits[0] + value_2.bits[1] + value_2.bits[2] == 0) {
    code = DIV_ZERO;
  } else {
    s21_big_decimal big_value_1 = to_big_decimal(value_1);
    s21_big_decimal big_value_2 = to_big_decimal(value_2);
    big_value_2.sign = 0;

    s21_big_decimal big_result = {{0}, 0, 0};
    s21_big_decimal div_res = {{0}, 0, 0};

    scale_normalization(&big_value_1, &big_value_2);

    s21_big_decimal mod = div_func(big_value_1, big_value_2, &div_res);
    big_cpy(&big_result, div_res);

    while (is_decimal(big_result)) {
      scale_increase(&mod);
      scale_increase(&big_result);

      s21_big_decimal div_res_tmp = {{0}, 0, 0};
      mod = div_func(mod, big_value_2, &div_res_tmp);

      sign_handler_add(&big_result, div_res_tmp);
    }

    if (getSign(value_1) ^ getSign(value_2)) {
      big_result.sign = 1;
    }

    result_with_scale(big_result, &code);

    if (!code) {
      reduce_to_decimal(&big_result);
      to_decimal(big_result, result);
    }
  }

  return code;
}

bool less_than_one(s21_decimal value) {
  s21_decimal one = {{1, 0, 0, 0}};

  if (getSign(value)) {
    setPosSign(&value);
  }

  return s21_is_less(value, one);
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  initDecimal(result);
  int code = OK;

  if (value_2.bits[0] + value_2.bits[1] + value_2.bits[2] == 0) {
    code = DIV_ZERO;
  } else {
    int sign = 0;

    if (less_than_one(value_2)) {
      setDegree(result, getDegree(value_2));
    }

    if (getSign(value_1) || (getSign(value_1) && getSign(value_2))) {
      sign = 1;
    }
    setPosSign(&value_2);

    s21_big_decimal big_value_1 = to_big_decimal(value_1);
    s21_big_decimal big_value_2 = to_big_decimal(value_2);
    s21_big_decimal mod = {{0}, 0, 0};

    for (int i = 191; i >= 0; i--) {
      bit_shift(&mod);

      if (big_value_1.bits[i]) {
        mod.bits[0] = 1;
      }

      if (is_big_greater(mod, big_value_2)) {
        sign_handler_sub(&mod, big_value_2);
      }
    }

    if (sign) mod.sign = 1;

    to_decimal(mod, result);
  }

  return code;
}

// ====================== comparison ========================
// 0 - FALSE
// 1 - TRUE

int s21_is_less(s21_decimal a, s21_decimal b) {
  int res = 0;
  if ((s21_is_equal(a, b) == 0) && (s21_is_greater(a, b) == 0)) {
    res = 1;
  }
  return res;
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  int res = 0;
  if ((s21_is_equal(a, b) == 1) || (s21_is_greater(a, b) == 0)) {
    res = 1;
  }
  return res;
}

int s21_is_greater(s21_decimal a, s21_decimal b) {
  int res = 0;
  int sign1 = getSign(a);
  int sign2 = getSign(b);
  int deg1 = getDegree(a);
  int deg2 = getDegree(b);

  if (deg1 != deg2) {
    s21_big_decimal big_value_1 = to_big_decimal(a);
    s21_big_decimal big_value_2 = to_big_decimal(b);
    scale_normalization(&big_value_1, &big_value_2);
    to_decimal(big_value_1, &a);
    to_decimal(big_value_2, &b);
    deg1 = getDegree(a);
    deg2 = getDegree(b);
  }
  if (s21_is_equal(a, b) == 1) {
    res = 0;
  } else if (sign1 == 1 && sign2 == 0) {
    res = 0;
  } else if (sign1 == 0 && sign2 == 1) {
    res = 1;
  } else if (sign1 == sign2) {
    for (int i = 95; i >= 0; i--) {
      // если встретили меньшее заканчиваем с успехом
      if (getBit(a, i) > getBit(b, i)) {
        res = 1;
        break;
        // если встретили большее заканчиваем с неудачей
      } else if (getBit(a, i) < getBit(b, i)) {
        res = 0;
        break;
      }
    }
    // если они были отрицательные, то инвертируем ответ
    if (sign1 == 1 && sign2 == 1 && (s21_is_equal(a, b) != 1)) {
      res = !res;
    }
  }
  return res;
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  int res = 0;
  if ((s21_is_equal(a, b) == 1) || (s21_is_greater(a, b) == 1)) {
    res = 1;
  }
  return res;
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
  int res = 0;
  int sign1 = getSign(a);
  int sign2 = getSign(b);
  int deg1 = getDegree(a);
  int deg2 = getDegree(b);

  if (deg1 != deg2) {
    s21_big_decimal big_value_1 = to_big_decimal(a);
    s21_big_decimal big_value_2 = to_big_decimal(b);
    scale_normalization(&big_value_1, &big_value_2);
    to_decimal(big_value_1, &a);
    to_decimal(big_value_2, &b);
    deg1 = getDegree(a);
    deg2 = getDegree(b);
  }
  if (sign1 == sign2 && deg1 == deg2) {
    for (int i = 95; i >= 0; i--) {
      // если встретили не такое значение
      if (getBit(a, i) != getBit(b, i)) {
        res = 0;
        break;

      } else {
        res = 1;
      }
    }
  }
  if (((a.bits[0] + a.bits[1] + a.bits[2]) == 0) &&
      ((b.bits[0] + b.bits[1] + b.bits[2]) == 0)) {
    res = 1;
  }

  return res;
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  int res = 1;
  if (s21_is_equal(a, b) == 1) {
    res = 0;
  }
  return res;
}

// ====================== converters ========================
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int res = 0;
  if (dst == NULL)
    res = 1;
  else {
    initDecimal(dst);
    if (src < 0) {
      setNegSign(dst);
      dst->bits[0] = src * (-1);
    } else {
      setPosSign(dst);
      dst->bits[0] = src;
    }
  }
  return res;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int res = 0;
  if (dst == NULL || getDegree(src) > 28)
    res = 1;
  else {
    *dst = 0;
    long double temp = 0.0;
    int sign = getSign(src);
    int scale = getDegree(src);
    for (int i = 0; i < 96; i++) {
      if (getBit(src, i)) temp += pow(2, (double)i);
    }
    while (scale != 0) {
      temp /= 10;
      scale--;
    }
    if (sign) temp *= -1;
    *dst = temp;
  }
  return res;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = 0;
  if (dst == NULL)
    res = 1;
  else {
    s21_decimal src_tr;
    initDecimal(&src_tr);
    s21_truncate(src, &src_tr);
    unsigned int sign = getSign(src_tr);
    if (sign) setPosSign(&src_tr);
    if (src_tr.bits[1] || src_tr.bits[2] || src_tr.bits[3] ||
        src_tr.bits[0] > (unsigned int)2147483647 + sign) {
      res = 1;
    } else {
      *dst = src_tr.bits[0];
      if (sign) *dst *= -1;
    }
  }
  return res;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (dst) initDecimal(dst);
  int res = 0;
  if (dst == NULL || (fabsf(src) > MAX_DEC) ||
      (fabsf(src) > 0 && fabsf(src) < MIN_DEC) || isnan(src) || isinf(src)) {
    res = 1;
  } else {
    if (src != 0) {
      if (src < 0) setNegSign(dst);
      double temp = (double)fabs(src);
      int off = 0;
      for (; off < 28 && (int)temp / (int)pow(2, 21) == 0; temp *= 10, off++) {
      }
      temp = (float)round(temp);
      for (; fmod(temp, 10) == 0 && off > 0; off--, temp /= 10) {
      }
      src = temp;
      int exp = ((*(int *)&src & ~0x80000000) >> 23) - 127;
      setBit(dst, exp);
      for (int i = exp - 1, j = 22; j >= 0; i--, j--)
        if ((*(int *)&src & (1 << j)) != 0) setBit(dst, i);
      setDegree(dst, off);
    }
  }
  return res;
}

// =================== other functions =====================
int s21_truncate(s21_decimal value, s21_decimal *result) {
  int code = INF;
  int sign = getSign(value);
  int deg = getDegree(value);

  if ((result != NULL) && (deg <= 28) && (deg >= 0)) {
    initDecimal(result);
    code = OK;

    // if int
    if (deg == 0) {
      *result = value;
    } else {
      s21_big_decimal big_value = to_big_decimal(value);
      s21_decimal ten = {{10, 0, 0, 0}};
      s21_big_decimal big_ten = to_big_decimal(ten);
      s21_decimal tmp = {{0, 0, 0, 0}};
      s21_big_decimal big_tmp = to_big_decimal(tmp);

      for (int i = deg; i > 0; i--) {
        div_func(big_value, big_ten, &big_tmp);
        // s21_div(value, ten, &tmp);
        big_value = big_tmp;
      }

      to_decimal(big_tmp, &tmp);
      if (sign == 1) {
        setNegSign(&tmp);
      } else if (sign == 0) {
        setPosSign(&tmp);
      }

      *result = tmp;
    }
  }
  return code;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int code = INF;
  int sign = getSign(value);

  if (result != NULL) {
    initDecimal(result);
    code = OK;
    *result = value;
    // add for zero?
    if (sign == 0) {
      setNegSign(result);
    } else if (sign == 1) {
      setPosSign(result);
    }
  }

  return code;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int code = INF;
  int sign = getSign(value);
  int deg = getDegree(value);
  s21_decimal tmp = {{0, 0, 0, 0}};
  s21_decimal one = {{1, 0, 0, 0}};  // for neg floor

  if (result != NULL && (deg <= 28) && (deg >= 0)) {
    initDecimal(result);
    code = OK;

    if (deg == 0) {
      tmp = value;
    } else {
      if (sign == 0) {
        // 1.1 => 1
        code = s21_truncate(value, &tmp);
      } else if (sign == 1) {
        // -1.1 *-1 => 1.1 => 1 => 1+1 => 2 *-1 => -2
        tmp = value;
        s21_negate(tmp, &tmp);
        code = s21_truncate(tmp, &tmp);
        code = code + s21_add(tmp, one, &tmp);
        s21_negate(tmp, &tmp);
      }
    }
    *result = tmp;
  }
  if (code > 0) {
    code = INF;
  }
  return code;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int code = INF;
  int sign = getSign(value);
  int deg = getDegree(value);

  if (result != NULL) {
    initDecimal(result);
    code = OK;
    if (deg == 0) {
      *result = value;
    } else {
      s21_decimal tmp = {{0, 0, 0, 0}};
      s21_decimal ostatok = {{0, 0, 0, 0}};
      s21_decimal one = {{1, 0, 0, 0}};
      float float_ostatok = 0;
      int int_ostatok = 0;
      // set pos sign
      if (sign == 1) {
        s21_negate(value, &value);
      }

      // 11.7 => 11
      // 11.7 - 11 => 0.7
      // if (0.7 > 0.5) => 11 + 1
      code = s21_truncate(value, &tmp);
      code = code + s21_sub(value, tmp, &ostatok);

      // orig func roundf() => round after 0.999999
      s21_from_decimal_to_float(ostatok, &float_ostatok);
      int_ostatok = (int)(10 * float_ostatok + 0.000001);
      if (int_ostatok >= 5) {
        code = code + s21_add(tmp, one, &tmp);
      }
      // return neg sign
      if (sign == 1) {
        s21_negate(tmp, &tmp);
      }
      *result = tmp;
    }
  }
  if (code > 0) {
    code = INF;
  }
  return code;
}

