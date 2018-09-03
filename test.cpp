// clang-format off
#include "rb_tree.hpp"

#define BOOST_TEST_MODULE rbt
#include <boost/test/included/unit_test.hpp>
// clang-format on

using namespace std;

BOOST_AUTO_TEST_CASE(test1) {
    RBTree<int> rbt;
    rbt.insert(1);
    rbt.insert(2);
    rbt.insert(3);
    rbt.insert(4);
    rbt.insert(5);
    rbt.insert(6);
    rbt.insert(7);
    rbt.insert(8);
    rbt.insert(9);
    rbt.insert(10);
    BOOST_TEST(rbt.find(0) == false);
    BOOST_TEST(rbt.find(10) == true);
}

/* BOOST_AUTO_TEST_CASE(test1) {

    RBTree<int> rbt;
    rbt.insert(1);
    rbt.insert(1);
    rbt.insert(1);
    rbt.insert(1);
    rbt.insert(1);
    rbt.insert(1);
    rbt.insert(1);
    rbt.insert(1);
    rbt.insert(2);
    BOOST_TEST(rbt.find(6) == false);
} */
