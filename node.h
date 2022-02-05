#ifndef NODE_H
#define NODE_H

#include <vector>
#include <cinttypes>
using namespace std;

namespace sol1597
{
    struct Node
    {
        char val;
        Node *left;
        Node *right;
        Node(char val, Node *left, Node *right) : val(val), left(left), right(right) {}
        Node(char val) : val(val), left(nullptr), right(nullptr) {}
    };
}
#endif