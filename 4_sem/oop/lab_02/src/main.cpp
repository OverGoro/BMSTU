#include "set.h"
#include <vector>
#include <gtest/gtest.h>
TEST(Constructors, empty)
{
    Set<double> set_1;
    ASSERT_EQ(set_1.size(), 0);
}
TEST(Constructors, array)
{
    double nums_d[] = {1.1, 1.1, 2.2, 3.3, 4.4, 5.5, 6.8, 6.8};
    int nums_i[] = {1, 2, 3, 4, 5, 6, 6, 6, 6};
    std::vector<int> ans = {1, 2, 3, 4, 5, 6};
    Set<int> set_2(sizeof(nums_d) / sizeof(nums_d[0]), nums_d);
    ASSERT_EQ(set_2, ans);
    Set<int> set_3(sizeof(nums_i) / sizeof(nums_i[0]), nums_i);
    ASSERT_EQ(set_3, ans);
}
TEST(Constructors, vector)
{
    std::vector<double> vec_d = {1.1, 2.2, 3.3, 4.4, 5.5, 6.8};
    std::vector<int> vec_i = {1, 2, 3, 4, 5, 6, 6, 6};
    std::vector<int> ans = {1, 2, 3, 4, 5, 6, 6, 6};
    Set<int> set_2(vec_i);
    ASSERT_EQ(set_2, ans);
    Set<int> set_3(vec_d);
    ASSERT_EQ(set_3, ans);
}

TEST(Constructors, set_copy)
{
    double nums[6] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.8};
    Set<double> set_1(6, nums);
    Set<double> set_2(set_1);
    ASSERT_EQ(set_1, set_2);
}
TEST(Constructors, set_move)
{
    double nums[6] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.8};
    Set<double> set_b;
    Set<double> set_1(6, nums);
    Set<double> set_2(std::move(set_1));
    Set<double> set_3;
    ASSERT_EQ(set_1, set_b);
    ASSERT_EQ(set_2, set_3);
}
TEST(Constructors, list)
{
    std::vector<int> vec = {1, 2, 3, 4, 5, 8};
    Set<int> set({1, 2, 3, 4, 5, 2, 3, 4, 2, 4, 5, 6, 8, 8});
    ASSERT_EQ(set, vec);
}

TEST(Operations, eq)
{
    Set<int> set_1({1, 2, 3, 4, 5, 2, 3, 4, 2, 4, 5, 6, 8, 8});
    Set<int> set_2({1, 2, 3, 4, 5, 2, 3, 4, 2, 4, 5, 6, 8, 8});
    Set<int> set_3({1, 12, 3, 4, 5, 2, 3, 4, 2, 4, 5, 6, 8, 8});
    ASSERT_TRUE(set_1 == set_2);
    ASSERT_FALSE(set_2 == set_3);
}

TEST(Operations, neq)
{
    Set<int> set_1({1, 2, 3, 4, 5, 2, 3, 4, 2, 4, 5, 6, 8, 8});
    Set<int> set_2({1, 2, 3, 4, 5, 2, 3, 4, 2, 4, 5, 6, 8, 8});
    Set<int> set_3({1, 12, 3, 4, 5, 2, 3, 4, 2, 4, 5, 6, 8, 8});
    ASSERT_FALSE(set_1 != set_2);
    ASSERT_TRUE(set_2 != set_3);
}

TEST(Operations, summ)
{
    Set<int> set_1({1, 2, 3, 4, 5, 2, 3, 4, 2, 4, 5, 6, 8, 8});
    set_1 += 1;
    std::vector<int> ans = {1, 2, 3, 4, 5, 6, 8};
    Set<int> set_2({1, 2, 3, 4, 5, 2, 3, 4, 2, 4, 5, 6, 8, 8});
    set_2 += 1.0;
    ASSERT_EQ(set_1, ans);
    ASSERT_EQ(set_2, ans);
}

TEST(Operations, minus)
{
    Set<int> set_1({1, 2, 3, 4, 5, 2, 3, 4, 2, 4, 5, 6, 8, 8});
    set_1 -= 1;
    std::vector<int> ans = {2, 3, 4, 5, 6, 8};
    Set<int> set_2({1, 2, 3, 4, 5, 2, 3, 4, 2, 4, 5, 6, 8, 8});
    set_2 -= 1.0;
    ASSERT_EQ(set_1, ans);
    ASSERT_EQ(set_2, ans);
}

TEST(Connections, unite)
{
    Set<int> set_1({1, 2, 3, 4});
    Set<int> set_2({2, 3, 4, 5});
    Set<double> set_3({2, 3, 4, 5});
    std::vector<int> ans = {1, 2, 3, 4, 5};
    ASSERT_EQ(set_1.unite(set_2), ans);
    ASSERT_EQ(set_1.unite(set_3), ans);
}
TEST(Connections, intersection)
{
    Set<int> set_1({1, 2, 3, 4});
    Set<int> set_2({2, 3, 4, 5});
    Set<double> set_3({2, 3, 4, 5});
    std::vector<int> ans = {2, 3, 4};
    set_1.intersect_update(set_2);
    ASSERT_EQ(set_1, ans);
}
TEST(Connections, difference)
{
    Set<int> set_1({1, 2, 3, 4});
    Set<int> set_2({2, 3, 4, 5});
    Set<double> set_3({2, 3, 4, 5});
    std::vector<int> ans = {1};
    ASSERT_EQ(set_1.difference(set_2), ans);
    ASSERT_EQ(set_1.difference(set_3), ans);
}
TEST(Connections, symmetric_difference)
{
    Set<int> set_1({1, 2, 3, 4});
    Set<int> set_2({2, 3, 4, 5});
    Set<double> set_3({2, 3, 4, 5});
    std::vector<int> ans = {1, 5};
    ASSERT_EQ(set_1.symmetric_difference(set_2), ans);
    ASSERT_EQ(set_1.symmetric_difference(set_3), ans);
}

TEST(Operators, union)
{
    Set<int> set_base({1, 2, 3, 4});

    int element_same_type = 5;
    Set<int> set_same_type({1, 2, 3, 4, 5, 6, 7});
    std::vector<int> vector_same_type({1, 2, 3, 4, 5, 6, 7});
    std::initializer_list<int> list_same_type = {1, 2, 3, 4, 5, 6, 7};

    double element_another_type = 5.1;
    Set<double> set_another_type({1, 2, 3, 4, 5, 6, 7.1});
    std::vector<double> vector_another_type({1, 2, 3, 4, 5, 6, 7.1});
    std::initializer_list<double> list_another_type = {1, 2, 3, 4, 5, 6, 7.1};

    Set<int> answer_container = {1, 2, 3, 4, 5, 6, 7};
    Set<int> answer_element = {1, 2, 3, 4, 5};

    Set<int> tmp_set(set_base);
    tmp_set += element_same_type;
    ASSERT_EQ(tmp_set, answer_element);

    tmp_set = set_base;
    tmp_set += set_same_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;
    tmp_set += vector_same_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;
    tmp_set += list_same_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;
    tmp_set += element_another_type;
    ASSERT_EQ(tmp_set, answer_element);

    tmp_set = set_base;
    tmp_set += set_another_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;
    tmp_set += vector_another_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;
    tmp_set += list_another_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;

    ASSERT_EQ(tmp_set + element_same_type, answer_element);

    tmp_set + set_same_type;
    ASSERT_EQ(tmp_set + set_same_type, answer_container);

    ASSERT_EQ(tmp_set + vector_same_type, answer_container);

    ASSERT_EQ(tmp_set + list_same_type, answer_container);

    ASSERT_EQ(tmp_set + element_another_type, answer_element);

    tmp_set + set_another_type;
    ASSERT_EQ(tmp_set + set_another_type, answer_container);

    ASSERT_EQ(tmp_set + vector_another_type, answer_container);

    ASSERT_EQ(tmp_set + list_another_type, answer_container);
}

TEST(Operators, difference)
{
    Set<int> set_base({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

    int element_same_type = 5;
    Set<int> set_same_type({1, 2, 3, 4, 5, 6, 7});
    std::vector<int> vector_same_type({1, 2, 3, 4, 5, 6, 7});
    std::initializer_list<int> list_same_type = {1, 2, 3, 4, 5, 6, 7};

    double element_another_type = 5.1;
    Set<double> set_another_type({1, 2, 3, 4, 5, 6, 7.1});
    std::vector<double> vector_another_type({1, 2, 3, 4, 5, 6, 7.1});
    std::initializer_list<double> list_another_type = {1, 2, 3, 4, 5, 6, 7.1};

    Set<int> answer_container = {8, 9, 10};
    Set<int> answer_element = {1, 2, 3, 4, 6, 7, 8, 9, 10};

    Set<int> tmp_set(set_base);
    tmp_set -= element_same_type;
    ASSERT_EQ(tmp_set, answer_element);

    tmp_set = set_base;
    tmp_set -= set_same_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;
    tmp_set -= vector_same_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;
    tmp_set -= list_same_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;
    tmp_set -= element_another_type;
    ASSERT_EQ(tmp_set, answer_element);

    tmp_set = set_base;
    tmp_set -= set_another_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;
    tmp_set -= vector_another_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;
    tmp_set -= list_another_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;

    ASSERT_EQ(tmp_set - element_same_type, answer_element);

    ASSERT_EQ(tmp_set - set_same_type, answer_container);

    ASSERT_EQ(tmp_set - vector_same_type, answer_container);

    ASSERT_EQ(tmp_set - list_same_type, answer_container);

    ASSERT_EQ(tmp_set - element_another_type, answer_element);

    ASSERT_EQ(tmp_set - set_another_type, answer_container);

    ASSERT_EQ(tmp_set - vector_another_type, answer_container);

    ASSERT_EQ(tmp_set - list_another_type, answer_container);
}

TEST(Operators, intersect)
{
    Set<int> set_base({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

    Set<int> set_same_type({1, 2, 3, 4, 5, 6, 7});
    std::vector<int> vector_same_type({1, 2, 3, 4, 5, 6, 7});
    std::initializer_list<int> list_same_type = {1, 2, 3, 4, 5, 6, 7};

    Set<double> set_another_type({1, 2, 3, 4, 5, 6, 7});
    std::vector<double> vector_another_type({1, 2, 3, 4, 5, 6, 7});
    std::initializer_list<double> list_another_type = {1, 2, 3, 4, 5, 6, 7};

    Set<int> answer_container = {1, 2, 3, 4, 5, 6, 7};

    Set<int> tmp_set(set_base);
    tmp_set &= vector_same_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;
    tmp_set &= list_same_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;
    tmp_set &= set_another_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;
    tmp_set &= vector_another_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;
    tmp_set &= list_another_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;

    ASSERT_EQ(tmp_set & set_same_type, answer_container);

    ASSERT_EQ(tmp_set & vector_same_type, answer_container);

    ASSERT_EQ(tmp_set & list_same_type, answer_container);

    ASSERT_EQ(tmp_set & set_another_type, answer_container);

    ASSERT_EQ(tmp_set & vector_another_type, answer_container);

    ASSERT_EQ(tmp_set & list_another_type, answer_container);
}

TEST(Operators, symmetric_difference)
{
    Set<int> set_base({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

    Set<int> set_same_type({1, 2, 3, 4, 5, 6, 7});
    std::vector<int> vector_same_type({1, 2, 3, 4, 5, 6, 7});
    std::initializer_list<int> list_same_type = {1, 2, 3, 4, 5, 6, 7};

    Set<double> set_another_type({1, 2, 3, 4, 5, 6, 7.1});
    std::vector<double> vector_another_type({1, 2, 3, 4, 5, 6, 7.1});
    std::initializer_list<double> list_another_type = {1, 2, 3, 4, 5, 6, 7.1};

    Set<int> answer_container = {0, 8, 9, 10};

    Set<int> tmp_set(set_base);
    tmp_set ^= vector_same_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;
    tmp_set ^= list_same_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;
    tmp_set ^= set_another_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;
    tmp_set ^= vector_another_type;
    ASSERT_EQ(tmp_set, answer_container);

    tmp_set = set_base;
    tmp_set ^= list_another_type;
    ASSERT_EQ(tmp_set, answer_container);
    tmp_set = set_base;

    ASSERT_EQ(tmp_set ^ set_same_type, answer_container);

    ASSERT_EQ(tmp_set ^ vector_same_type, answer_container);

    ASSERT_EQ(tmp_set ^ list_same_type, answer_container);

    ASSERT_EQ(tmp_set ^ set_another_type, answer_container);

    ASSERT_EQ(tmp_set ^ vector_another_type, answer_container);

    ASSERT_EQ(tmp_set ^ list_another_type, answer_container);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    return 0;
}
