#include <check.h>
#include "check_each.h"
#include "check_find.h"
#include "check_insert.h"
#include "check_max.h"
#include "check_min.h"
#include "check_remove.h"
#include "check_clear.h"
#include "check_create.h"
#include "check_destroy.h"

int main(void) 
{
    int no_failed = 0;                   
    Suite *s_each = each_suite();
    Suite *s_find = find_suite();
    Suite *s_insert = insert_suite();
    Suite *s_max = max_suite();
    Suite *s_min = min_suite();
    Suite *s_remove = remove_suite();
    Suite *s_clear = clear_suite();
    Suite *s_create = create_suite();
    Suite *s_destroy = destroy_suite();

    SRunner *runner;
    runner = srunner_create(s_create);
    srunner_add_suite(runner, s_clear);
    srunner_add_suite(runner, s_destroy);
    srunner_add_suite(runner, s_insert);
    srunner_add_suite(runner, s_remove);
    srunner_add_suite(runner, s_find);
    srunner_add_suite(runner, s_each);
    srunner_add_suite(runner, s_min);
    srunner_add_suite(runner, s_max);


    srunner_run_all(runner, CK_VERBOSE);  
    no_failed = srunner_ntests_failed(runner); 
    srunner_free(runner);
    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
