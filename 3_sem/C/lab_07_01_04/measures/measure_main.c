#include "time_test.h"
#include "error.h"
#include <stddef.h>
#include <stdio.h>


int main(void)
{
    int rc = make_measure("measures/sorted_data_q.txt", "measures/sorted_data_m.txt", set_sorted_el);
    if (rc != ERR_OK)
        return rc;

    rc = make_measure("measures/reversed_data_q.txt", "measures/reversed_data_m.txt", set_reversed_el);
    if (rc != ERR_OK)
        return rc;

    rc = make_measure("measures/equal_data_q.txt", "measures/equal_data_m.txt", set_equal_el);
    if (rc != ERR_OK)
        return rc;

    rc = make_measure("measures/random_data_q.txt", "measures/random_data_m.txt", set_random_el);
    if (rc != ERR_OK)
        return rc;
}
