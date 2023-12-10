#include <check.h>
#include "check_matrix_summ.h"
#include "check_matrix_multiply.h"
#include "check_slae.h"
int main(void) 
{
    int no_failed = 0;                   
    Suite *s_summ;
    Suite *s_multiply;
    Suite *s_slae;
    SRunner *runner;

    s_summ = summ_suite();
    s_multiply = multiply_suite();
    s_slae = slae_suite();

    runner = srunner_create(s_multiply);
    srunner_add_suite(runner, s_summ);
    srunner_add_suite(runner, s_slae);

    srunner_run_all(runner, CK_VERBOSE);  
    no_failed = srunner_ntests_failed(runner); 
    srunner_free(runner);
    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
