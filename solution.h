
#ifndef SOLUTION_H
#define SOLUTION_H

#include "node.h"
#include <vector>
#include <stack>
#include <string>
using namespace std;
namespace sol1597
{
    class Solution
    {
    private:
        bool compare(char op1, char op2);
        char pop(stack<char> &ops);
        Node *pop(stack<Node *> &nodes);

    public:
        Node *build(string exp);
    };
}
#endif