#include <gtest/gtest.h>

#include <memory>
#include "IntervalTree.h"

using namespace IntervalTree;

struct IntervalTreeTest : ::testing::Test {
       
    IntervalTree::Tree<std::string>* m_tree;

    virtual void SetUp() {
        m_tree = new IntervalTree::Tree<std::string>();
    }

    virtual void TearDown() {
        delete m_tree;
    }

    bool contain(const std::list<std::string>& results, const std::string& expected) {

        for (auto const& v : results) {
            if(expected == v){
                return true;
            }
        }
        return false;
    }

    bool contain(const std::list<std::string>& results, const std::list<std::string>& expecteds) {

        for (auto const& expected : expecteds) {
            if (!contain(results, expected)) {
                std::cout << "not found "  << expected << std::endl;
                return false;
            }
        }
        return true;
    }
};

TEST_F(IntervalTreeTest, SimpleTest)
{
    m_tree->insert(new IntervalTree::Interval(15,20), "v_1");
    m_tree->insert(new IntervalTree::Interval(10,30), "v_2");
    m_tree->insert(new IntervalTree::Interval(17,19), "v_3");
    m_tree->insert(new IntervalTree::Interval(5,20) , "v_4");
    m_tree->insert(new IntervalTree::Interval(12,15), "v_5");
    m_tree->insert(new IntervalTree::Interval(30,40), "v_6");

    m_tree->print();

    EXPECT_TRUE(contain(m_tree->get(31), std::list<std::string>({"v_6"})));
    EXPECT_TRUE(contain(m_tree->get(12), std::list<std::string>({"v_2", "v_4", "v_5"})));
    EXPECT_TRUE(contain(m_tree->get(15), std::list<std::string>({"v_1", "v_2", "v_4", "v_5"})));
    EXPECT_TRUE(contain(m_tree->get(30), std::list<std::string>({"v_2", "v_6"})));
    EXPECT_TRUE(contain(m_tree->get(40), std::list<std::string>({"v_6"})));
}


