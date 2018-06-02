// clang-format off
#include "rb_tree.hpp"

#define BOOST_TEST_MODULE rbt
#include <boost/test/included/unit_test.hpp>
// clang-format on

using namespace std;

BOOST_AUTO_TEST_CASE(test1) {
    RBTree<int> rbt;
    rbt.insert(1);
    rbt.insert(1);
    rbt.insert(1);
    rbt.insert(1);
    rbt.insert(2);
    BOOST_TEST(rbt.find(2) == 1);
}
