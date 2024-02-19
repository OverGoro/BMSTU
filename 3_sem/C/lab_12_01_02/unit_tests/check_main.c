#include <check.h>
#include "check_form.h"
#include "check_shift.h"

int main(void) {
    int no_failed = 0;                   
    Suite *s_form, *s_shift;
    SRunner *runner;

    s_form = form_suite();
    s_shift = shift_suite();
    runner = srunner_create(s_shift);
    srunner_add_suite(runner, s_form);

    srunner_run_all(runner, CK_VERBOSE);  
    no_failed = srunner_ntests_failed(runner); 
    srunner_free(runner);                      
    return (no_failed == 0) ? 0 : 1;
}
