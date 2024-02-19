#include "check_all.h"

START_TEST(test_all_one)
{
    char buf_1[100];
	buf_1[0] = '\0';
    char buf_2[100];
	buf_2[0] = '\0';
    int num = 100;
    char str[5] = "abcd";

    int rc_1 = my_snprintf(buf_1, sizeof(buf_1), "%ho%s", num, str);
    int rc_2 = snprintf(buf_2, sizeof(buf_2), "%ho%s", num, str);
    
    ck_assert_int_eq(rc_1, rc_2);
    
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST
START_TEST(test_all_one_text)
{
    char buf_1[100];
	buf_1[0] = '\0';
    char buf_2[100];
	buf_2[0] = '\0';
    int num = 100;
    char str[5] = "abcd";

    int rc_1 = my_snprintf(buf_1, sizeof(buf_1), "abcd%hoabcdef%s\n", num, str);
    int rc_2 = snprintf(buf_2, sizeof(buf_2), "abcd%hoabcdef%s\n", num, str);
    
    ck_assert_int_eq(rc_1, rc_2);
    
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(test_all_several)
{
    char buf_1[100];
	buf_1[0] = '\0';
    char buf_2[100];
	buf_2[0] = '\0';
    int num = 100;
    char str[5] = "abcd";

    int rc_1 = my_snprintf(buf_1, sizeof(buf_1), "%ho%ho%s%s", num, num, str, str);
    int rc_2 = snprintf(buf_2, sizeof(buf_2), "%ho%ho%s%s", num, num, str, str);
    
    ck_assert_int_eq(rc_1, rc_2);
    
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(test_all_several_with_text)
{
    char buf_1[100];
	buf_1[0] = '\0';
    char buf_2[100];
	buf_2[0] = '\0';
    int num = 100;
    char str[5] = "abcd";

    int rc_1 = my_snprintf(buf_1, sizeof(buf_1), "sadasd%hodashd%hosdf%ssdfsdf%sdsfsdfsdf\n\n", num, num, str, str);
    int rc_2 = snprintf(buf_2, sizeof(buf_2), "sadasd%hodashd%hosdf%ssdfsdf%sdsfsdfsdf\n\n", num, num, str, str);
    
    ck_assert_int_eq(rc_1, rc_2);
    
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(test_null_buff)
{
    char *buf_1 = NULL;
    char *buf_2 = NULL;
    int num = 100;
    char str[5] = "abcd";

    int rc_1 = my_snprintf(buf_1, 0, "%ho%ho%s%s\n", num, num, str, str);
    int rc_2 = snprintf(buf_2, 0, "%ho%ho%s%s\n", num, num, str, str);
    
    ck_assert_int_eq(rc_1, rc_2);
    
    ck_assert_ptr_null(buf_1);
    ck_assert_ptr_null(buf_2);
    ck_assert_ptr_eq(buf_1, buf_2);
}
END_TEST

START_TEST(test_null_buff_size)
{
    char buf_1[100];
	buf_1[0] = '\0';
    char buf_2[100];
	buf_2[0] = '\0';
    int num = 100;
    char str[5] = "abcd";

    int rc_1 = my_snprintf(buf_1, 0, "%ho%ho%s%s\n", num, num, str, str);
    int rc_2 = snprintf(buf_2, 0, "%ho%ho%s%s\n", num, num, str, str);
    
    ck_assert_int_eq(rc_1, rc_2);
    
    ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

Suite *all_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("all");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_all_one);
    tcase_add_test(tc_core, test_all_one_text);
    tcase_add_test(tc_core, test_all_several);
    tcase_add_test(tc_core, test_all_several_with_text);
    tcase_add_test(tc_core, test_null_buff);
    tcase_add_test(tc_core, test_null_buff_size);
    suite_add_tcase(s, tc_core);

    return s;
}

