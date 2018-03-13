#include <stdio.h>
#include <vector>
#include <list>
#include <algorithm>  
#include  <utility>

namespace IntervalTree {

struct Interval {
    int m_low;
    int m_high;
    Interval(int low, int high) {
        m_low = low;
        m_high = high;
    }
};

template <class T>
struct Node {
    const Interval *m_i;
    int m_max;
    Node *m_left;
    Node *m_right;
    int m_height;
    T m_value;

    Node(const Interval *i, const T value) {
        m_i = i;
        m_max = i->m_high;
        m_left = NULL;
        m_right = NULL;
        m_height = 1;
        m_value = value;
    }

private:
    void calHeight() {
        m_height = std::max(height(m_right), height(m_left)) + 1;
    }

    void balance() {
        int balance = height(m_left) - height(m_right);
        if (balance < -1) {
            rotateLeft();
        } else if (balance > 1) {
            rotateRight();
        } else {
            // balanced
        }
    }

    void addLeft(const Interval *i, const T value) {
        if (m_left == NULL) 
            m_left = new Node(i, value);
        else
            m_left->insert(i, value);
    }

    void addRight(const Interval *i, const T value) {
        if (m_right == NULL) 
            m_right = new Node(i, value);
        else
            m_right->insert(i, value);
    }

    void rotateRight() {
        Node<T> * temp = m_left->m_right;
        Node<T> * _left = m_left;

        Node<T> * copy = new Node<T>(*this);
        *this = std::move(*_left);
        delete _left;

        m_right = copy;
        m_right->m_left= temp;
        m_right->calHeight();
        calHeight();
    }

    void rotateLeft(){
        Node<T> * temp = m_right->m_left;
        Node<T> * _right = m_right;

        Node<T> * copy = new Node<T>(*this);
        *this = std::move(*_right);
        delete _right;

        m_left = copy;
        m_left->m_right = temp;
        m_left->calHeight();
        calHeight();
    }

public:
    void insert(const Interval *i, const T value) {
        if (i->m_low < m_i->m_low) {
            addLeft(i, value);
        } else {
            addRight(i, value);
        }

        if (m_max < i->m_high)
            m_max = i->m_high;

        calHeight();
        balance();
    }

    void print() const {

        printf("[%d,%d] max %d height %d\n", m_i->m_low, m_i->m_high, m_max, m_height);

        if (m_left != NULL) {
            printf("[%d,%d] left\n", m_i->m_low, m_i->m_high);
            m_left->print();
        }

        if (m_right != NULL) {
            printf("[%d,%d] right\n", m_i->m_low, m_i->m_high);
            m_right->print();
        }
    }

    std::list<T> lookup(int point) const {

        std::list<T> values;

        if (point >= m_i->m_low && point <= m_i->m_high) {
            values.push_back(m_value);
        }

        if (m_left != NULL && m_left->m_max >= point) {
            std::list<T> left = m_left->lookup(point);
            values.splice(values.end(), std::move(left));
        }

        if (m_right != NULL) {
            std::list<T> right = m_right->lookup(point);
            values.splice(values.end(), std::move(right));
        }

        // TODO return multiple
        return values;
    }
};

template <class T>
static int height(Node<T> *node) {
    if (node == NULL) 
        return 0;

    return node->m_height;
}

template <class T>
struct Tree {
    Node<T> * m_root;

    Tree() {
        m_root = NULL;
    }

    void insert(Interval * i, T value) {
        if (m_root == NULL) {
            m_root = new Node<T>(i, value);
            return ;
        }

        m_root->insert(i, value);
    }

    std::list<T> get(int point) const {
        if (m_root == NULL)
            throw std::runtime_error("empty tree");

        return m_root->lookup(point);
    }

    void print() {
        if (m_root == NULL)
            throw std::runtime_error("empty tree");

        m_root->print();
    }
};

}; // Namespace 
