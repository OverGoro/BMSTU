#include "check_ho.h"
START_TEST(test_one_ho)
{
    char buf_1[100];
	buf_1[0] = '\0';
    char buf_2[100];
	buf_2[0] = '\0';
    int num = 100;

    int rc_1 = my_snprintf(buf_1, sizeof(buf_1), "%ho", num);
    int rc_2 = snprintf(buf_2, sizeof(buf_2), "%ho", num);
    
    
    ck_assert_int_eq(rc_1, rc_2);
    
	ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(test_one_with_text_ho)
{
    char buf_1[100];
	buf_1[0] = '\0';
    char buf_2[100];
	buf_2[0] = '\0';
    int num = 100;

    int rc_1 = my_snprintf(buf_1, sizeof(buf_1), "===%ho___", num);
    int rc_2 = snprintf(buf_2, sizeof(buf_2), "===%ho___", num);
    
    
    ck_assert_int_eq(rc_1, rc_2);
    
	ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(test_several_ho)
{
    char buf_1[100];
	buf_1[0] = '\0';
    char buf_2[100];
	buf_2[0] = '\0';
    int num = 100;

    int rc_1 = my_snprintf(buf_1, sizeof(buf_1), "%ho%ho%ho", num, num, num);
    int rc_2 = snprintf(buf_2, sizeof(buf_2), "%ho%ho%ho", num, num, num);
    
    
    ck_assert_int_eq(rc_1, rc_2);
    
	ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(test_several_with_text_ho)
{
    char buf_1[100];
	buf_1[0] = '\0';
    char buf_2[100];
	buf_2[0] = '\0';
    int num = 100;

    int rc_1 = my_snprintf(buf_1, sizeof(buf_1), "abc%hoabc%hoho%hoho", num, num, num);
    int rc_2 = snprintf(buf_2, sizeof(buf_2), "abc%hoabc%hoho%hoho", num, num, num);
    
    
    ck_assert_int_eq(rc_1, rc_2);
    
	ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(test_several_minus)
{
    char buf_1[100];
	buf_1[0] = '\0';
    char buf_2[100];
	buf_2[0] = '\0';
    int num = -1;

    int rc_1 = my_snprintf(buf_1, sizeof(buf_1), "abc%hoabc%hoho%hoho", num, num, num);
    int rc_2 = snprintf(buf_2, sizeof(buf_2), "abc%hoabc%hoho%hoho", num, num, num);
    
    
    ck_assert_int_eq(rc_1, rc_2);
    
	ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(test_several_zero)
{
    char buf_1[100];
	buf_1[0] = '\0';
    char buf_2[100];
	buf_2[0] = '\0';
    int num = 0;

    int rc_1 = my_snprintf(buf_1, sizeof(buf_1), "abc%hoabc%hoho%hoho", num, num, num);
    int rc_2 = snprintf(buf_2, sizeof(buf_2), "abc%hoabc%hoho%hoho", num, num, num);
    
    
    ck_assert_int_eq(rc_1, rc_2);
    
	ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(test_few_buffer)
{
    char buf_1[100];
	buf_1[0] = '\0';
    char buf_2[100];
	buf_2[0] = '\0';
    int num = 1000;

    int rc_1 = my_snprintf(buf_1, 4, "%ho", num);
    int rc_2 = snprintf(buf_2, 4, "%ho", num);
    
    ck_assert_int_eq(rc_1, rc_2);
    
	ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

Suite *ho_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("ho");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_one_ho);
    tcase_add_test(tc_core, test_one_with_text_ho);
    tcase_add_test(tc_core, test_several_ho);
    tcase_add_test(tc_core, test_several_with_text_ho);
    tcase_add_test(tc_core, test_several_minus);
    tcase_add_test(tc_core, test_several_zero);
    tcase_add_test(tc_core, test_few_buffer);
    suite_add_tcase(s, tc_core);

    return s;
}

