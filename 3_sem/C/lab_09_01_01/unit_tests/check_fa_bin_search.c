#include "check_fa_bin_search.h"

// Поиск по названию
START_TEST(test_bin_search_title)
{
    film_t film_array[5] = {
        {"Film 1", "Author1", 2000},
        {"Film 2", "Author1", 2005},
        {"Film 3", "Author3", 2010},
        {"Film 4", "Author1", 2015},
        {"Film 5", "Author1", 2020}
    };

    film_t film = {"Film 3", "Author3", 2010};

    film_t *found = fa_bin_search(film_array, 5, &film, film_cmp_by_title);

    ck_assert_ptr_eq(found, &film_array[2]);
}
END_TEST

// Поиск по автору
START_TEST(test_bin_search_name)
{
    film_t film_array[5] = {
        {"Film 1", "Author1", 2000},
        {"Film 2", "Author1", 2005},
        {"Film 3", "Author3", 2010},
        {"Film 4", "Author1", 2015},
        {"Film 5", "Author1", 2020}
    };

    film_t film = {"Film 3", "Author3", 2010};

    film_t *found = fa_bin_search(film_array, 5, &film, film_cmp_by_name);

    ck_assert_ptr_eq(found, &film_array[2]);
}
END_TEST

// Поиск по названию
START_TEST(test_bin_search_year)
{
    film_t film_array[5] = {
        {"Film 1", "Author1", 2000},
        {"Film 2", "Author1", 2005},
        {"Film 3", "Author3", 2010},
        {"Film 4", "Author1", 2015},
        {"Film 5", "Author1", 2020}
    };

    film_t film = {"Film 3", "Author3", 2010};

    film_t *found = fa_bin_search(film_array, 5, &film, film_cmp_by_year);

    ck_assert_ptr_eq(found, &film_array[2]);
}
END_TEST

// Поиск по названию, не найден
START_TEST(test_bin_search_title_not)
{
    film_t film_array[5] = {
        {"Film 1", "Author1", 2000},
        {"Film 2", "Author1", 2005},
        {"Film 3", "Author3", 2010},
        {"Film 4", "Author1", 2015},
        {"Film 5", "Author1", 2020}
    };

    film_t film = {"Film X", "AuthorX", 2};

    film_t *found = fa_bin_search(film_array, 5, &film, film_cmp_by_title);

    ck_assert_ptr_null(found);
}
END_TEST

// Поиск по автору, не найден
START_TEST(test_bin_search_name_not)
{
    film_t film_array[5] = {
        {"Film 1", "Author1", 2000},
        {"Film 2", "Author1", 2005},
        {"Film 3", "Author3", 2010},
        {"Film 4", "Author1", 2015},
        {"Film 5", "Author1", 2020}
    };

    film_t film = {"Film X", "AuthorX", 2};

    film_t *found = fa_bin_search(film_array, 5, &film, film_cmp_by_name);

    ck_assert_ptr_null(found);
}
END_TEST

// Поиск по названию, не найден
START_TEST(test_bin_search_year_not)
{
    film_t film_array[5] = {
        {"Film 1", "Author1", 2000},
        {"Film 2", "Author1", 2005},
        {"Film 3", "Author3", 2010},
        {"Film 4", "Author1", 2015},
        {"Film 5", "Author1", 2020}
    };

    film_t film = {"Film X", "AuthorX", 2};

    film_t *found = fa_bin_search(film_array, 5, &film, film_cmp_by_year);

    ck_assert_ptr_null(found);
}
END_TEST

Suite *fa_bin_search_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("summ");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_bin_search_title);
    tcase_add_test(tc_core, test_bin_search_name);
    tcase_add_test(tc_core, test_bin_search_year);
    tcase_add_test(tc_core, test_bin_search_title_not);
    tcase_add_test(tc_core, test_bin_search_name_not);
    tcase_add_test(tc_core, test_bin_search_year_not);
    suite_add_tcase(s, tc_core);

    return s;
}

