#include "solution.h"

#include <functional>
#include <unordered_map>
#include <stack>
#include <locale>
using namespace sol1597;
using namespace std;

/* takeaways
   - you can think of operators as a series
     of commands that signal when an expression
     tree (a subtree) should be built
     - let say the expression is 1*2+3
       - when you see * you push it to the operator
         stack as its second operand 2 hasn't been
         scanned yet
       - when you see +, which has a lower priority
         than *, it will signals that * can build that
         expression tree 1*2 now
       - why? we need 1*2 to be closer to the bottom
         of the tree per the requirements so it need
         to build first
       - so who is going to tell + to build its expression?
         - there is no operator coming in any more
         - so we need a catch-all in the end to finish
           building the entire tree

    - parenthesis
      - when you see ')', it's a signal that you can build the
        expression tree between the closest ')' and this ')'
    - nodes stack
      - when it's time to build expression, nodes got pop out
        from the nodes stack to form a more complex expression.
      - The more complex expression (subtree) then got
        pushed back to the stack to serve as the foundation
        of building an even more complex expression next time
        around

*/
Node *Solution::build(string exp)
{
  stack<Node *> nodes;
  stack<char> ops;
  locale loc;

  function<void()> buildExpr = [&]()
  {
    /*
      - the right operand is on top of
        left operand in the stack
      - make sure you get the order
        right when building the
        expression tree
    */
    auto right = pop(nodes);
    auto left = pop(nodes);
    nodes.push(new Node(pop(ops), left, right));
  };

  for (const auto c : exp)
  {
    if (isdigit(c, loc))
      nodes.push(new Node(c));
    else if (c == '(')
      /*
        - this is just a marker and won't
          trigger any building of expression
          tree
      */
      ops.push(c);
    else if (c == ')')
    {
      /* ok we now can to build everything between (...) */
      while (ops.top() != '(')
        buildExpr();
      /* remove '(' */
      ops.pop();
    }
    else if (c == '+' || c == '-' || c == '*' || c == '/')
    {
      /*
        - you trigger building the expression tree
          only if the operator on top of the stack has a higher
          priority than the incoming operator
        - why? you want the expression tree with higher
          priority operator placed toward the bottom
          of the tree per the requirements
      */
      while (!ops.empty() && compare(ops.top(), c))
        buildExpr();
      ops.push(c);
    }
  }

  /* catch-all - make sure there is no leftover */
  while (!ops.empty())
    buildExpr();

  return nodes.top();
}

bool Solution::compare(char op1, char op2)
{
  /* parenthesis has lower priority */
  if (op1 == '(' || op1 == ')')
    return false;

  /* this also covers the case where
     op1 is + or - and op2 is * or /,
     which it will return false
  */
  return op1 == '*' || op1 == '/' ||
         op2 == '+' || op2 == '-';
}
char Solution::pop(stack<char> &ops)
{
  auto op = ops.top();
  ops.pop();
  return op;
}
Node *Solution::pop(stack<Node *> &nodes)
{
  auto node = nodes.top();
  nodes.pop();
  return node;
}
