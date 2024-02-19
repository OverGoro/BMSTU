#include <check.h>
#include "check_fa_find_place.h"
#include "check_fa_bin_search.h"
#include "check_fa_paste.h"
int main(void) 
{
    int no_failed = 0;                   
    Suite *s_fa_find_place;
    Suite *s_fa_bin_search;
    Suite *s_fa_paste;

    SRunner *runner;

    s_fa_find_place = fa_find_place_suite();
    s_fa_bin_search = fa_bin_search_suite();
    s_fa_paste = fa_paste_suite();


    runner = srunner_create(s_fa_find_place);
    srunner_add_suite(runner, s_fa_bin_search);
    srunner_add_suite(runner, s_fa_paste);

    srunner_run_all(runner, CK_VERBOSE);  
    no_failed = srunner_ntests_failed(runner); 
    srunner_free(runner);
    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
    return 0;
}
