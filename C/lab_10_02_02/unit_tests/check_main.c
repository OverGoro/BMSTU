#include <check.h>
#include "check_pop_front.h"
#include "check_pop_back.h"
#include "check_polynome_count.h"
int main(void) 
{
    int no_failed = 0;                   
    Suite *s_pop_front = pop_front_suite();
    Suite *s_pop_back = pop_back_suite();
    Suite *s_polynome_count = polynome_count_suite();
    SRunner *runner;

    runner = srunner_create(s_pop_back);
    srunner_add_suite(runner, s_pop_front);
    srunner_add_suite(runner, s_polynome_count);

    srunner_run_all(runner, CK_VERBOSE);  
    no_failed = srunner_ntests_failed(runner); 
    srunner_free(runner);
    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
