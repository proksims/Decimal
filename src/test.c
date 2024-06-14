#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"

#define EXPONENT_PLUS_1 65536
#define EXPONENT_PLUS_28 1835008
#define INT_MAX 2147483647
#define INT_MIN -2147483648
#define UINT_MAX 4294967295

// =================================================================
START_TEST(s21_floor_1) {
  s21_decimal a = {0};
  ck_assert_int_eq(1, s21_floor(a, NULL));
}
END_TEST

START_TEST(s21_floor_2) {
  s21_decimal a = {0};
  float val = 1.0;
  s21_from_float_to_decimal(val, &a);
  s21_floor(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 1, 0.000001);
}
END_TEST

START_TEST(s21_floor_3) {
  s21_decimal a = {0};
  float val = -1.0;
  s21_from_float_to_decimal(val, &a);
  s21_floor(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -1, 0.000001);
}
END_TEST

START_TEST(s21_floor_4) {
  s21_decimal a = {0};
  float val = 1.111;
  s21_from_float_to_decimal(val, &a);
  s21_floor(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 1, 0.000001);
}
END_TEST

START_TEST(s21_floor_5) {
  s21_decimal a = {0};
  float val = -1.111;
  s21_from_float_to_decimal(val, &a);
  s21_floor(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -2, 0.000001);
}
END_TEST

START_TEST(s21_floor_6) {
  s21_decimal a = {0};
  float val = 1;
  s21_from_float_to_decimal(val, &a);
  s21_floor(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 1, 0.000001);
}
END_TEST

START_TEST(s21_floor_7) {
  s21_decimal a = {0};
  float val = -1.9;
  s21_from_float_to_decimal(val, &a);
  s21_floor(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -2, 0.000001);
}
END_TEST

START_TEST(s21_floor_8) {
  s21_decimal a = {0};
  float val = 1.9999;
  s21_from_float_to_decimal(val, &a);
  s21_floor(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 1, 0.000001);
}
END_TEST

START_TEST(s21_floor_9) {
  s21_decimal a = {0};
  float val = -1.9999;
  s21_from_float_to_decimal(val, &a);
  s21_floor(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -2, 0.000001);
}
END_TEST

START_TEST(s21_floor_10) {
  s21_decimal a = {0};
  float val = 100.9999;
  s21_from_float_to_decimal(val, &a);
  s21_floor(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 100, 0.000001);
}
END_TEST

START_TEST(s21_floor_11) {
  s21_decimal a = {0};
  float val = -100.9999;
  s21_from_float_to_decimal(val, &a);
  s21_floor(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -101, 0.000001);
}
END_TEST

START_TEST(s21_floor_12) {
  s21_decimal a = {0};
  float val = 999998.5;
  s21_from_float_to_decimal(val, &a);
  s21_floor(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 999998, 0.000001);
}
END_TEST

START_TEST(s21_floor_13) {
  s21_decimal a = {0};
  float val = -999998.5;
  s21_from_float_to_decimal(val, &a);
  s21_floor(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -999999, 0.000001);
}
END_TEST

START_TEST(s21_floor_14) {
  // 0.91275848761238746318274123
  s21_decimal dec = {0};
  dec.bits[0] = 598769227;
  dec.bits[1] = 2903911868;
  dec.bits[2] = 4948073;
  dec.bits[3] = 1703936;
  s21_decimal ans;
  s21_decimal true_ans = {0};
  int res = s21_floor(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_floor_15) {
  // -0.91275848761238746318274123
  s21_decimal dec = {0};
  dec.bits[0] = 598769227;
  dec.bits[1] = 2903911868;
  dec.bits[2] = 4948073;
  dec.bits[3] = 1703936;
  s21_negate(dec, &dec);
  s21_decimal ans;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 1;
  s21_negate(true_ans, &true_ans);
  int res = s21_floor(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_floor_16) {
  s21_decimal dec = {0};
  dec.bits[0] = 1;
  dec.bits[1] = 0;
  dec.bits[3] = 0;
  s21_decimal ans;
  s21_decimal true_ans = {{1, 0, 0, 0}};
  int res = s21_floor(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_floor_17) {
  s21_decimal a = {0};
  float val = 0.0;
  s21_from_float_to_decimal(val, &a);
  s21_floor(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 0, 0.000001);
}
END_TEST

START_TEST(s21_floor_18) {
  // 553402.375000
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  float val = 0.0;
  int res = s21_floor(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 553402, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_floor_19) {
  // -55.340240
  s21_decimal a = {.bits = {33, 2, 3000, -2146107392}};
  float val = 0.0;
  int res = s21_floor(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -56, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_floor_20) {
  // -55.340240
  s21_decimal a = {.bits = {33, 2, 3000, -2146107392}};
  float val = 0.0;
  int res = s21_floor(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -56, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

// =================================================================

START_TEST(s21_round_1) {
  s21_decimal a = {0};
  ck_assert_int_eq(1, s21_round(a, NULL));
}
END_TEST

START_TEST(s21_round_2) {
  s21_decimal a = {0};
  float val = 0.0;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 0, 0.000001);
}
END_TEST

START_TEST(s21_round_3) {
  s21_decimal a = {0};
  float val = 0.000009;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 0, 0.000001);
}
END_TEST

START_TEST(s21_round_4) {
  s21_decimal a = {0};
  float val = 0.1;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 0, 0.000001);
}
END_TEST

START_TEST(s21_round_5) {
  s21_decimal a = {0};
  float val = 0.49;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 0, 0.000001);
}
END_TEST

START_TEST(s21_round_6) {
  s21_decimal a = {0};
  float val = 0.5;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 1, 0.000001);
}
END_TEST

START_TEST(s21_round_7) {
  s21_decimal a = {0};
  float val = 0.99;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 1, 0.000001);
}
END_TEST

START_TEST(s21_round_8) {
  s21_decimal a = {0};
  float val = 1.0;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 1, 0.000001);
}
END_TEST

START_TEST(s21_round_9) {
  s21_decimal a = {0};
  float val = 1.4;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 1, 0.000001);
}
END_TEST

START_TEST(s21_round_10) {
  s21_decimal a = {0};
  float val = 1;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 1, 0.000001);
}
END_TEST

START_TEST(s21_round_11) {
  s21_decimal a = {0};
  float val = 1.499999999999;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 2, 0.000001);
}
END_TEST

START_TEST(s21_round_12) {
  s21_decimal a = {0};
  float val = 1.5;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 2, 0.000001);
}
END_TEST

START_TEST(s21_round_13) {
  s21_decimal a = {0};
  float val = 1.5999;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 2, 0.000001);
}
END_TEST

START_TEST(s21_round_14) {
  s21_decimal a = {0};
  float val = -0.1;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 0, 0.000001);
}
END_TEST

START_TEST(s21_round_15) {
  s21_decimal a = {0};
  float val = -0.49;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 0, 0.000001);
}
END_TEST

START_TEST(s21_round_16) {
  s21_decimal a = {0};
  float val = -0.5;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -1, 0.000001);
}
END_TEST

START_TEST(s21_round_17) {
  s21_decimal a = {0};
  float val = -0.99;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -1, 0.000001);
}
END_TEST

START_TEST(s21_round_18) {
  s21_decimal a = {0};
  float val = -1.0;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -1, 0.000001);
}
END_TEST

START_TEST(s21_round_19) {
  s21_decimal a = {0};
  float val = -1.4;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -1, 0.000001);
}
END_TEST

START_TEST(s21_round_20) {
  s21_decimal a = {0};
  float val = -1.49;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -1, 0.000001);
}
END_TEST

START_TEST(s21_round_21) {
  s21_decimal a = {0};
  float val = -1.499999999999;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -2, 0.000001);
}
END_TEST

START_TEST(s21_round_22) {
  s21_decimal a = {0};
  float val = -1.5;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -2, 0.000001);
}
END_TEST

START_TEST(s21_round_23) {
  s21_decimal a = {0};
  float val = -1.5999;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -2, 0.000001);
}
END_TEST

START_TEST(s21_round_24) {
  s21_decimal a = {0};
  float val = -5.5;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -6, 0.000001);
}
END_TEST

START_TEST(s21_round_25) {
  s21_decimal a = {0};
  float val = 1000.4;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 1000, 0.000001);
}
END_TEST

START_TEST(s21_round_26) {
  s21_decimal a = {0};
  float val = -1000.9;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -1001, 0.000001);
}
END_TEST

START_TEST(s21_round_27) {
  // -39.104096094745301845239149102
  s21_decimal dec = {0};
  dec.bits[0] = 178532910;
  dec.bits[1] = 4081246736;
  dec.bits[2] = 2119837296;
  dec.bits[3] = 2149253120;
  s21_decimal ans;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 39;
  s21_negate(true_ans, &true_ans);
  int res = s21_round(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_round_28) {
  // 0.91275848761238746318274123
  s21_decimal dec = {0};
  dec.bits[0] = 598769227;
  dec.bits[1] = 2903911868;
  dec.bits[2] = 4948073;
  dec.bits[3] = 1703936;
  s21_decimal ans;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 1;
  int res = s21_round(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_round_29) {
  // -0.91275848761238746318274123
  s21_decimal dec = {0};
  dec.bits[0] = 598769227;
  dec.bits[1] = 2903911868;
  dec.bits[2] = 4948073;
  dec.bits[3] = 1703936;
  s21_negate(dec, &dec);
  s21_decimal ans;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = 1;
  s21_negate(true_ans, &true_ans);
  int res = s21_round(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_round_30) {
  s21_decimal dec = {0};
  dec.bits[0] = 784662527;
  dec.bits[1] = 11641532;
  dec.bits[3] = 1114112;
  s21_decimal ans;
  s21_decimal true_ans = {{1}};
  int res = s21_round(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_round_31) {
  // 553402.375000
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  float val = 0.0;
  int res = s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 553402, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_round_32) {
  // 0.055340
  s21_decimal a = {.bits = {10, 100, 3, 1376256}};
  float val = 0.0;
  int res = s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 0, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_round_33) {
  // -5534023.500000
  s21_decimal a = {.bits = {16, 100, 3, 851968}};
  float val = 0.0;
  int res = s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 5534023, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_round_34) {
  s21_decimal dec = {0};
  dec.bits[0] = 1;
  dec.bits[1] = 0;
  dec.bits[3] = 0;
  s21_decimal ans;
  s21_decimal true_ans = {{1, 0, 0, 0}};
  int res = s21_round(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

// =================================================================

START_TEST(s21_truncate_1) {
  s21_decimal a = {0};
  ck_assert_int_eq(1, s21_truncate(a, NULL));
}
END_TEST

START_TEST(s21_truncate_2) {
  s21_decimal a = {0};
  float val = 0.0;
  s21_from_float_to_decimal(val, &a);
  s21_truncate(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 0, 0.000001);
}
END_TEST

START_TEST(s21_truncate_3) {
  s21_decimal a = {0};
  float val = 0.123;
  s21_from_float_to_decimal(val, &a);
  s21_truncate(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 0, 0.000001);
}
END_TEST

START_TEST(s21_truncate_4) {
  s21_decimal a = {0};
  float val = 1;
  s21_from_float_to_decimal(val, &a);
  s21_truncate(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 1, 0.000001);
}
END_TEST

START_TEST(s21_truncate_5) {
  s21_decimal a = {0};
  float val = 100.09;
  s21_from_float_to_decimal(val, &a);
  s21_truncate(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 100, 0.000001);
}
END_TEST

START_TEST(s21_truncate_6) {
  s21_decimal a = {0};
  float val = 12345.6789;
  s21_from_float_to_decimal(val, &a);
  s21_truncate(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 12345, 0.000001);
}
END_TEST

START_TEST(s21_truncate_7) {
  s21_decimal a = {0};
  float val = -0.123;
  s21_from_float_to_decimal(val, &a);
  s21_truncate(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 0, 0.000001);
}
END_TEST

START_TEST(s21_truncate_8) {
  s21_decimal a = {0};
  float val = -1.99999;
  s21_from_float_to_decimal(val, &a);
  s21_truncate(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -1, 0.000001);
}
END_TEST

START_TEST(s21_truncate_9) {
  s21_decimal a = {0};
  float val = -100.09;
  s21_from_float_to_decimal(val, &a);
  s21_truncate(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -100, 0.000001);
}
END_TEST

START_TEST(s21_truncate_10) {
  s21_decimal a = {0};
  float val = -12345.6789;
  s21_from_float_to_decimal(val, &a);
  s21_truncate(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -12345, 0.000001);
}
END_TEST

START_TEST(s21_truncate_11) {
  // -39.104096094745301845239149102
  s21_decimal dec = {0};
  dec.bits[0] = 178532910;
  dec.bits[1] = 4081246736;
  dec.bits[2] = 2119837296;
  dec.bits[3] = 2149253120;
  s21_decimal ans;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 39;
  s21_negate(true_ans, &true_ans);
  int res = s21_truncate(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_truncate_12) {
  // 0.91275848761238746318274123
  s21_decimal dec = {0};
  dec.bits[0] = 598769227;
  dec.bits[1] = 2903911868;
  dec.bits[2] = 4948073;
  dec.bits[3] = 1703936;
  s21_decimal ans;
  s21_decimal true_ans = {0};
  int res = s21_truncate(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_truncate_13) {
  // -0.91275848761238746318274123
  s21_decimal dec = {0};
  dec.bits[0] = 598769227;
  dec.bits[1] = 2903911868;
  dec.bits[2] = 4948073;
  dec.bits[3] = 1703936;
  s21_negate(dec, &dec);
  s21_decimal ans;
  s21_decimal true_ans = {0};
  s21_negate(true_ans, &true_ans);
  int res = s21_truncate(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_truncate_14) {
  s21_decimal dec = {0};
  dec.bits[0] = 784662527;
  dec.bits[1] = 11641532;
  dec.bits[3] = 1114112;
  s21_decimal ans;
  s21_decimal true_ans = {0};
  int res = s21_truncate(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_truncate_15) {
  // -63.319000
  s21_decimal a = {.bits = {32444, 100, 343253, -2145976320}};
  float val = 0.0;
  int res = s21_truncate(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -63, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_truncate_16) {
  // 184467.421875
  s21_decimal a = {.bits = {1, 1, 1, 917504}};
  float val = 0.0;
  int res = s21_truncate(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 184467, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_truncate_17) {
  // 0
  s21_decimal a = {.bits = {0, 0, 0, 851968}};
  float val = 0.0;
  int res = s21_truncate(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 0, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_truncate_18) {
  s21_decimal dec = {0};
  dec.bits[0] = 1;
  dec.bits[1] = 0;
  dec.bits[3] = 0;
  s21_decimal ans;
  s21_decimal true_ans = {{1, 0, 0, 0}};
  int res = s21_truncate(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

// =================================================================

START_TEST(s21_negate_1) {
  s21_decimal a = {.bits = {32444, 100, 343253, -2145976320}};
  s21_decimal ans = {0};
  float x, y;
  int res = s21_negate(a, &ans);
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(ans, &y);
  ck_assert_float_eq_tol(-x, y, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_negate_2) {
  s21_decimal a = {.bits = {1, 1, 1, 917504}};
  s21_decimal ans = {0};
  float x, y;
  int res = s21_negate(a, &ans);
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(ans, &y);
  ck_assert_float_eq_tol(-x, y, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_negate_3) {
  s21_decimal a = {.bits = {0, 0, 0, 917504}};
  s21_decimal ans = {0};
  float x, y;
  int res = s21_negate(a, &ans);
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(ans, &y);
  ck_assert_float_eq_tol(-x, y, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

// =================================================================

START_TEST(s21_is_equal_1) {
  // 0
  s21_decimal a = {.bits = {0, 0, 0, 917504}};
  s21_decimal b = {.bits = {0, 0, 0, 917504}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_2) {
  s21_decimal a = {.bits = {0, 0, 0, 917504}};
  s21_decimal b = {.bits = {0, 0, 0, 0}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_3) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, 655360}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_4) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, -2146828288}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_5) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_6) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {10, 2, 3, -2146566144}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_7) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_8) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_9) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_10) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_11) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_12) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_13) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_14) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_15) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_16) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_17) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_18) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_19) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_20) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_21) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_22) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_23) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_24) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_25) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_26) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_27) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_28) {
  s21_decimal a = {.bits = {3, 2, 1, 524288}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_29) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, -2146828288}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_30) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_31) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {10, 2, 3, -2146566144}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_32) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_33) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_34) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {10, 2, 3, -2146566144}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_35) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_36) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_37) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_38) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_39) {
  s21_decimal a = {.bits = {3, 2, 1, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_40) {
  s21_decimal a = {.bits = {3, 2, 1, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_41) {
  s21_decimal a = {.bits = {3, 2, 1, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_42) {
  s21_decimal a = {.bits = {3, 2, 1, -2146959360}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST
START_TEST(s21_is_equal_43) {
  s21_decimal a = {.bits = {3, 2, 1, -2146959360}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_44) {
  s21_decimal a = {.bits = {3, 2, 1, 524288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x == y);
}
END_TEST

START_TEST(s21_is_equal_45) {
  s21_decimal a = {{42, 0}}, b = {{42, 0}};
  ck_assert_uint_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(s21_is_equal_46) {
  s21_decimal a = {{0, 0, 0, 1}}, b = {{0, 0, 0, 2147483647}};
  ck_assert_uint_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(s21_is_equal_47) {
  s21_decimal a = {{0}}, b = {{0}};
  ck_assert_uint_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(s21_is_equal_48) {
  s21_decimal a = {{1, 1, 1, 1}}, b = {{1, 1, 1, 1}};
  ck_assert_uint_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(s21_is_equal_49) {
  s21_decimal a = {{1, 2, 3, 0}}, b = {{1, 1, 3, 0}};
  ck_assert_uint_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(s21_is_equal_50) {
  s21_decimal a = {{1, 1, 1, 0}}, b = {{1, 1, 2, 0}};
  ck_assert_uint_eq(s21_is_equal(a, b), 0);
}
END_TEST
// =================================================================

START_TEST(s21_is_greater_1) {
  // 0
  s21_decimal a = {.bits = {0, 0, 0, 917504}};
  s21_decimal b = {.bits = {0, 0, 0, 917504}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

START_TEST(s21_is_greater_2) {
  s21_decimal a = {.bits = {0, 0, 0, 917504}};
  s21_decimal b = {.bits = {0, 0, 0, 0}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

START_TEST(s21_is_greater_3) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, 655360}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

START_TEST(s21_is_greater_4) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, -2146828288}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

START_TEST(s21_is_greater_5) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

START_TEST(s21_is_greater_6) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {10, 2, 3, -2146566144}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

START_TEST(s21_is_greater_7) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

START_TEST(s21_is_greater_8) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_9) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_10) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

START_TEST(s21_is_greater_11) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

START_TEST(s21_is_greater_12) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

START_TEST(s21_is_greater_13) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_14) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_15) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

START_TEST(s21_is_greater_16) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_17) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_18) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_19) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

START_TEST(s21_is_greater_20) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_21) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_22) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_23) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

START_TEST(s21_is_greater_24) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_25) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_26) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_27) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

START_TEST(s21_is_greater_28) {
  s21_decimal a = {.bits = {3, 2, 1, 524288}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

START_TEST(s21_is_greater_29) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, -2146828288}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

START_TEST(s21_is_greater_30) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_31) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {10, 2, 3, -2146566144}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_32) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_33) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_34) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {10, 2, 3, -2146566144}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

START_TEST(s21_is_greater_35) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

START_TEST(s21_is_greater_36) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

START_TEST(s21_is_greater_37) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_38) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_39) {
  s21_decimal a = {.bits = {3, 2, 1, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_40) {
  s21_decimal a = {.bits = {3, 2, 1, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_41) {
  s21_decimal a = {.bits = {3, 2, 1, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_42) {
  s21_decimal a = {.bits = {3, 2, 1, -2146959360}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST
START_TEST(s21_is_greater_43) {
  s21_decimal a = {.bits = {3, 2, 1, -2146959360}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

START_TEST(s21_is_greater_44) {
  s21_decimal a = {.bits = {3, 2, 1, 524288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x > y);
}
END_TEST

// =================================================================

START_TEST(s21_is_greater_or_equal_1) {
  // 0
  s21_decimal a = {.bits = {0, 0, 0, 917504}};
  s21_decimal b = {.bits = {0, 0, 0, 917504}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

START_TEST(s21_is_greater_or_equal_2) {
  s21_decimal a = {.bits = {0, 0, 0, 917504}};
  s21_decimal b = {.bits = {0, 0, 0, 0}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

START_TEST(s21_is_greater_or_equal_3) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, 655360}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

START_TEST(s21_is_greater_or_equal_4) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, -2146828288}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

START_TEST(s21_is_greater_or_equal_5) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

START_TEST(s21_is_greater_or_equal_6) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {10, 2, 3, -2146566144}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

START_TEST(s21_is_greater_or_equal_7) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

START_TEST(s21_is_greater_or_equal_8) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_9) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_10) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

START_TEST(s21_is_greater_or_equal_11) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

START_TEST(s21_is_greater_or_equal_12) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

START_TEST(s21_is_greater_or_equal_13) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_14) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_15) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

START_TEST(s21_is_greater_or_equal_16) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_17) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_18) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_19) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

START_TEST(s21_is_greater_or_equal_20) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_21) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_22) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_23) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

START_TEST(s21_is_greater_or_equal_24) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_25) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_26) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_27) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

START_TEST(s21_is_greater_or_equal_28) {
  s21_decimal a = {.bits = {3, 2, 1, 524288}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

START_TEST(s21_is_greater_or_equal_29) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, -2146828288}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

START_TEST(s21_is_greater_or_equal_30) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_31) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {10, 2, 3, -2146566144}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_32) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_33) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_34) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {10, 2, 3, -2146566144}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

START_TEST(s21_is_greater_or_equal_35) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

START_TEST(s21_is_greater_or_equal_36) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

START_TEST(s21_is_greater_or_equal_37) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_38) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_39) {
  s21_decimal a = {.bits = {3, 2, 1, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_40) {
  s21_decimal a = {.bits = {3, 2, 1, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_41) {
  s21_decimal a = {.bits = {3, 2, 1, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_42) {
  s21_decimal a = {.bits = {3, 2, 1, -2146959360}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST
START_TEST(s21_is_greater_or_equal_43) {
  s21_decimal a = {.bits = {3, 2, 1, -2146959360}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

START_TEST(s21_is_greater_or_equal_44) {
  s21_decimal a = {.bits = {3, 2, 1, 524288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_greater_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x >= y);
}
END_TEST

// =================================================================

START_TEST(s21_is_not_equal_1) {
  // 0
  s21_decimal a = {.bits = {0, 0, 0, 917504}};
  s21_decimal b = {.bits = {0, 0, 0, 917504}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_2) {
  s21_decimal a = {.bits = {0, 0, 0, 917504}};
  s21_decimal b = {.bits = {0, 0, 0, 0}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_3) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, 655360}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_4) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, -2146828288}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_5) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_6) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {10, 2, 3, -2146566144}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_7) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_8) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_9) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_10) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_11) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_12) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_13) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_14) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_15) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_16) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_17) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_18) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_19) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_20) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_21) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_22) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_23) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_24) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_25) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_26) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_27) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_28) {
  s21_decimal a = {.bits = {3, 2, 1, 524288}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_29) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, -2146828288}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_30) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_31) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {10, 2, 3, -2146566144}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_32) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_33) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_34) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {10, 2, 3, -2146566144}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_35) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_36) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_37) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_38) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_39) {
  s21_decimal a = {.bits = {3, 2, 1, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_40) {
  s21_decimal a = {.bits = {3, 2, 1, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_41) {
  s21_decimal a = {.bits = {3, 2, 1, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_42) {
  s21_decimal a = {.bits = {3, 2, 1, -2146959360}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST
START_TEST(s21_is_not_equal_43) {
  s21_decimal a = {.bits = {3, 2, 1, -2146959360}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_44) {
  s21_decimal a = {.bits = {3, 2, 1, 524288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_not_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x != y);
}
END_TEST

START_TEST(s21_is_not_equal_45) {
  s21_decimal a = {{42, 0}}, b = {{42, 0}};
  ck_assert_uint_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(s21_is_not_equal_46) {
  s21_decimal a = {{0, 0, 0, 2147483647}}, b = {{0, 0, 0, 2147483647}};
  ck_assert_uint_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(s21_is_not_equal_47) {
  s21_decimal a = {{0}}, b = {{0}};
  ck_assert_uint_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

// =================================================================

START_TEST(s21_is_less_1) {
  // 0
  s21_decimal a = {.bits = {0, 0, 0, 917504}};
  s21_decimal b = {.bits = {0, 0, 0, 917504}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_2) {
  s21_decimal a = {.bits = {0, 0, 0, 917504}};
  s21_decimal b = {.bits = {0, 0, 0, 0}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_3) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, 655360}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_4) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, -2146828288}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_5) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_6) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {10, 2, 3, -2146566144}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_7) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_8) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_9) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_10) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_11) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_12) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_13) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_14) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_15) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_16) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_17) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_18) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_19) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_20) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_21) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_22) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_23) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_24) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_25) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_26) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_27) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_28) {
  s21_decimal a = {.bits = {3, 2, 1, 524288}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_29) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, -2146828288}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_30) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_31) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {10, 2, 3, -2146566144}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_32) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_33) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_34) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {10, 2, 3, -2146566144}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_35) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_36) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_37) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_38) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_39) {
  s21_decimal a = {.bits = {3, 2, 1, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_40) {
  s21_decimal a = {.bits = {3, 2, 1, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_41) {
  s21_decimal a = {.bits = {3, 2, 1, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_42) {
  s21_decimal a = {.bits = {3, 2, 1, -2146959360}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST
START_TEST(s21_is_less_43) {
  s21_decimal a = {.bits = {3, 2, 1, -2146959360}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_44) {
  s21_decimal a = {.bits = {3, 2, 1, 524288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x < y);
}
END_TEST

START_TEST(s21_is_less_45) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 0;
  value_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
  setNegSign(&value_2);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
}
END_TEST

// =================================================================

START_TEST(s21_is_less_or_equal_1) {
  // 0
  s21_decimal a = {.bits = {0, 0, 0, 917504}};
  s21_decimal b = {.bits = {0, 0, 0, 917504}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

START_TEST(s21_is_less_or_equal_2) {
  s21_decimal a = {.bits = {0, 0, 0, 917504}};
  s21_decimal b = {.bits = {0, 0, 0, 0}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

START_TEST(s21_is_less_or_equal_3) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, 655360}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

START_TEST(s21_is_less_or_equal_4) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, -2146828288}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

START_TEST(s21_is_less_or_equal_5) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

START_TEST(s21_is_less_or_equal_6) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {10, 2, 3, -2146566144}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

START_TEST(s21_is_less_or_equal_7) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

START_TEST(s21_is_less_or_equal_8) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_9) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_10) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

START_TEST(s21_is_less_or_equal_11) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

START_TEST(s21_is_less_or_equal_12) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

START_TEST(s21_is_less_or_equal_13) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_14) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_15) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

START_TEST(s21_is_less_or_equal_16) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_17) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_18) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_19) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

START_TEST(s21_is_less_or_equal_20) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_21) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_22) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_23) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

START_TEST(s21_is_less_or_equal_24) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {3, 2, 1, -2146828288}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_25) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_26) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_27) {
  s21_decimal a = {.bits = {1, 2, 3, 917504}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

START_TEST(s21_is_less_or_equal_28) {
  s21_decimal a = {.bits = {3, 2, 1, 524288}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

START_TEST(s21_is_less_or_equal_29) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, -2146828288}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

START_TEST(s21_is_less_or_equal_30) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_31) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {10, 2, 3, -2146566144}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_32) {
  s21_decimal a = {.bits = {1, 2, 3, 655360}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_33) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_34) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {10, 2, 3, -2146566144}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

START_TEST(s21_is_less_or_equal_35) {
  s21_decimal a = {.bits = {1, 2, 3, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

START_TEST(s21_is_less_or_equal_36) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, -2146566144}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

START_TEST(s21_is_less_or_equal_37) {
  s21_decimal a = {.bits = {1, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_38) {
  s21_decimal a = {.bits = {10, 2, 3, -2146566144}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_39) {
  s21_decimal a = {.bits = {3, 2, 1, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, -2146959360}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_40) {
  s21_decimal a = {.bits = {3, 2, 1, -2146828288}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_41) {
  s21_decimal a = {.bits = {3, 2, 1, -2146828288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_42) {
  s21_decimal a = {.bits = {3, 2, 1, -2146959360}};
  s21_decimal b = {.bits = {3, 2, 1, 524288}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST
START_TEST(s21_is_less_or_equal_43) {
  s21_decimal a = {.bits = {3, 2, 1, -2146959360}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

START_TEST(s21_is_less_or_equal_44) {
  s21_decimal a = {.bits = {3, 2, 1, 524288}};
  s21_decimal b = {.bits = {1, 2, 3, 917504}};
  int res = s21_is_less_or_equal(a, b);
  float x, y;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  ck_assert_int_eq(res, x <= y);
}
END_TEST

// =============================================================
START_TEST(s21_add_1) {
  s21_decimal a = {.bits = {1, 1, 1, 65536}};
  s21_decimal b = {.bits = {1, 1, 1, 65536}};
  s21_decimal ans_dec = {0};
  int res = s21_add(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x + y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_add_2) {
  s21_decimal a = {.bits = {1, 1, 1, 65536}};
  s21_decimal b = {.bits = {1, 1, 1, 655360}};
  s21_decimal ans_dec = {0};
  int res = s21_add(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x + y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_add_3) {
  s21_decimal a = {.bits = {1, 1, 1, 65536}};
  s21_decimal b = {.bits = {1, 15, 1, 655360}};
  s21_decimal ans_dec = {0};
  int res = s21_add(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x + y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_add_4) {
  s21_decimal a = {.bits = {1, 1, 1, 65536}};
  s21_decimal b = {.bits = {1, 1, 1, -2147418112}};
  s21_decimal ans_dec = {0};
  int res = s21_add(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x + y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
// START_TEST(s21_add_5) {
//   s21_decimal a = {.bits={1,1,1,65536}};
//   s21_decimal b = {.bits={24,1,1,-2147418112}};
//   s21_decimal ans_dec = {0};
//   int res = s21_add(a, b, &ans_dec);
//   float ans_float = 0;
//   s21_from_decimal_to_float(ans_dec, &ans_float);
//   float x, y, z;
//   s21_from_decimal_to_float(a, &x);
//   s21_from_decimal_to_float(b, &y);
//   z = x + y;
//   ck_assert_float_eq_tol(ans_float, z, 0.000001);
//   ck_assert_int_eq(res, 0);
// }
// END_TEST
START_TEST(s21_add_6) {
  s21_decimal a = {.bits = {1, 1, 1, 65536}};
  s21_decimal b = {.bits = {1, 1, 1, 655360}};
  s21_decimal ans_dec = {0};
  int res = s21_add(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x + y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

// START_TEST(s21_add_7) {
//   s21_decimal a = {.bits={24,1,1,-2147418112}};
//   s21_decimal b = {.bits={1,1,1,65536}};
//   s21_decimal ans_dec = {0};
//   int res = s21_add(a, b, &ans_dec);
//   float ans_float = 0;
//   s21_from_decimal_to_float(ans_dec, &ans_float);
//   float x, y, z;
//   s21_from_decimal_to_float(a, &x);
//   s21_from_decimal_to_float(b, &y);
//   z = x + y;
//   ck_assert_float_eq_tol(ans_float, z, 0.000001);
//   ck_assert_int_eq(res, 0);
// }
// END_TEST
START_TEST(s21_add_8) {
  s21_decimal a = {.bits = {24, 1, 1, -2147418112}};
  s21_decimal b = {.bits = {1, 1, 1, 655360}};
  s21_decimal ans_dec = {0};
  int res = s21_add(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x + y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_add_9) {
  s21_decimal a = {.bits = {24, 1, 1, -2147418112}};
  s21_decimal b = {.bits = {1, 15, 1, 655360}};
  s21_decimal ans_dec = {0};
  int res = s21_add(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x + y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_add_10) {
  s21_decimal a = {.bits = {24, 1, 1, -2147418112}};
  s21_decimal b = {.bits = {1, 1, 1, -2147418112}};
  s21_decimal ans_dec = {0};
  int res = s21_add(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x + y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_add_11) {
  s21_decimal a = {.bits = {24, 1, 1, -2147418112}};
  s21_decimal b = {.bits = {1, 1, 1, 655360}};
  s21_decimal ans_dec = {0};
  int res = s21_add(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x + y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_add_12) {
  s21_decimal a = {.bits = {1, 1, 1, 655360}};
  s21_decimal b = {.bits = {1, 1, 1, 65536}};
  s21_decimal ans_dec = {0};
  int res = s21_add(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x + y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_add_13) {
  s21_decimal a = {.bits = {1, 1, 1, 655360}};
  s21_decimal b = {.bits = {1, 1, 1, 655360}};
  s21_decimal ans_dec = {0};
  int res = s21_add(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x + y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_add_14) {
  s21_decimal a = {.bits = {1, 1, 1, 655360}};
  s21_decimal b = {.bits = {1, 15, 1, 655360}};
  s21_decimal ans_dec = {0};
  int res = s21_add(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x + y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_add_15) {
  s21_decimal a = {.bits = {1, 1, 1, 655360}};
  s21_decimal b = {.bits = {1, 1, 1, -2147418112}};
  s21_decimal ans_dec = {0};
  int res = s21_add(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x + y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_add_16) {
  s21_decimal a = {.bits = {1, 15, 1, 655360}};
  s21_decimal b = {.bits = {1, 1, 1, -2147418112}};
  s21_decimal ans_dec = {0};
  int res = s21_add(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x + y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_add_17) {
  s21_decimal a = {.bits = {95, 0, 0, 65536}};
  s21_decimal b = {.bits = {1, 0, 0, 65536}};
  s21_decimal ans_dec = {0};
  int res = s21_add(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x + y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_sub_1) {
  s21_decimal a = {.bits = {1, 1, 1, 65536}};
  s21_decimal b = {.bits = {1, 1, 1, 65536}};
  s21_decimal ans_dec = {0};
  int res = s21_sub(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x - y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_sub_2) {
  s21_decimal a = {.bits = {1, 1, 1, 65536}};
  s21_decimal b = {.bits = {1, 1, 1, 655360}};
  s21_decimal ans_dec = {0};
  int res = s21_sub(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x - y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_sub_3) {
  s21_decimal a = {.bits = {1, 1, 1, 65536}};
  s21_decimal b = {.bits = {1, 15, 1, 655360}};
  s21_decimal ans_dec = {0};
  int res = s21_sub(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x - y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_sub_4) {
  s21_decimal a = {.bits = {1, 1, 1, 65536}};
  s21_decimal b = {.bits = {1, 1, 1, -2147418112}};
  s21_decimal ans_dec = {0};
  int res = s21_sub(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x - y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_sub_5) {
  s21_decimal a = {.bits = {1, 1, 1, 65536}};
  s21_decimal b = {.bits = {24, 1, 1, -2147418112}};
  s21_decimal ans_dec = {0};
  int res = s21_sub(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x - y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_sub_6) {
  s21_decimal a = {.bits = {1, 1, 1, 65536}};
  s21_decimal b = {.bits = {1, 1, 1, 655360}};
  s21_decimal ans_dec = {0};
  int res = s21_sub(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x - y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_sub_7) {
  s21_decimal a = {.bits = {24, 1, 1, -2147418112}};
  s21_decimal b = {.bits = {1, 1, 1, 65536}};
  s21_decimal ans_dec = {0};
  int res = s21_sub(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x - y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_sub_8) {
  s21_decimal a = {.bits = {24, 1, 1, -2147418112}};
  s21_decimal b = {.bits = {1, 1, 1, 655360}};
  s21_decimal ans_dec = {0};
  int res = s21_sub(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x - y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_sub_9) {
  s21_decimal a = {.bits = {24, 1, 1, -2147418112}};
  s21_decimal b = {.bits = {1, 15, 1, 655360}};
  s21_decimal ans_dec = {0};
  int res = s21_sub(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x - y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

// START_TEST(s21_sub_10) {
//   s21_decimal a = {.bits={24,1,1,-2147418112}};
//   s21_decimal b = {.bits={1,1,1,-2147418112}};
//   s21_decimal ans_dec = {0};
//   int res = s21_sub(a, b, &ans_dec);
//   float ans_float = 0;
//   s21_from_decimal_to_float(ans_dec, &ans_float);
//   float x, y, z;
//   s21_from_decimal_to_float(a, &x);
//   s21_from_decimal_to_float(b, &y);
//   z = x - y;
//   ck_assert_float_eq_tol(ans_float, z, 0.000001);
//   ck_assert_int_eq(res, 0);
// }
// END_TEST

START_TEST(s21_sub_11) {
  s21_decimal a = {.bits = {24, 1, 1, -2147418112}};
  s21_decimal b = {.bits = {1, 1, 1, 655360}};
  s21_decimal ans_dec = {0};
  int res = s21_sub(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x - y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_sub_12) {
  s21_decimal a = {.bits = {1, 1, 1, 655360}};
  s21_decimal b = {.bits = {1, 1, 1, 65536}};
  s21_decimal ans_dec = {0};
  int res = s21_sub(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x - y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_sub_13) {
  s21_decimal a = {.bits = {1, 1, 1, 655360}};
  s21_decimal b = {.bits = {1, 1, 1, 655360}};
  s21_decimal ans_dec = {0};
  int res = s21_sub(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x - y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
// START_TEST(s21_sub_14) {
//   s21_decimal a = {.bits={1,1,1,655360}};
//   s21_decimal b = {.bits={1,15,1,655360}};
//   s21_decimal ans_dec = {0};
//   int res = s21_sub(a, b, &ans_dec);
//   float ans_float = 0;
//   s21_from_decimal_to_float(ans_dec, &ans_float);
//   float x, y, z;
//   s21_from_decimal_to_float(a, &x);
//   s21_from_decimal_to_float(b, &y);
//   z = x - y;
//   ck_assert_float_eq_tol(ans_float, z, 0.000001);
//   ck_assert_int_eq(res, 0);
// }
// END_TEST
START_TEST(s21_sub_15) {
  s21_decimal a = {.bits = {1, 1, 1, 655360}};
  s21_decimal b = {.bits = {1, 1, 1, -2147418112}};
  s21_decimal ans_dec = {0};
  int res = s21_sub(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x - y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_sub_16) {
  s21_decimal a = {.bits = {1, 15, 1, 655360}};
  s21_decimal b = {.bits = {1, 1, 1, -2147418112}};
  s21_decimal ans_dec = {0};
  int res = s21_sub(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x - y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_sub_17) {
  s21_decimal a = {.bits = {1, 1, 1, 65536}};
  s21_decimal b = {.bits = {1, 1, 1, -2147418112}};
  s21_decimal ans_dec = {0};
  int res = s21_sub(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x - y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_sub_18) {
  s21_decimal a = {.bits = {1, 1, 1, -2147418112}};
  s21_decimal b = {.bits = {1, 1, 1, -2147418112}};
  s21_decimal ans_dec = {0};
  int res = s21_sub(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x - y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_sub_19) {
  s21_decimal a = {.bits = {1, 1, 1, -2147418112}};
  s21_decimal b = {.bits = {1, 1, 1, 65536}};
  s21_decimal ans_dec = {0};
  int res = s21_sub(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x - y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_sub_20) {
  s21_decimal a = {.bits = {95, 0, 0, 65536}};
  s21_decimal b = {.bits = {1, 0, 0, 65536}};
  s21_decimal ans_dec = {0};
  int res = s21_sub(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x - y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_mul_18) {
  s21_decimal a = {.bits = {1, 1, 1, -2147418112}};
  s21_decimal b = {.bits = {1, 1, 1, -2147418112}};
  s21_decimal ans_dec = {0};
  int res = s21_mul(a, b, &ans_dec);
  ck_assert_int_eq(res, 1);
}
END_TEST
START_TEST(s21_mul_19) {
  s21_decimal a = {.bits = {1, 1, 1, -2147418112}};
  s21_decimal b = {.bits = {1, 1, 1, 65536}};
  s21_decimal ans_dec = {0};
  int res = s21_mul(a, b, &ans_dec);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(s21_mul_20) {
  s21_decimal a = {.bits = {95, 0, 0, 65536}};
  s21_decimal b = {.bits = {1, 0, 0, 65536}};
  s21_decimal ans_dec = {0};
  int res = s21_mul(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x * y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

// START_TEST(s21_mul_21) {
//   s21_decimal a = {.bits={1,1,1,655360}};
//   s21_decimal b = {.bits={1,1,1,655360}};
//   s21_decimal ans_dec = {0};
//   int res = s21_mul(a, b, &ans_dec);
//   float ans_float = 0;
//   s21_from_decimal_to_float(ans_dec, &ans_float);
//   float x, y, z;
//   s21_from_decimal_to_float(a, &x);
//   s21_from_decimal_to_float(b, &y);
//   z = x * y;
//   ck_assert_float_eq_tol(ans_float, z, 0.000001);
//   ck_assert_int_eq(res, 0);
// }
// END_TEST
START_TEST(s21_mul_22) {
  s21_decimal a = {.bits = {1, 0, 0, 655360}};
  s21_decimal b = {.bits = {1, 0, 0, 655360}};
  s21_decimal ans_dec = {0};
  int res = s21_mul(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x * y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_mul_23) {
  s21_decimal a = {.bits = {1, 0, 0, 655360}};
  s21_decimal b = {.bits = {1, 0, 0, -2146828288}};
  s21_decimal ans_dec = {0};
  int res = s21_mul(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x * y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_mul_24) {
  s21_decimal a = {.bits = {1, 0, 1, 917504}};
  s21_decimal b = {.bits = {1, 0, 0, -2146828288}};
  s21_decimal ans_dec = {0};
  int res = s21_mul(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x * y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

// conv tests
//  float to dec
START_TEST(float_to_decimal_1) {
  float a = 1234567890123456789012345678.0;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_2) {
  float a = 123456789012345678901234567.8;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_3) {
  float a = 12345678901234567890123456.78;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_4) {
  float a = 1234567890123456789012345.678;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_5) {
  float a = 123456789012345678901234.5678;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_6) {
  float a = 12345678901234567890123.45678;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_7) {
  float a = 1234567890123456789012.345678;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_8) {
  float a = 123456789012345678901.2345678;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_9) {
  float a = 12345678901234567890.12345678;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_10) {
  float a = 1234567890123456789.012345678;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_11) {
  float a = 123456789012345678.9012345678;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_12) {
  float a = 12345678901234567.89012345678;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_13) {
  float a = 1234567890123456.7890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_14) {
  float a = 123456789012345.67890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_15) {
  float a = 12345678901234.56789012345678;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_16) {
  float a = 1234567890123.4567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_17) {
  float a = 123456789012.34567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_18) {
  float a = 12345678901.234567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_19) {
  float a = 1234567890.1234567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_20) {
  float a = 123456789.01234567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_21) {
  float a = 12345678.901234567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_22) {
  float a = 1234567.8901234567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_23) {
  float a = 123456.78901234567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_24) {
  float a = 12345.678901234567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_25) {
  float a = 1234.5678901234567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_26) {
  float a = 123.45678901234567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_27) {
  float a = 12.345678901234567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1E-06);
}
END_TEST

START_TEST(float_to_decimal_28) {
  float a = 1.2345678901234567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_29) {
  float a = 0.12345678901234567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_30) {
  float a = 1.2e-27;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-28);
}
END_TEST

START_TEST(float_to_decimal_31) {
  float a = 1.2e-26;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-28);
}
END_TEST

START_TEST(float_to_decimal_32) {
  float a = 1.2e-25;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-28);
}
END_TEST

START_TEST(float_to_decimal_33) {
  float a = 1.2e-24;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-28);
}
END_TEST

START_TEST(float_to_decimal_34) {
  float a = 1.2e-23;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-28);
}
END_TEST

START_TEST(float_to_decimal_35) {
  float a = 1.2e-22;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-28);
}
END_TEST

START_TEST(float_to_decimal_36) {
  float a = 1.2e-21;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-27);
}
END_TEST

START_TEST(float_to_decimal_37) {
  float a = 1.2e-20;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-26);
}
END_TEST

START_TEST(float_to_decimal_38) {
  float a = 1.2e-19;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-25);
}
END_TEST

START_TEST(float_to_decimal_39) {
  float a = 1.2e-18;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-24);
}
END_TEST

START_TEST(float_to_decimal_40) {
  float a = 1.2e-17;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-23);
}
END_TEST

START_TEST(float_to_decimal_41) {
  float a = 1.2e-16;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-22);
}
END_TEST

START_TEST(float_to_decimal_42) {
  float a = 1.2e-15;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-21);
}
END_TEST

START_TEST(float_to_decimal_43) {
  float a = 1.2e-14;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-20);
}
END_TEST

START_TEST(float_to_decimal_44) {
  float a = 1.2e-13;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-19);
}
END_TEST

START_TEST(float_to_decimal_45) {
  float a = 1.2e-12;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-18);
}
END_TEST

START_TEST(float_to_decimal_46) {
  float a = 1.2e-11;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-17);
}
END_TEST

START_TEST(float_to_decimal_47) {
  float a = 1.2e-10;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-16);
}
END_TEST

START_TEST(float_to_decimal_48) {
  float a = 1.2e-9;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-15);
}
END_TEST

START_TEST(float_to_decimal_49) {
  float a = 1.2e-8;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-15);
}
END_TEST

START_TEST(float_to_decimal_50) {
  float a = MAX_DEC + 1;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(0, b);
}
END_TEST

START_TEST(float_to_decimal_51) {
  float a = MIN_DEC - 1;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(-1, b);
}
END_TEST

START_TEST(float_to_decimal_52) {
  float a = 0.0;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_53) {
  float a = MAX_DEC;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
}
END_TEST

START_TEST(float_to_decimal_54) {
  s21_decimal val;
  float fl1 = 3;
  float fl2 = 127.1234;
  float fl1_res = 0;
  float fl2_res = 0;

  s21_from_float_to_decimal(fl1, &val);
  s21_from_decimal_to_float(val, &fl1_res);
  ck_assert_double_eq_tol(fl1, fl1_res, 1e-28);
  s21_from_float_to_decimal(fl2, &val);
  s21_from_decimal_to_float(val, &fl2_res);
  ck_assert_double_eq_tol(fl2, fl2_res, 1e-28);
}
END_TEST

START_TEST(float_to_decimal_55) {
  s21_decimal val;
  float fl1 = -128.023;
  float fl2 = 12345.37643764;
  float fl1_res = 0;
  float fl2_res = 0;

  s21_from_float_to_decimal(fl1, &val);
  s21_from_decimal_to_float(val, &fl1_res);
  ck_assert_double_eq_tol(fl1, fl1_res, 1e-4);

  s21_from_float_to_decimal(fl2, &val);
  s21_from_decimal_to_float(val, &fl2_res);
  ck_assert_double_eq_tol(fl2, fl2_res, 1e-2);
}
END_TEST

START_TEST(float_to_decimal_56) {
  s21_decimal val;
  float num = -2147483648;
  s21_from_float_to_decimal(num, &val);
  ck_assert_int_eq(val.bits[0], 2147483648);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 2147483648);
}
END_TEST

START_TEST(float_to_decimal_57) {
  s21_decimal val;
  float fl1 = 22.14836E+03;
  float fl2 = -2.1474836E+09;
  float fl1_res = 0;
  float fl2_res = 0;

  s21_from_float_to_decimal(fl1, &val);
  s21_from_decimal_to_float(val, &fl1_res);
  ck_assert_double_eq_tol(fl1, fl1_res, 1e-28);

  s21_from_float_to_decimal(fl2, &val);
  s21_from_decimal_to_float(val, &fl2_res);
  ck_assert_double_eq_tol(fl2, fl2_res, 1e-28);
}
END_TEST

START_TEST(float_to_decimal_58) {
  s21_decimal val = {0};
  s21_from_float_to_decimal(1.02E+09, &val);
  ck_assert_int_eq(val.bits[0], 1020000000);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_59) {
  s21_decimal val = {0};
  float fl1 = -333.2222;
  float fl2 = -2.1474836E+20;
  float fl1_res = 0;
  float fl2_res = 0;

  s21_from_float_to_decimal(fl1, &val);
  s21_from_decimal_to_float(val, &fl1_res);
  ck_assert_double_eq_tol(fl1, fl1_res, 1e-28);

  s21_from_float_to_decimal(fl2, &val);
  s21_from_decimal_to_float(val, &fl2_res);
  ck_assert_double_eq_tol(fl2, fl2_res, 1e-28);
}
END_TEST

START_TEST(float_to_decimal_60) {
  s21_decimal val = {0};
  float a = 1.0 / 0.0;
  s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_61) {
  s21_decimal val = {0};
  float a = -1.0 / 0.0;
  s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_62) {
  s21_decimal val = {0};
  float a = 1e-30;
  s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_63) {
  s21_decimal dec = {0};
  float tmp = 0;
  float tmp1 = 0.03;
  s21_from_float_to_decimal(tmp1, &dec);
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, tmp1, 1e-06);
}
END_TEST

START_TEST(float_to_decimal_64) {
  s21_decimal dec = {0};
  s21_from_float_to_decimal(-128.023, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -128.023, 1e-04);
}
END_TEST

START_TEST(float_to_decimal_65) {
  s21_decimal dec = {0};
  s21_from_float_to_decimal(-2.1474836E+09, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -2.1474836E+09, 1e-06);
}
END_TEST

START_TEST(float_to_decimal_66) {
  s21_decimal dec = {0};
  s21_from_float_to_decimal(22.14836E+03, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, 22.14836E+03, 1e-06);
}
END_TEST

START_TEST(float_to_decimal_67) {
  s21_decimal dec = {0};
  s21_from_float_to_decimal(1.02E+08, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, 1.02E+08, 1e-06);
}
END_TEST

START_TEST(float_to_decimal_68) {
  s21_decimal dec = {0};
  s21_from_float_to_decimal(-333.2222, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -333.2222, 1e-06);
}
END_TEST

START_TEST(float_to_decimal_69) {
  s21_decimal dec = {0};
  float a = 1.0 / 0.0;
  int ret = s21_from_float_to_decimal(a, &dec);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(float_to_decimal_70) {
  s21_decimal dec = {0};
  float a = -1.0 / 0.0;
  s21_from_float_to_decimal(a, &dec);
  ck_assert_int_eq(dec.bits[0], 0);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_71) {
  float f = 0.03;
  s21_decimal result = {0};
  s21_decimal check = {{3, 0, 0, 0}};
  setDegree(&check, 2);
  int return_value = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(float_to_decimal_72) {
  float f = -128.023;
  s21_decimal result = {0};
  s21_decimal check = {{12802299, 0, 0, 0}};
  setDegree(&check, 5);
  setNegSign(&check);
  int return_value = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(float_to_decimal_73) {
  float f = 1.0 / 0.0;
  s21_decimal result = {0};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

// dec to int
START_TEST(from_decimal_to_int_0) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  setDegree(&val, 5);
  int res = 1234;
  int tmp = 0;
  int *dst = &tmp;
  s21_from_decimal_to_int(val, dst);
  ck_assert_int_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_int_1) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  setBit(&val, 127);
  setDegree(&val, 5);
  int res = -1234;
  int tmp = 0;
  int *dst = &tmp;
  s21_from_decimal_to_int(val, dst);
  ck_assert_int_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_int_2) {
  s21_decimal var = {{0, 0, 0, 0}};
  int value = 0;
  s21_from_int_to_decimal(5, &var);
  s21_from_decimal_to_int(var, &value);
  ck_assert_int_eq(5, value);
}
END_TEST

START_TEST(from_decimal_to_int_4) {
  int n = 666;
  s21_decimal var = {{0, 1, 0, 0}};
  int value = 0;
  s21_from_int_to_decimal(n, &var);
  s21_from_decimal_to_int(var, &value);
  ck_assert_float_eq_tol(n, value, 10);
}
END_TEST

START_TEST(s21_from_decimal_to_int_1) {
  s21_decimal src = {{0}};
  int result = 0, number = 0;
  src.bits[0] = INT_MAX;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_float_eq(number, 2147483647);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_2) {
  s21_decimal src = {{0}};
  int result = 0, number = 0;
  src.bits[0] = 133141;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 133141);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_4) {
  s21_decimal src = {{0}};
  int result = 0, number = 0;
  long int c = 2147483648;
  src.bits[0] = 123451234;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = c;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -123451234);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_5) {
  s21_decimal src = {{0}};
  int result = 0, number = 0;
  long int c = 2147483648;
  src.bits[0] = 18;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = c;  // 2147483648
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -18);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_6) {
  s21_decimal src = {{0}};
  int result = 0, number = 0;
  src.bits[0] = UINT_MAX;
  src.bits[1] = UINT_MAX;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 0);
  ck_assert_int_eq(result, 1);
}
END_TEST

// dec to int

int check, result, code;

START_TEST(s21_test_from_decimal_to_int_0) {
  s21_decimal a = {{100, 0, 0, 0}};
  check = 100;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_1) {
  s21_decimal a = {{INT_MAX, 0, 0, 0}};
  check = INT_MAX;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_3) {
  s21_decimal a = {{INT_MAX, INT_MAX, INT_MAX, 0}};
  check = 0;

  code = s21_from_decimal_to_int(a, &result);
  //   ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_4) {
  s21_decimal a = {{2147483647, 2147483647, 2147483647, 1 >> 31}};
  check = 0;
  code = s21_from_decimal_to_int(a, &result);
  //   ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_7) {
  int result = 0;
  s21_decimal a = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  check = 0;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_8) {
  s21_decimal a = {{2147483648, 2147483647, 2147483647, 1 >> 31}};
  check = 0;
  code = s21_from_decimal_to_int(a, &result);
  //   ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_9) {
  s21_decimal a = {{INT_MAX, 0, 0, INT_MIN}};
  check = -INT_MAX;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_10) {
  s21_decimal a = {{INT_MAX, 0, 0, INT_MIN}};

  check = -INT_MAX;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_11) {
  s21_decimal a = {{INT_MAX, 0, 0, EXPONENT_PLUS_1}};
  check = 214748364;  // (int)(INT_MAX / 10^1)
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_14) {
  s21_decimal a = {{INT_MAX, 0, 0, EXPONENT_PLUS_28}};
  check = 0;  // (int)(INT_MAX / 10^28)
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_15) {
  s21_decimal a;
  a.bits[0] = 0b10000000000000000000000000000000;
  a.bits[1] = 0b00000000000000000000000000000000;
  a.bits[2] = 000000000000000000000000000000000;
  a.bits[3] = 0b10000000000000000000000000000000;
  check = -2147483648;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_16) {
  s21_decimal a;
  a.bits[0] = 0b00000000000000000000000000000001;
  a.bits[1] = 0b00000000000000000000000000000000;
  a.bits[2] = 0b00000000000000000000000000000000;
  a.bits[3] = 0b00000000000000000000000000000000;
  check = 1;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_test_from_decimal_to_int_17) {
  s21_decimal a;
  a.bits[0] = 0b01111111111111111111111111111111;
  a.bits[1] = 0b00000000000000000000000000000000;
  a.bits[2] = 0b00000000000000000000000000000000;
  a.bits[3] = 0b10000000000000000000000000000000;
  check = -2147483647;
  code = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest1) {
  // 6556
  s21_decimal src1;
  // src1 = 2;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  int result = 0;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 2);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest2) {
  // 6570
  s21_decimal src1;
  // src1 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  int result = 0;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest3) {
  // 6584
  s21_decimal src1;
  // src1 = 3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  int result = 0;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 3);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest4) {
  // 6598
  s21_decimal src1;
  // src1 = 4.5;

  src1.bits[0] = 0b00000000000000000000000000101101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  int result = 0;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 4);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest5) {
  // 6612
  s21_decimal src1;
  // src1 = -4.5;

  src1.bits[0] = 0b00000000000000000000000000101101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  int result = 0;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -4);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest11) {
  // 6696
  s21_decimal src1;
  // src1 = 1;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  int result = 0;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest12) {
  // 6710
  s21_decimal src1;
  // src1 = 1.25;

  src1.bits[0] = 0b00000000000000000000000001111101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000100000000000000000;
  int result = 0;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest13) {
  // 6724
  s21_decimal src1;
  // src1 = -1.25;

  src1.bits[0] = 0b00000000000000000000000001111101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000100000000000000000;
  int result = 0;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -1);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest14) {
  // 6738
  s21_decimal src1;
  // src1 = -12.25;

  src1.bits[0] = 0b00000000000000000000010011001001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000100000000000000000;
  int result = 0;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -12);
}
END_TEST

START_TEST(s21_from_decimal_to_intTest15) {
  // 6752
  s21_decimal src1;
  // src1 = -3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  int result = 0;
  int *res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -3);
}
END_TEST

// dec to float
START_TEST(from_decimal_to_float_0) {
  s21_decimal val = {{1234567, 0, 0, 0}};
  setDegree(&val, 5);
  float res = 12.34567;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq_tol(*dst, res, 10e-6);
}
END_TEST

START_TEST(from_decimal_to_float_1) {
  s21_decimal val = {{1234567, 0, 0, 0}};
  setBit(&val, 127);
  setDegree(&val, 5);
  float res = -12.34567;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq_tol(*dst, res, 10e-6);
}
END_TEST

START_TEST(from_decimal_to_float_2) {
  s21_decimal var = {{0, 0, 0, 0}};
  float value = 0;
  s21_from_float_to_decimal(5.0, &var);
  s21_from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(5.0, value, 10e-5);
}
END_TEST

START_TEST(from_decimal_to_float_3) {
  float n = 123123.213235;
  s21_decimal var = {{0, 0, 0, 0}};
  float value = 0;
  s21_from_float_to_decimal(n, &var);
  s21_from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(n, value, 10);
}
END_TEST

START_TEST(from_decimal_to_float_4) {
  float n = -1e-6;
  s21_decimal var = {{0, 0, 0, 0}};
  float value = 0;
  s21_from_float_to_decimal(n, &var);
  s21_from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(n, value, 10);
}
END_TEST

START_TEST(s21_from_decimal_to_float_1) {
  s21_decimal var = {0};
  float value = 0;
  s21_from_float_to_decimal(5.0, &var);
  s21_from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(5.0, value, 10e-5);
}
END_TEST

START_TEST(s21_from_decimal_to_float_2) {
  float n = -876867;
  s21_decimal var = {0};
  float value = 0;
  s21_from_float_to_decimal(n, &var);
  s21_from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(n, value, 10);
}
END_TEST

START_TEST(s21_from_decimal_to_float_3) {
  float n = -1e-6;
  s21_decimal var = {0};
  float value = 0;
  s21_from_float_to_decimal(n, &var);
  s21_from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(n, value, 10);
}
END_TEST

START_TEST(s21_from_decimal_to_float_4) {
  s21_decimal value = {{1812, 0, 0, 0}};
  setNegSign(&value);
  float result = 0;
  float check = -1812;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_5) {
  s21_decimal value = {{18122, 0, 0, 0}};
  setDegree(&value, 3);
  setNegSign(&value);
  float result = 0;
  float check = -18.122;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_6) {
  s21_decimal value = {{0xFFFFFF, 0, 0, 0}};
  float result = 0;
  float check = 16777215;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_7) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  float result = 0;
  float check = 0xFFFFFFFFFFFFFFFF;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_8) {
  s21_decimal src = {0};
  int result = 0;
  float number = 0.0;
  src.bits[0] = 23450987;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 2147745792;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq_tol(number, -2345.0988, 1e-03);
  ck_assert_int_eq(result, 0);
}
END_TEST

// int to dec
int a, add, equal;
START_TEST(from_int_to_decimal_0) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = -2147483648;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal_1) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = -123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal_2) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = 2147483647;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(s21_from_int_to_decimal_1) {
  s21_decimal val = {0};

  s21_from_int_to_decimal(0, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  initDecimal(&val);
  s21_from_int_to_decimal(-128, &val);
  ck_assert_int_eq(val.bits[0], 128);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 2147483648);

  initDecimal(&val);
  s21_from_int_to_decimal(127, &val);
  ck_assert_int_eq(val.bits[0], 127);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  initDecimal(&val);
  s21_from_int_to_decimal(-2147483648, &val);
  ck_assert_int_eq(val.bits[0], 2147483648);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 2147483648);

  initDecimal(&val);
  s21_from_int_to_decimal(2147483647, &val);
  ck_assert_int_eq(val.bits[0], 2147483647);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal_0) {
  a = 100;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;

  add = s21_from_int_to_decimal(a, ptr_b);  // a записываем в b
  s21_decimal etalon = {{100, 0, 0, 0}};
  ck_assert_int_eq(add, 0);
  // выходное значение s21_from_int_to_decimal - 0 TRUE и 1 FALSE
  // s21_is_equal Возвращаемое значение: 0 - FALSE 1 - TRUE
  equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal_1) {
  a = 100;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;

  add = s21_from_int_to_decimal(a, ptr_b);  // a записываем в b
  s21_decimal etalon = {{1000, 0, 0, 0}};
  ck_assert_int_eq(add, 0);
  // выходное значение s21_from_int_to_decimal -
  // 0 TRUE и 1 FALSE
  // s21_is_equal Возвращаемое значение: 0 - FALSE 1 - TRUE
  equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, 0);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal_2) {
  a = INT_MAX;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;

  add = s21_from_int_to_decimal(a, ptr_b);  // a записываем в b
  s21_decimal etalon = {{INT_MAX, 0, 0, 0}};
  ck_assert_int_eq(add, 0);  // выходное значение s21_from_int_to_decimal -
                             // 0 TRUE и 1 FALSE
  // s21_is_equal Возвращаемое значение: 0 - FALSE 1 - TRUE
  equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal_3) {
  a = -INT_MAX;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;

  add = s21_from_int_to_decimal(a, ptr_b);  // a записываем в b
  s21_decimal etalon = {{INT_MAX, 0, 0, 0}};
  ck_assert_int_eq(add, 0);  // выходное значение s21_from_int_to_decimal -
                             // 0 TRUE и 1 FALSE
  // s21_is_equal Возвращаемое значение: 0 - FALSE 1 - TRUE
  equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, 0);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal_4) {
  a = -INT_MAX;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;

  add = s21_from_int_to_decimal(a, ptr_b);  // a записываем в b
  s21_decimal etalon = {{INT_MAX, 0, 0, ~(INT_MAX)}};
  ck_assert_int_eq(add, 0);  // выходное значение s21_from_int_to_decimal -
                             // 0 TRUE и 1 FALSE
  // s21_is_equal Возвращаемое значение: 0 - FALSE 1 - TRUE
  equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal_5) {
  a = 0;  // ERROR of NAN
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;

  add = s21_from_int_to_decimal(a, ptr_b);  // a записываем в b
  s21_decimal etalon = {{INT_MAX, 0, 0, ~(INT_MAX)}};
  ck_assert_int_eq(add, 0);  // выходное значение s21_from_int_to_decimal -
                             // 0 TRUE и 1 FALSE
  // s21_is_equal Возвращаемое значение: 0 - FALSE 1 - TRUE
  equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, 0);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest1) {
  // 6412
  int src1 = 1;
  s21_decimal origin = {0}, result = {0};
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest2) {
  // 6428
  int src1 = -1;
  s21_decimal origin = {0}, result = {0};
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest3) {
  // 6444
  int src1 = 0;
  s21_decimal origin = {0}, result = {0};
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest4) {
  // 6460
  int src1 = 0;
  s21_decimal origin = {0}, result = {0};
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest5) {
  // 6476
  int src1 = -987879878;
  s21_decimal origin = {0}, result = {0};
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00111010111000011101100111000110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest6) {
  // 6492
  int src1 = -2147483646;
  s21_decimal origin = {0}, result = {0};
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b01111111111111111111111111111110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest7) {
  // 6508
  int src1 = 2147483646;
  s21_decimal origin = {0}, result = {0};
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b01111111111111111111111111111110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest8) {
  // 6524
  int src1 = 796132784;
  s21_decimal origin = {0}, result = {0};
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00101111011101000000010110110000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest9) {
  // 6540
  int src1 = -12345677;
  s21_decimal origin = {0}, result = {0};
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);
  origin.bits[0] = 0b00000000101111000110000101001101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_div_1) {
  s21_decimal a = {.bits = {1, 1, 1, 655360}};
  s21_decimal b = {.bits = {1, 1, 1, 655360}};
  s21_decimal ans_dec = {0};
  int res = s21_div(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x / y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_div_2) {
  s21_decimal a = {.bits = {1, 1, 1, 655360}};
  s21_decimal b = {.bits = {1, 1, 1, 983040}};
  s21_decimal ans_dec = {0};
  int res = s21_div(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x / y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_div_3) {
  s21_decimal a = {
      .bits = {
          1, 1, 1,
          655360}};  // 10000000000000000000000000000101000000000000000000000000000000001
                     // 18446744078004518913
  s21_decimal b = {.bits = {1, 10, 1, -2146500608}};  // 18446744116659224577
  s21_decimal ans_dec = {0};
  int res = s21_div(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x / y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_div_4) {
  s21_decimal a = {.bits = {1, 1, 1, 983040}};
  s21_decimal b = {.bits = {1, 1, 1, -2146500608}};
  s21_decimal ans_dec = {0};
  int res = s21_div(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x / y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_div_5) {
  s21_decimal a = {.bits = {1, 2, 1, 983040}};
  s21_decimal b = {.bits = {1, 1, 1, -2146500608}};
  s21_decimal ans_dec = {0};
  int res = s21_div(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x / y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_div_6) {
  s21_decimal a = {.bits = {1, 2, 1, 983040}};
  s21_decimal b = {.bits = {1, 0, 0, -2146500608}};
  s21_decimal ans_dec = {0};
  int res = s21_div(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x / y;
  ck_assert_float_eq_tol(ans_float, z, 0.000001);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_div_7) {
  s21_decimal a = {.bits = {1, 1, 1, 983040}};
  s21_decimal b = {.bits = {0, 0, 0, 0}};
  s21_decimal ans_dec = {0};
  int res = s21_div(a, b, &ans_dec);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(s21_div_8) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 9;
  dec1.bits[3] = 65536;
  dec2.bits[0] = 6;
  dec2.bits[3] = 65536;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 15;
  true_ans.bits[3] = 65536;
  int res = s21_div(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_div_9) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 2814903;
  dec1.bits[3] = 65536;
  dec2.bits[0] = 0;
  int res = s21_div(dec1, dec2, &ans);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(s21_div_10) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  a.bits[2] = 65536;
  b.bits[0] = 4578783;
  s21_decimal ans_dec = {0};
  int res = s21_div(a, b, &ans_dec);
  float ans_float = 0;
  s21_from_decimal_to_float(ans_dec, &ans_float);
  float x, y, z;
  s21_from_decimal_to_float(a, &x);
  s21_from_decimal_to_float(b, &y);
  z = x / y;
  ck_assert_float_eq_tol(ans_float, z, 1e+11);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_div_11) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 4294967294;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;
  dec2.bits[0] = 1;
  dec2.bits[3] = 1179648;
  int res = s21_div(dec1, dec2, &ans);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_div_12) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 4294967294;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;
  dec2.bits[0] = 1;
  setDegree(&dec2, 10);
  // set_exp(10, &(dec2.bits[3]));
  s21_negate(dec2, &dec2);
  int res = s21_div(dec1, dec2, &ans);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(s21_div_14) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;
  dec2.bits[0] = 1;
  setDegree(&dec1, 10);
  setDegree(&dec2, 10);
  // set_exp(10, &(dec2.bits[3]));
  // set_exp(10, &(dec1.bits[3]));
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 4294967295;
  true_ans.bits[1] = 4294967295;
  true_ans.bits[2] = 4294967295;
  int res = s21_div(dec1, dec2, &ans);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_div_15) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 1188260494;
  dec1.bits[1] = 2547073670;
  dec1.bits[2] = 423;
  dec1.bits[3] = 786432;
  dec2.bits[0] = 1658453339;
  dec2.bits[1] = 2896612263;
  dec2.bits[2] = 67010;
  dec2.bits[3] = 786432;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 2998137797;
  true_ans.bits[1] = 614149364;
  true_ans.bits[2] = 3426771;
  true_ans.bits[3] = 1835008;
  int res = s21_div(dec1, dec2, &ans);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_mod_1) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 10;
  dec2.bits[0] = 4;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 2;
  int res = s21_mod(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_mod_2) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 4036421147;
  dec1.bits[1] = 382;
  dec1.bits[2] = 262144;
  dec2.bits[0] = 2945631615;
  dec2.bits[1] = 658;
  dec2.bits[2] = 2147876864;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 867247046;
  true_ans.bits[1] = 90;
  true_ans.bits[2] = 393216;
  int res = s21_mod(dec1, dec2, &ans);
  ck_assert_int_eq(0, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_mod_3) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;
  dec2.bits[0] = 1;
  s21_decimal true_ans = {0};
  int res = s21_mod(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_mod_4) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;
  dec2.bits[0] = 1;
  s21_decimal true_ans = {0};
  int res = s21_mod(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_mod_5) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;
  dec2.bits[0] = 0;
  setDegree(&dec1, 5);
  setDegree(&dec2, 2);

  // set_exp(5, &(dec1.bits[3]));
  // set_exp(2, &(dec2.bits[3]));
  int res = s21_mod(dec1, dec2, &ans);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(s21_mod_6) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 5;
  dec2.bits[0] = 10;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 5;
  int res = s21_mod(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}

START_TEST(s21_mod_7) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 5;
  s21_negate(dec1, &dec1);
  dec2.bits[0] = 10;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 5;
  s21_negate(true_ans, &true_ans);
  int res = s21_mod(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}

START_TEST(s21_mod_8) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 10;
  dec2.bits[0] = 10;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 0;
  int res = s21_mod(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}

START_TEST(s21_mod_9) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 0;
  dec2.bits[0] = 10;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 0;
  int res = s21_mod(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}

Suite *suite_insert(void) {
  Suite *s = suite_create("suite_insert");
  TCase *tc_core = tcase_create("insert_tc");

  tcase_add_test(tc_core, s21_floor_1);
  tcase_add_test(tc_core, s21_floor_2);
  tcase_add_test(tc_core, s21_floor_3);
  tcase_add_test(tc_core, s21_floor_4);
  tcase_add_test(tc_core, s21_floor_5);
  tcase_add_test(tc_core, s21_floor_6);
  tcase_add_test(tc_core, s21_floor_7);
  tcase_add_test(tc_core, s21_floor_8);
  tcase_add_test(tc_core, s21_floor_9);
  tcase_add_test(tc_core, s21_floor_10);
  tcase_add_test(tc_core, s21_floor_11);
  tcase_add_test(tc_core, s21_floor_12);
  tcase_add_test(tc_core, s21_floor_13);
  tcase_add_test(tc_core, s21_floor_14);
  tcase_add_test(tc_core, s21_floor_15);
  tcase_add_test(tc_core, s21_floor_16);
  tcase_add_test(tc_core, s21_floor_17);
  tcase_add_test(tc_core, s21_floor_18);
  tcase_add_test(tc_core, s21_floor_19);
  tcase_add_test(tc_core, s21_floor_20);

  tcase_add_test(tc_core, s21_round_1);
  tcase_add_test(tc_core, s21_round_2);
  tcase_add_test(tc_core, s21_round_3);
  tcase_add_test(tc_core, s21_round_4);
  tcase_add_test(tc_core, s21_round_5);
  tcase_add_test(tc_core, s21_round_6);
  tcase_add_test(tc_core, s21_round_7);
  tcase_add_test(tc_core, s21_round_8);
  tcase_add_test(tc_core, s21_round_9);
  tcase_add_test(tc_core, s21_round_10);
  tcase_add_test(tc_core, s21_round_11);
  tcase_add_test(tc_core, s21_round_12);
  tcase_add_test(tc_core, s21_round_13);
  tcase_add_test(tc_core, s21_round_14);
  tcase_add_test(tc_core, s21_round_15);
  tcase_add_test(tc_core, s21_round_16);
  tcase_add_test(tc_core, s21_round_17);
  tcase_add_test(tc_core, s21_round_18);
  tcase_add_test(tc_core, s21_round_19);
  tcase_add_test(tc_core, s21_round_20);
  tcase_add_test(tc_core, s21_round_21);
  tcase_add_test(tc_core, s21_round_22);
  tcase_add_test(tc_core, s21_round_23);
  tcase_add_test(tc_core, s21_round_24);
  tcase_add_test(tc_core, s21_round_25);
  tcase_add_test(tc_core, s21_round_26);
  tcase_add_test(tc_core, s21_round_27);
  tcase_add_test(tc_core, s21_round_28);
  tcase_add_test(tc_core, s21_round_29);
  tcase_add_test(tc_core, s21_round_30);
  tcase_add_test(tc_core, s21_round_31);
  tcase_add_test(tc_core, s21_round_32);
  tcase_add_test(tc_core, s21_round_33);
  tcase_add_test(tc_core, s21_round_34);

  tcase_add_test(tc_core, s21_truncate_1);
  tcase_add_test(tc_core, s21_truncate_2);
  tcase_add_test(tc_core, s21_truncate_3);
  tcase_add_test(tc_core, s21_truncate_4);
  tcase_add_test(tc_core, s21_truncate_5);
  tcase_add_test(tc_core, s21_truncate_6);
  tcase_add_test(tc_core, s21_truncate_7);
  tcase_add_test(tc_core, s21_truncate_8);
  tcase_add_test(tc_core, s21_truncate_9);
  tcase_add_test(tc_core, s21_truncate_10);
  tcase_add_test(tc_core, s21_truncate_11);
  tcase_add_test(tc_core, s21_truncate_12);
  tcase_add_test(tc_core, s21_truncate_13);
  tcase_add_test(tc_core, s21_truncate_14);
  tcase_add_test(tc_core, s21_truncate_15);
  tcase_add_test(tc_core, s21_truncate_16);
  tcase_add_test(tc_core, s21_truncate_17);
  tcase_add_test(tc_core, s21_truncate_18);

  tcase_add_test(tc_core, s21_negate_1);
  tcase_add_test(tc_core, s21_negate_2);
  tcase_add_test(tc_core, s21_negate_3);

  tcase_add_test(tc_core, s21_is_equal_1);
  tcase_add_test(tc_core, s21_is_equal_2);
  tcase_add_test(tc_core, s21_is_equal_3);
  tcase_add_test(tc_core, s21_is_equal_4);
  tcase_add_test(tc_core, s21_is_equal_5);
  tcase_add_test(tc_core, s21_is_equal_6);
  tcase_add_test(tc_core, s21_is_equal_7);
  tcase_add_test(tc_core, s21_is_equal_8);
  tcase_add_test(tc_core, s21_is_equal_9);
  tcase_add_test(tc_core, s21_is_equal_10);
  tcase_add_test(tc_core, s21_is_equal_11);
  tcase_add_test(tc_core, s21_is_equal_12);
  tcase_add_test(tc_core, s21_is_equal_13);
  tcase_add_test(tc_core, s21_is_equal_14);
  tcase_add_test(tc_core, s21_is_equal_15);
  tcase_add_test(tc_core, s21_is_equal_16);
  tcase_add_test(tc_core, s21_is_equal_17);
  tcase_add_test(tc_core, s21_is_equal_18);
  tcase_add_test(tc_core, s21_is_equal_19);
  tcase_add_test(tc_core, s21_is_equal_20);
  tcase_add_test(tc_core, s21_is_equal_21);
  tcase_add_test(tc_core, s21_is_equal_22);
  tcase_add_test(tc_core, s21_is_equal_23);
  tcase_add_test(tc_core, s21_is_equal_24);
  tcase_add_test(tc_core, s21_is_equal_25);
  tcase_add_test(tc_core, s21_is_equal_26);
  tcase_add_test(tc_core, s21_is_equal_27);
  tcase_add_test(tc_core, s21_is_equal_28);
  tcase_add_test(tc_core, s21_is_equal_29);
  tcase_add_test(tc_core, s21_is_equal_30);
  tcase_add_test(tc_core, s21_is_equal_31);
  tcase_add_test(tc_core, s21_is_equal_32);
  tcase_add_test(tc_core, s21_is_equal_33);
  tcase_add_test(tc_core, s21_is_equal_34);
  tcase_add_test(tc_core, s21_is_equal_35);
  tcase_add_test(tc_core, s21_is_equal_36);
  tcase_add_test(tc_core, s21_is_equal_37);
  tcase_add_test(tc_core, s21_is_equal_38);
  tcase_add_test(tc_core, s21_is_equal_39);
  tcase_add_test(tc_core, s21_is_equal_40);
  tcase_add_test(tc_core, s21_is_equal_41);
  tcase_add_test(tc_core, s21_is_equal_42);
  tcase_add_test(tc_core, s21_is_equal_43);
  tcase_add_test(tc_core, s21_is_equal_44);
  tcase_add_test(tc_core, s21_is_equal_45);
  tcase_add_test(tc_core, s21_is_equal_46);
  tcase_add_test(tc_core, s21_is_equal_47);
  tcase_add_test(tc_core, s21_is_equal_48);
  tcase_add_test(tc_core, s21_is_equal_49);
  tcase_add_test(tc_core, s21_is_equal_50);

  tcase_add_test(tc_core, s21_is_greater_1);
  tcase_add_test(tc_core, s21_is_greater_2);
  tcase_add_test(tc_core, s21_is_greater_3);
  tcase_add_test(tc_core, s21_is_greater_4);
  tcase_add_test(tc_core, s21_is_greater_5);
  tcase_add_test(tc_core, s21_is_greater_6);
  tcase_add_test(tc_core, s21_is_greater_7);
  tcase_add_test(tc_core, s21_is_greater_8);
  tcase_add_test(tc_core, s21_is_greater_9);
  tcase_add_test(tc_core, s21_is_greater_10);
  tcase_add_test(tc_core, s21_is_greater_11);
  tcase_add_test(tc_core, s21_is_greater_12);
  tcase_add_test(tc_core, s21_is_greater_13);
  tcase_add_test(tc_core, s21_is_greater_14);
  tcase_add_test(tc_core, s21_is_greater_15);
  tcase_add_test(tc_core, s21_is_greater_16);
  tcase_add_test(tc_core, s21_is_greater_17);
  tcase_add_test(tc_core, s21_is_greater_18);
  tcase_add_test(tc_core, s21_is_greater_19);
  tcase_add_test(tc_core, s21_is_greater_20);
  tcase_add_test(tc_core, s21_is_greater_21);
  tcase_add_test(tc_core, s21_is_greater_22);
  tcase_add_test(tc_core, s21_is_greater_23);
  tcase_add_test(tc_core, s21_is_greater_24);
  tcase_add_test(tc_core, s21_is_greater_25);
  tcase_add_test(tc_core, s21_is_greater_26);
  tcase_add_test(tc_core, s21_is_greater_27);
  tcase_add_test(tc_core, s21_is_greater_28);
  tcase_add_test(tc_core, s21_is_greater_29);
  tcase_add_test(tc_core, s21_is_greater_30);
  tcase_add_test(tc_core, s21_is_greater_31);
  tcase_add_test(tc_core, s21_is_greater_32);
  tcase_add_test(tc_core, s21_is_greater_33);
  tcase_add_test(tc_core, s21_is_greater_34);
  tcase_add_test(tc_core, s21_is_greater_35);
  tcase_add_test(tc_core, s21_is_greater_36);
  tcase_add_test(tc_core, s21_is_greater_37);
  tcase_add_test(tc_core, s21_is_greater_38);
  tcase_add_test(tc_core, s21_is_greater_39);
  tcase_add_test(tc_core, s21_is_greater_40);
  tcase_add_test(tc_core, s21_is_greater_41);
  tcase_add_test(tc_core, s21_is_greater_42);
  tcase_add_test(tc_core, s21_is_greater_43);
  tcase_add_test(tc_core, s21_is_greater_44);

  tcase_add_test(tc_core, s21_is_greater_or_equal_1);
  tcase_add_test(tc_core, s21_is_greater_or_equal_2);
  tcase_add_test(tc_core, s21_is_greater_or_equal_3);
  tcase_add_test(tc_core, s21_is_greater_or_equal_4);
  tcase_add_test(tc_core, s21_is_greater_or_equal_5);
  tcase_add_test(tc_core, s21_is_greater_or_equal_6);
  tcase_add_test(tc_core, s21_is_greater_or_equal_7);
  tcase_add_test(tc_core, s21_is_greater_or_equal_8);
  tcase_add_test(tc_core, s21_is_greater_or_equal_9);
  tcase_add_test(tc_core, s21_is_greater_or_equal_10);
  tcase_add_test(tc_core, s21_is_greater_or_equal_11);
  tcase_add_test(tc_core, s21_is_greater_or_equal_12);
  tcase_add_test(tc_core, s21_is_greater_or_equal_13);
  tcase_add_test(tc_core, s21_is_greater_or_equal_14);
  tcase_add_test(tc_core, s21_is_greater_or_equal_15);
  tcase_add_test(tc_core, s21_is_greater_or_equal_16);
  tcase_add_test(tc_core, s21_is_greater_or_equal_17);
  tcase_add_test(tc_core, s21_is_greater_or_equal_18);
  tcase_add_test(tc_core, s21_is_greater_or_equal_19);
  tcase_add_test(tc_core, s21_is_greater_or_equal_20);
  tcase_add_test(tc_core, s21_is_greater_or_equal_21);
  tcase_add_test(tc_core, s21_is_greater_or_equal_22);
  tcase_add_test(tc_core, s21_is_greater_or_equal_23);
  tcase_add_test(tc_core, s21_is_greater_or_equal_24);
  tcase_add_test(tc_core, s21_is_greater_or_equal_25);
  tcase_add_test(tc_core, s21_is_greater_or_equal_26);
  tcase_add_test(tc_core, s21_is_greater_or_equal_27);
  tcase_add_test(tc_core, s21_is_greater_or_equal_28);
  tcase_add_test(tc_core, s21_is_greater_or_equal_29);
  tcase_add_test(tc_core, s21_is_greater_or_equal_30);
  tcase_add_test(tc_core, s21_is_greater_or_equal_31);
  tcase_add_test(tc_core, s21_is_greater_or_equal_32);
  tcase_add_test(tc_core, s21_is_greater_or_equal_33);
  tcase_add_test(tc_core, s21_is_greater_or_equal_34);
  tcase_add_test(tc_core, s21_is_greater_or_equal_35);
  tcase_add_test(tc_core, s21_is_greater_or_equal_36);
  tcase_add_test(tc_core, s21_is_greater_or_equal_37);
  tcase_add_test(tc_core, s21_is_greater_or_equal_38);
  tcase_add_test(tc_core, s21_is_greater_or_equal_39);
  tcase_add_test(tc_core, s21_is_greater_or_equal_40);
  tcase_add_test(tc_core, s21_is_greater_or_equal_41);
  tcase_add_test(tc_core, s21_is_greater_or_equal_42);
  tcase_add_test(tc_core, s21_is_greater_or_equal_43);
  tcase_add_test(tc_core, s21_is_greater_or_equal_44);

  tcase_add_test(tc_core, s21_is_not_equal_1);
  tcase_add_test(tc_core, s21_is_not_equal_2);
  tcase_add_test(tc_core, s21_is_not_equal_3);
  tcase_add_test(tc_core, s21_is_not_equal_4);
  tcase_add_test(tc_core, s21_is_not_equal_5);
  tcase_add_test(tc_core, s21_is_not_equal_6);
  tcase_add_test(tc_core, s21_is_not_equal_7);
  tcase_add_test(tc_core, s21_is_not_equal_8);
  tcase_add_test(tc_core, s21_is_not_equal_9);
  tcase_add_test(tc_core, s21_is_not_equal_10);
  tcase_add_test(tc_core, s21_is_not_equal_11);
  tcase_add_test(tc_core, s21_is_not_equal_12);
  tcase_add_test(tc_core, s21_is_not_equal_13);
  tcase_add_test(tc_core, s21_is_not_equal_14);
  tcase_add_test(tc_core, s21_is_not_equal_15);
  tcase_add_test(tc_core, s21_is_not_equal_16);
  tcase_add_test(tc_core, s21_is_not_equal_17);
  tcase_add_test(tc_core, s21_is_not_equal_18);
  tcase_add_test(tc_core, s21_is_not_equal_19);
  tcase_add_test(tc_core, s21_is_not_equal_20);
  tcase_add_test(tc_core, s21_is_not_equal_21);
  tcase_add_test(tc_core, s21_is_not_equal_22);
  tcase_add_test(tc_core, s21_is_not_equal_23);
  tcase_add_test(tc_core, s21_is_not_equal_24);
  tcase_add_test(tc_core, s21_is_not_equal_25);
  tcase_add_test(tc_core, s21_is_not_equal_26);
  tcase_add_test(tc_core, s21_is_not_equal_27);
  tcase_add_test(tc_core, s21_is_not_equal_28);
  tcase_add_test(tc_core, s21_is_not_equal_29);
  tcase_add_test(tc_core, s21_is_not_equal_30);
  tcase_add_test(tc_core, s21_is_not_equal_31);
  tcase_add_test(tc_core, s21_is_not_equal_32);
  tcase_add_test(tc_core, s21_is_not_equal_33);
  tcase_add_test(tc_core, s21_is_not_equal_34);
  tcase_add_test(tc_core, s21_is_not_equal_35);
  tcase_add_test(tc_core, s21_is_not_equal_36);
  tcase_add_test(tc_core, s21_is_not_equal_37);
  tcase_add_test(tc_core, s21_is_not_equal_38);
  tcase_add_test(tc_core, s21_is_not_equal_39);
  tcase_add_test(tc_core, s21_is_not_equal_40);
  tcase_add_test(tc_core, s21_is_not_equal_41);
  tcase_add_test(tc_core, s21_is_not_equal_42);
  tcase_add_test(tc_core, s21_is_not_equal_43);
  tcase_add_test(tc_core, s21_is_not_equal_44);
  tcase_add_test(tc_core, s21_is_not_equal_45);
  tcase_add_test(tc_core, s21_is_not_equal_46);
  tcase_add_test(tc_core, s21_is_not_equal_47);

  tcase_add_test(tc_core, s21_is_less_1);
  tcase_add_test(tc_core, s21_is_less_2);
  tcase_add_test(tc_core, s21_is_less_3);
  tcase_add_test(tc_core, s21_is_less_4);
  tcase_add_test(tc_core, s21_is_less_5);
  tcase_add_test(tc_core, s21_is_less_6);
  tcase_add_test(tc_core, s21_is_less_7);
  tcase_add_test(tc_core, s21_is_less_8);
  tcase_add_test(tc_core, s21_is_less_9);
  tcase_add_test(tc_core, s21_is_less_10);
  tcase_add_test(tc_core, s21_is_less_11);
  tcase_add_test(tc_core, s21_is_less_12);
  tcase_add_test(tc_core, s21_is_less_13);
  tcase_add_test(tc_core, s21_is_less_14);
  tcase_add_test(tc_core, s21_is_less_15);
  tcase_add_test(tc_core, s21_is_less_16);
  tcase_add_test(tc_core, s21_is_less_17);
  tcase_add_test(tc_core, s21_is_less_18);
  tcase_add_test(tc_core, s21_is_less_19);
  tcase_add_test(tc_core, s21_is_less_20);
  tcase_add_test(tc_core, s21_is_less_21);
  tcase_add_test(tc_core, s21_is_less_22);
  tcase_add_test(tc_core, s21_is_less_23);
  tcase_add_test(tc_core, s21_is_less_24);
  tcase_add_test(tc_core, s21_is_less_25);
  tcase_add_test(tc_core, s21_is_less_26);
  tcase_add_test(tc_core, s21_is_less_27);
  tcase_add_test(tc_core, s21_is_less_28);
  tcase_add_test(tc_core, s21_is_less_29);
  tcase_add_test(tc_core, s21_is_less_30);
  tcase_add_test(tc_core, s21_is_less_31);
  tcase_add_test(tc_core, s21_is_less_32);
  tcase_add_test(tc_core, s21_is_less_33);
  tcase_add_test(tc_core, s21_is_less_34);
  tcase_add_test(tc_core, s21_is_less_35);
  tcase_add_test(tc_core, s21_is_less_36);
  tcase_add_test(tc_core, s21_is_less_37);
  tcase_add_test(tc_core, s21_is_less_38);
  tcase_add_test(tc_core, s21_is_less_39);
  tcase_add_test(tc_core, s21_is_less_40);
  tcase_add_test(tc_core, s21_is_less_41);
  tcase_add_test(tc_core, s21_is_less_42);
  tcase_add_test(tc_core, s21_is_less_43);
  tcase_add_test(tc_core, s21_is_less_44);
  tcase_add_test(tc_core, s21_is_less_45);

  tcase_add_test(tc_core, s21_is_less_or_equal_1);
  tcase_add_test(tc_core, s21_is_less_or_equal_2);
  tcase_add_test(tc_core, s21_is_less_or_equal_3);
  tcase_add_test(tc_core, s21_is_less_or_equal_4);
  tcase_add_test(tc_core, s21_is_less_or_equal_5);
  tcase_add_test(tc_core, s21_is_less_or_equal_6);
  tcase_add_test(tc_core, s21_is_less_or_equal_7);
  tcase_add_test(tc_core, s21_is_less_or_equal_8);
  tcase_add_test(tc_core, s21_is_less_or_equal_9);
  tcase_add_test(tc_core, s21_is_less_or_equal_10);
  tcase_add_test(tc_core, s21_is_less_or_equal_11);
  tcase_add_test(tc_core, s21_is_less_or_equal_12);
  tcase_add_test(tc_core, s21_is_less_or_equal_13);
  tcase_add_test(tc_core, s21_is_less_or_equal_14);
  tcase_add_test(tc_core, s21_is_less_or_equal_15);
  tcase_add_test(tc_core, s21_is_less_or_equal_16);
  tcase_add_test(tc_core, s21_is_less_or_equal_17);
  tcase_add_test(tc_core, s21_is_less_or_equal_18);
  tcase_add_test(tc_core, s21_is_less_or_equal_19);
  tcase_add_test(tc_core, s21_is_less_or_equal_20);
  tcase_add_test(tc_core, s21_is_less_or_equal_21);
  tcase_add_test(tc_core, s21_is_less_or_equal_22);
  tcase_add_test(tc_core, s21_is_less_or_equal_23);
  tcase_add_test(tc_core, s21_is_less_or_equal_24);
  tcase_add_test(tc_core, s21_is_less_or_equal_25);
  tcase_add_test(tc_core, s21_is_less_or_equal_26);
  tcase_add_test(tc_core, s21_is_less_or_equal_27);
  tcase_add_test(tc_core, s21_is_less_or_equal_28);
  tcase_add_test(tc_core, s21_is_less_or_equal_29);
  tcase_add_test(tc_core, s21_is_less_or_equal_30);
  tcase_add_test(tc_core, s21_is_less_or_equal_31);
  tcase_add_test(tc_core, s21_is_less_or_equal_32);
  tcase_add_test(tc_core, s21_is_less_or_equal_33);
  tcase_add_test(tc_core, s21_is_less_or_equal_34);
  tcase_add_test(tc_core, s21_is_less_or_equal_35);
  tcase_add_test(tc_core, s21_is_less_or_equal_36);
  tcase_add_test(tc_core, s21_is_less_or_equal_37);
  tcase_add_test(tc_core, s21_is_less_or_equal_38);
  tcase_add_test(tc_core, s21_is_less_or_equal_39);
  tcase_add_test(tc_core, s21_is_less_or_equal_40);
  tcase_add_test(tc_core, s21_is_less_or_equal_41);
  tcase_add_test(tc_core, s21_is_less_or_equal_42);
  tcase_add_test(tc_core, s21_is_less_or_equal_43);
  tcase_add_test(tc_core, s21_is_less_or_equal_44);

  tcase_add_test(tc_core, s21_add_1);
  tcase_add_test(tc_core, s21_add_2);
  tcase_add_test(tc_core, s21_add_3);
  tcase_add_test(tc_core, s21_add_4);
  // tcase_add_test(tc_core, s21_add_5);
  tcase_add_test(tc_core, s21_add_6);
  // tcase_add_test(tc_core, s21_add_7);
  tcase_add_test(tc_core, s21_add_8);
  tcase_add_test(tc_core, s21_add_9);
  tcase_add_test(tc_core, s21_add_10);
  tcase_add_test(tc_core, s21_add_11);
  tcase_add_test(tc_core, s21_add_12);
  tcase_add_test(tc_core, s21_add_13);
  tcase_add_test(tc_core, s21_add_14);
  tcase_add_test(tc_core, s21_add_15);
  tcase_add_test(tc_core, s21_add_16);
  tcase_add_test(tc_core, s21_add_17);

  tcase_add_test(tc_core, s21_sub_1);
  tcase_add_test(tc_core, s21_sub_2);
  tcase_add_test(tc_core, s21_sub_3);
  tcase_add_test(tc_core, s21_sub_4);
  tcase_add_test(tc_core, s21_sub_5);
  tcase_add_test(tc_core, s21_sub_6);
  tcase_add_test(tc_core, s21_sub_7);
  tcase_add_test(tc_core, s21_sub_8);
  tcase_add_test(tc_core, s21_sub_9);
  // tcase_add_test(tc_core, s21_sub_10);
  tcase_add_test(tc_core, s21_sub_11);
  tcase_add_test(tc_core, s21_sub_12);
  tcase_add_test(tc_core, s21_sub_13);
  // tcase_add_test(tc_core, s21_sub_14);
  tcase_add_test(tc_core, s21_sub_15);
  tcase_add_test(tc_core, s21_sub_16);
  tcase_add_test(tc_core, s21_sub_17);
  tcase_add_test(tc_core, s21_sub_18);
  tcase_add_test(tc_core, s21_sub_19);
  tcase_add_test(tc_core, s21_sub_20);

  tcase_add_test(tc_core, s21_mul_18);
  tcase_add_test(tc_core, s21_mul_19);
  tcase_add_test(tc_core, s21_mul_20);
  // tcase_add_test(tc_core, s21_mul_21);
  tcase_add_test(tc_core, s21_mul_22);
  tcase_add_test(tc_core, s21_mul_23);
  tcase_add_test(tc_core, s21_mul_24);

  // float to dec
  tcase_add_test(tc_core, float_to_decimal_1);
  tcase_add_test(tc_core, float_to_decimal_2);
  tcase_add_test(tc_core, float_to_decimal_3);
  tcase_add_test(tc_core, float_to_decimal_4);
  tcase_add_test(tc_core, float_to_decimal_5);
  tcase_add_test(tc_core, float_to_decimal_6);
  tcase_add_test(tc_core, float_to_decimal_7);
  tcase_add_test(tc_core, float_to_decimal_8);
  tcase_add_test(tc_core, float_to_decimal_9);
  tcase_add_test(tc_core, float_to_decimal_10);
  tcase_add_test(tc_core, float_to_decimal_11);
  tcase_add_test(tc_core, float_to_decimal_12);
  tcase_add_test(tc_core, float_to_decimal_13);
  tcase_add_test(tc_core, float_to_decimal_14);
  tcase_add_test(tc_core, float_to_decimal_15);
  tcase_add_test(tc_core, float_to_decimal_16);
  tcase_add_test(tc_core, float_to_decimal_17);
  tcase_add_test(tc_core, float_to_decimal_18);
  tcase_add_test(tc_core, float_to_decimal_19);
  tcase_add_test(tc_core, float_to_decimal_20);
  tcase_add_test(tc_core, float_to_decimal_21);
  tcase_add_test(tc_core, float_to_decimal_22);
  tcase_add_test(tc_core, float_to_decimal_23);
  tcase_add_test(tc_core, float_to_decimal_24);
  tcase_add_test(tc_core, float_to_decimal_25);
  tcase_add_test(tc_core, float_to_decimal_26);
  tcase_add_test(tc_core, float_to_decimal_27);
  tcase_add_test(tc_core, float_to_decimal_28);
  tcase_add_test(tc_core, float_to_decimal_29);
  tcase_add_test(tc_core, float_to_decimal_30);
  tcase_add_test(tc_core, float_to_decimal_31);
  tcase_add_test(tc_core, float_to_decimal_32);
  tcase_add_test(tc_core, float_to_decimal_33);
  tcase_add_test(tc_core, float_to_decimal_34);
  tcase_add_test(tc_core, float_to_decimal_35);
  tcase_add_test(tc_core, float_to_decimal_36);
  tcase_add_test(tc_core, float_to_decimal_37);
  tcase_add_test(tc_core, float_to_decimal_38);
  tcase_add_test(tc_core, float_to_decimal_39);
  tcase_add_test(tc_core, float_to_decimal_40);
  tcase_add_test(tc_core, float_to_decimal_41);
  tcase_add_test(tc_core, float_to_decimal_42);
  tcase_add_test(tc_core, float_to_decimal_43);
  tcase_add_test(tc_core, float_to_decimal_44);
  tcase_add_test(tc_core, float_to_decimal_45);
  tcase_add_test(tc_core, float_to_decimal_46);
  tcase_add_test(tc_core, float_to_decimal_47);
  tcase_add_test(tc_core, float_to_decimal_48);
  tcase_add_test(tc_core, float_to_decimal_49);
  tcase_add_test(tc_core, float_to_decimal_50);
  tcase_add_test(tc_core, float_to_decimal_51);
  tcase_add_test(tc_core, float_to_decimal_52);
  tcase_add_test(tc_core, float_to_decimal_53);
  tcase_add_test(tc_core, float_to_decimal_54);
  tcase_add_test(tc_core, float_to_decimal_55);
  tcase_add_test(tc_core, float_to_decimal_56);
  tcase_add_test(tc_core, float_to_decimal_57);
  tcase_add_test(tc_core, float_to_decimal_58);
  tcase_add_test(tc_core, float_to_decimal_59);
  tcase_add_test(tc_core, float_to_decimal_60);
  tcase_add_test(tc_core, float_to_decimal_61);
  tcase_add_test(tc_core, float_to_decimal_62);
  tcase_add_test(tc_core, float_to_decimal_63);
  tcase_add_test(tc_core, float_to_decimal_64);
  tcase_add_test(tc_core, float_to_decimal_65);
  tcase_add_test(tc_core, float_to_decimal_66);
  tcase_add_test(tc_core, float_to_decimal_67);
  tcase_add_test(tc_core, float_to_decimal_68);
  tcase_add_test(tc_core, float_to_decimal_69);
  tcase_add_test(tc_core, float_to_decimal_70);
  tcase_add_test(tc_core, float_to_decimal_71);
  tcase_add_test(tc_core, float_to_decimal_72);
  tcase_add_test(tc_core, float_to_decimal_73);

  // dec to int
  tcase_add_test(tc_core, from_decimal_to_int_0);
  tcase_add_test(tc_core, from_decimal_to_int_1);
  tcase_add_test(tc_core, from_decimal_to_int_2);
  tcase_add_test(tc_core, from_decimal_to_int_4);
  tcase_add_test(tc_core, s21_from_decimal_to_int_1);
  tcase_add_test(tc_core, s21_from_decimal_to_int_2);
  tcase_add_test(tc_core, s21_from_decimal_to_int_4);
  tcase_add_test(tc_core, s21_from_decimal_to_int_5);
  tcase_add_test(tc_core, s21_from_decimal_to_int_6);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_0);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_1);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_3);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_4);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_7);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_8);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_9);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_10);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_11);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_14);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_15);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_16);
  tcase_add_test(tc_core, s21_test_from_decimal_to_int_17);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest1);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest2);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest3);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest4);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest5);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest11);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest12);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest13);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest14);
  tcase_add_test(tc_core, s21_from_decimal_to_intTest15);

  // dec to float

  tcase_add_test(tc_core, from_decimal_to_float_0);
  tcase_add_test(tc_core, from_decimal_to_float_1);
  tcase_add_test(tc_core, from_decimal_to_float_2);
  tcase_add_test(tc_core, from_decimal_to_float_3);
  tcase_add_test(tc_core, from_decimal_to_float_4);
  tcase_add_test(tc_core, s21_from_decimal_to_float_1);
  tcase_add_test(tc_core, s21_from_decimal_to_float_2);
  tcase_add_test(tc_core, s21_from_decimal_to_float_3);
  tcase_add_test(tc_core, s21_from_decimal_to_float_4);
  tcase_add_test(tc_core, s21_from_decimal_to_float_5);
  tcase_add_test(tc_core, s21_from_decimal_to_float_6);
  tcase_add_test(tc_core, s21_from_decimal_to_float_7);
  tcase_add_test(tc_core, s21_from_decimal_to_float_8);

  // int to dec
  tcase_add_test(tc_core, from_int_to_decimal_0);
  tcase_add_test(tc_core, from_int_to_decimal_1);
  tcase_add_test(tc_core, from_int_to_decimal_2);
  tcase_add_test(tc_core, s21_from_int_to_decimal_1);

  tcase_add_test(tc_core, s21_test_from_int_to_decimal_0);
  tcase_add_test(tc_core, s21_test_from_int_to_decimal_1);
  tcase_add_test(tc_core, s21_test_from_int_to_decimal_2);
  tcase_add_test(tc_core, s21_test_from_int_to_decimal_3);
  tcase_add_test(tc_core, s21_test_from_int_to_decimal_4);
  tcase_add_test(tc_core, s21_test_from_int_to_decimal_5);
  tcase_add_test(tc_core, s21_from_int_to_decimalTest1);
  tcase_add_test(tc_core, s21_from_int_to_decimalTest2);
  tcase_add_test(tc_core, s21_from_int_to_decimalTest3);
  tcase_add_test(tc_core, s21_from_int_to_decimalTest4);
  tcase_add_test(tc_core, s21_from_int_to_decimalTest5);
  tcase_add_test(tc_core, s21_from_int_to_decimalTest6);
  tcase_add_test(tc_core, s21_from_int_to_decimalTest7);
  tcase_add_test(tc_core, s21_from_int_to_decimalTest8);
  tcase_add_test(tc_core, s21_from_int_to_decimalTest9);
  tcase_add_test(tc_core, from_int_to_decimal_0);
  tcase_add_test(tc_core, from_int_to_decimal_1);

  tcase_add_test(tc_core, s21_div_1);
  tcase_add_test(tc_core, s21_div_2);
  tcase_add_test(tc_core, s21_div_3);
  tcase_add_test(tc_core, s21_div_4);
  tcase_add_test(tc_core, s21_div_5);
  tcase_add_test(tc_core, s21_div_6);
  tcase_add_test(tc_core, s21_div_7);
  tcase_add_test(tc_core, s21_div_8);
  tcase_add_test(tc_core, s21_div_9);
  tcase_add_test(tc_core, s21_div_10);
  tcase_add_test(tc_core, s21_div_11);
  tcase_add_test(tc_core, s21_div_12);
  tcase_add_test(tc_core, s21_div_14);
  tcase_add_test(tc_core, s21_div_15);

  tcase_add_test(tc_core, s21_mod_1);
  tcase_add_test(tc_core, s21_mod_2);
  tcase_add_test(tc_core, s21_mod_3);
  tcase_add_test(tc_core, s21_mod_4);
  tcase_add_test(tc_core, s21_mod_5);
  tcase_add_test(tc_core, s21_mod_6);
  tcase_add_test(tc_core, s21_mod_7);
  tcase_add_test(tc_core, s21_mod_8);
  tcase_add_test(tc_core, s21_mod_9);

  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  int fail;
  Suite *s;
  SRunner *sr;
  s = suite_insert();
  sr = srunner_create(s);
  fail = srunner_ntests_failed(sr);

  // srunner_run_all(sr, CK_VERBOSE);
  //  srunner_run_all(sr, CK_NORMAL);
  srunner_run_all(sr, CK_ENV);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_free(sr);
  return fail == 0 ? 0 : 1;
}
