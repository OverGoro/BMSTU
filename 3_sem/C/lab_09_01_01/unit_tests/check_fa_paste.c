#include "check_fa_paste.h"
#include "film_array.h"
#include "check_cmp.h"
#include <check.h>
// Вставка в начало
START_TEST(test_paste_begin)
{
    film_t film_array[5] = {
        {"Film 1", "Author1", 2000},
        {"Film 2", "Author1", 2005},
        {"Film 3", "Author3", 2010}
    };
    size_t n = 3;

    film_t film = {"Film x", "Authorx", 2010};

    film_t film_ans_array[5] = {
        {"Film x", "Authorx", 2010},
        {"Film 1", "Author1", 2000},
        {"Film 2", "Author1", 2005},
        {"Film 3", "Author3", 2010}
    };
    fa_paste(film_array, &n, &film, 0);
    int rc = cmp_film_t_arr(film_array, film_ans_array, n, 4);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_paste_middle)
{
    film_t film_array[5] = {
        {"Film 1", "Author1", 2000},
        {"Film 2", "Author1", 2005},
        {"Film 3", "Author3", 2010}
    };
    size_t n = 3;

    film_t film = {"Film x", "Authorx", 2010};

    film_t film_ans_array[5] = {
        {"Film 1", "Author1", 2000},
        {"Film x", "Authorx", 2010},
        {"Film 2", "Author1", 2005},
        {"Film 3", "Author3", 2010}
    };
    fa_paste(film_array, &n, &film, 1);
    int rc = cmp_film_t_arr(film_array, film_ans_array, n, 4);
    ck_assert_int_eq(rc, 0);
}
END_TEST


START_TEST(test_paste_end)
{
    film_t film_array[5] = {
        {"Film 1", "Author1", 2000},
        {"Film 2", "Author1", 2005},
        {"Film 3", "Author3", 2010}
    };
    size_t n = 3;

    film_t film = {"Film x", "Authorx", 2010};

    film_t film_ans_array[5] = {
        {"Film 1", "Author1", 2000},
        {"Film 2", "Author1", 2005},
        {"Film 3", "Author3", 2010},
        {"Film x", "Authorx", 2010}
    };
    fa_paste(film_array, &n, &film, 3);
    int rc = cmp_film_t_arr(film_array, film_ans_array, n, 4);
    ck_assert_int_eq(rc, 0);
}
END_TEST

Suite *fa_paste_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("paste");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_paste_begin);
    tcase_add_test(tc_core, test_paste_middle);
    tcase_add_test(tc_core, test_paste_end);
    suite_add_tcase(s, tc_core);

    return s;
}
