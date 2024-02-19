#include <check.h>
#include "check_ho.h"
#include "check_s.h"
#include "check_all.h"

int main(void) 
{
    int no_failed = 0;                   
    Suite *s_ho;
    Suite *s_s;
    Suite *s_all;
    SRunner *runner;

    s_ho = ho_suite();
    s_s = s_suite();
    s_all = all_suite();


    runner = srunner_create(s_ho);
    srunner_add_suite(runner, s_s);
    srunner_add_suite(runner, s_all);

    srunner_run_all(runner, CK_VERBOSE);  
    no_failed = srunner_ntests_failed(runner); 
    srunner_free(runner);
    return (no_failed == 0) ? 0 : 1;
    return 0;
}
