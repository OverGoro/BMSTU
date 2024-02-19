#include <check.h>
#include "check_sort.h"
#include "check_key.h"
int main(void) {
    int no_failed = 0;                   
    Suite *s_sort, *s_key;                            
    SRunner *runner;                     

    s_sort = sort_suite();
    s_key = key_suite();
    runner = srunner_create(s_sort);
    srunner_add_suite(runner, s_key);

    srunner_run_all(runner, CK_VERBOSE);  
    no_failed = srunner_ntests_failed(runner); 
    srunner_free(runner);                      
    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
