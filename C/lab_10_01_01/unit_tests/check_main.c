#include <check.h>
#include "check_node_remove.h"
#include "check_remove_duplicates.h"
#include "check_split.h"
#include "check_sort.h"
#include "check_pop_front.h"
#include "check_pop_back.h"
#include "check_merge.h"
int main(void) 
{
    int no_failed = 0;                   
    Suite *s_node_remove = node_remove_suite();
    Suite *s_remove_duplicates = remove_duplicates_suite();
    Suite *s_split = split_suite();
    Suite *s_sort = sort_suite();
    Suite *s_pop_front = pop_front_suite();
    Suite *s_pop_back = pop_back_suite();
    Suite *s_merge = merge_suite();
    SRunner *runner;

    runner = srunner_create(s_node_remove);
    srunner_add_suite(runner, s_remove_duplicates);
    srunner_add_suite(runner, s_split);
    srunner_add_suite(runner, s_sort);
    srunner_add_suite(runner, s_pop_front);
    srunner_add_suite(runner, s_pop_back);
    srunner_add_suite(runner, s_merge);

    srunner_run_all(runner, CK_VERBOSE);  
    no_failed = srunner_ntests_failed(runner); 
    srunner_free(runner);
    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
