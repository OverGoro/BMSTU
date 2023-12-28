#include "check_fa_find_place.h"
// Вставка в начало
START_TEST(test_begin)
{
    film_t film_array[5] = {
        {"Film 1", "Author1", 2000},
        {"Film 2", "Author1", 2005},
        {"Film 3", "Author1", 2010},
        {"Film 4", "Author1", 2015},
        {"Film 5", "Author1", 2020}
    };

    film_t film = {"Film X", "AuthorX", 1};

    size_t pos = fa_find_place(film_array, 5, &film, film_cmp_by_year);

    ck_assert_uint_eq(pos, 0);
}
END_TEST

// Вставка в середину
START_TEST(test_middle)
{
    film_t film_array[5] = {
        {"Film 1", "Author1", 2000},
        {"Film 2", "Author1", 2005},
        {"Film 3", "Author1", 2010},
        {"Film 4", "Author1", 2015},
        {"Film 5", "Author1", 2020}
    };

    film_t film = {"Film X", "AuthorX", 2011};

    size_t pos = fa_find_place(film_array, 5, &film, film_cmp_by_year);

    ck_assert_uint_eq(pos, 3);
}
END_TEST
// Вставка в конец
START_TEST(test_end)
{
    film_t film_array[5] = {
        {"Film 1", "Author1", 2000},
        {"Film 2", "Author1", 2005},
        {"Film 3", "Author1", 2010},
        {"Film 4", "Author1", 2015},
        {"Film 5", "Author1", 2020}
    };

    film_t film = {"Film X", "AuthorX", 9999};

    size_t pos = fa_find_place(film_array, 5, &film, film_cmp_by_year);

    ck_assert_uint_eq(pos, 5);
}
END_TEST


Suite *fa_find_place_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("summ");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_begin);
    tcase_add_test(tc_core, test_middle);
    tcase_add_test(tc_core, test_end);
    suite_add_tcase(s, tc_core);

    return s;
}

