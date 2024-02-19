#include "check_s.h"
START_TEST(test_one_s)
{
    char buf_1[100];
	buf_1[0] = '\0';
    char buf_2[100];
	buf_2[0] = '\0';
    char str[5] = "abcd";

    int rc_1 = my_snprintf(buf_1, sizeof(buf_1), "%s", str);
    int rc_2 = snprintf(buf_2, sizeof(buf_2), "%s", str);
    
    ck_assert_int_eq(rc_1, rc_2);
    
	ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(test_one_with_text_s)
{
    char buf_1[100];
	buf_1[0] = '\0';
    char buf_2[100];
	buf_2[0] = '\0';
    char str[5] = "abcd";

    int rc_1 = my_snprintf(buf_1, sizeof(buf_1), "===%s___", str);
    int rc_2 = snprintf(buf_2, sizeof(buf_2), "===%s___", str);
    
    ck_assert_int_eq(rc_1, rc_2);
    
	ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(test_several_s)
{
    char buf_1[100];
	buf_1[0] = '\0';
    char buf_2[100];
	buf_2[0] = '\0';
    char str[5] = "abcd";

    int rc_1 = my_snprintf(buf_1, sizeof(buf_1), "%s%s%s", str, str, str);
    int rc_2 = snprintf(buf_2, sizeof(buf_2), "%s%s%s", str, str, str);
    
    ck_assert_int_eq(rc_1, rc_2);
    
	ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

START_TEST(test_several_with_text_s)
{
    char buf_1[100];
	buf_1[0] = '\0';
    char buf_2[100];
	buf_2[0] = '\0';
    char str[5] = "abcd";

    int rc_1 = my_snprintf(buf_1, sizeof(buf_1), "abc%sabc%ss%ss", str, str, str);
    int rc_2 = snprintf(buf_2, sizeof(buf_2), "abc%sabc%ss%ss", str, str, str);
       
    ck_assert_int_eq(rc_1, rc_2);
    
	ck_assert_str_eq(buf_1, buf_2);
}
END_TEST

Suite *s_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("s");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_one_s);
    tcase_add_test(tc_core, test_one_with_text_s);
    tcase_add_test(tc_core, test_several_s);
    tcase_add_test(tc_core, test_several_with_text_s);
    suite_add_tcase(s, tc_core);

    return s;
}

