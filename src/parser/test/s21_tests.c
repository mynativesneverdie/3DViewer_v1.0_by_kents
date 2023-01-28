#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_parser.h"

START_TEST(parse_arr_v) {
  struct info file_struct = {0, 0, 0, 0, 0, 0};

  parse_file("objects/cube.obj", &file_struct);

  ck_assert_float_eq_tol(file_struct.arr_v[0], 0, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[1], 0, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[2], 0, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[3], 0, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[4], 0, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[5], 1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[6], 0, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[7], 1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[8], 0, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[9], 0, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[10], 1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[11], 1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[12], 1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[13], 0, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[14], 0, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[15], 1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[16], 0, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[17], 1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[18], 1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[19], 1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[20], 0, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[21], 1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[22], 1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[23], 1, 1e-6);

  free(file_struct.arr_v);
  free(file_struct.arr_f);
}
END_TEST

START_TEST(parse_arr_f) {
  struct info file_struct = {0, 0, 0, 0, 0, 0};

  parse_file("objects/cube.obj", &file_struct);

  ck_assert_uint_eq(file_struct.arr_f[0], 0);
  ck_assert_uint_eq(file_struct.arr_f[1], 6);
  ck_assert_uint_eq(file_struct.arr_f[2], 6);
  ck_assert_uint_eq(file_struct.arr_f[3], 4);
  ck_assert_uint_eq(file_struct.arr_f[4], 0);
  ck_assert_uint_eq(file_struct.arr_f[5], 4);
  ck_assert_uint_eq(file_struct.arr_f[6], 0);
  ck_assert_uint_eq(file_struct.arr_f[7], 2);
  ck_assert_uint_eq(file_struct.arr_f[8], 2);
  ck_assert_uint_eq(file_struct.arr_f[9], 6);
  ck_assert_uint_eq(file_struct.arr_f[10], 0);
  ck_assert_uint_eq(file_struct.arr_f[11], 6);
  ck_assert_uint_eq(file_struct.arr_f[12], 0);
  ck_assert_uint_eq(file_struct.arr_f[13], 3);
  ck_assert_uint_eq(file_struct.arr_f[14], 3);
  ck_assert_uint_eq(file_struct.arr_f[15], 2);
  ck_assert_uint_eq(file_struct.arr_f[16], 0);
  ck_assert_uint_eq(file_struct.arr_f[17], 2);
  ck_assert_uint_eq(file_struct.arr_f[18], 0);
  ck_assert_uint_eq(file_struct.arr_f[19], 1);
  ck_assert_uint_eq(file_struct.arr_f[20], 1);
  ck_assert_uint_eq(file_struct.arr_f[21], 3);
  ck_assert_uint_eq(file_struct.arr_f[22], 0);
  ck_assert_uint_eq(file_struct.arr_f[23], 3);
  ck_assert_uint_eq(file_struct.arr_f[24], 2);
  ck_assert_uint_eq(file_struct.arr_f[25], 7);
  ck_assert_uint_eq(file_struct.arr_f[26], 7);
  ck_assert_uint_eq(file_struct.arr_f[27], 6);
  ck_assert_uint_eq(file_struct.arr_f[28], 2);
  ck_assert_uint_eq(file_struct.arr_f[29], 6);
  ck_assert_uint_eq(file_struct.arr_f[30], 2);
  ck_assert_uint_eq(file_struct.arr_f[31], 3);
  ck_assert_uint_eq(file_struct.arr_f[32], 3);
  ck_assert_uint_eq(file_struct.arr_f[33], 7);
  ck_assert_uint_eq(file_struct.arr_f[34], 2);
  ck_assert_uint_eq(file_struct.arr_f[35], 7);
  ck_assert_uint_eq(file_struct.arr_f[36], 4);
  ck_assert_uint_eq(file_struct.arr_f[37], 6);
  ck_assert_uint_eq(file_struct.arr_f[38], 6);
  ck_assert_uint_eq(file_struct.arr_f[39], 7);
  ck_assert_uint_eq(file_struct.arr_f[40], 4);
  ck_assert_uint_eq(file_struct.arr_f[41], 7);
  ck_assert_uint_eq(file_struct.arr_f[42], 4);
  ck_assert_uint_eq(file_struct.arr_f[43], 7);
  ck_assert_uint_eq(file_struct.arr_f[44], 7);
  ck_assert_uint_eq(file_struct.arr_f[45], 5);
  ck_assert_uint_eq(file_struct.arr_f[46], 4);
  ck_assert_uint_eq(file_struct.arr_f[47], 5);
  ck_assert_uint_eq(file_struct.arr_f[48], 0);
  ck_assert_uint_eq(file_struct.arr_f[49], 4);
  ck_assert_uint_eq(file_struct.arr_f[50], 4);
  ck_assert_uint_eq(file_struct.arr_f[51], 5);
  ck_assert_uint_eq(file_struct.arr_f[52], 0);
  ck_assert_uint_eq(file_struct.arr_f[53], 5);
  ck_assert_uint_eq(file_struct.arr_f[54], 0);
  ck_assert_uint_eq(file_struct.arr_f[55], 5);
  ck_assert_uint_eq(file_struct.arr_f[56], 5);
  ck_assert_uint_eq(file_struct.arr_f[57], 1);
  ck_assert_uint_eq(file_struct.arr_f[58], 0);
  ck_assert_uint_eq(file_struct.arr_f[59], 1);
  
  free(file_struct.arr_v);
  free(file_struct.arr_f);
}
END_TEST

START_TEST(parser_info) {
  struct info file_struct = {0, 0, 0, 0, 0, 0};

  parse_file("objects/cube.obj", &file_struct);

  ck_assert_uint_eq(file_struct.index_v, 24);
  ck_assert_uint_eq(file_struct.index_f, 60);
  ck_assert_float_eq_tol(file_struct.max_v, 1, 1e-6);

  free(file_struct.arr_v);
  free(file_struct.arr_f);
}
END_TEST

START_TEST(move) {
  struct info file_struct = {0, 0, 0, 0, 0, 0};

  parse_file("objects/cube.obj", &file_struct);

  move_axis(&file_struct, 0.1, 0.1, 0.1);

  ck_assert_float_eq_tol(file_struct.arr_v[0], 0.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[1], 0.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[2], 0.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[3], 0.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[4], 0.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[5], 1.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[6], 0.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[7], 1.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[8], 0.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[9], 0.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[10], 1.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[11], 1.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[12], 1.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[13], 0.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[14], 0.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[15], 1.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[16], 0.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[17], 1.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[18], 1.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[19], 1.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[20], 0.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[21], 1.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[22], 1.1, 1e-6);
  ck_assert_float_eq_tol(file_struct.arr_v[23], 1.1, 1e-6);

  free(file_struct.arr_v);
  free(file_struct.arr_f);
}
END_TEST

Suite *s21_suite(void) {
  Suite *suite;

  suite = suite_create("s21_3d_viewer");
  TCase *tcase_core = tcase_create("s21_3d_viewer");

  tcase_add_test(tcase_core, parse_arr_v);
  tcase_add_test(tcase_core, parse_arr_f);
  tcase_add_test(tcase_core, parser_info);
  tcase_add_test(tcase_core, move);

  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main(void) {
  Suite *suite = s21_suite();

  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_VERBOSE);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  
  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

