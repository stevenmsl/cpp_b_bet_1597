#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include "solution.h"
#include "util.h"

using namespace std;
using namespace sol1597;

tuple<string, string, string> testFixture1()
{
  return make_tuple("2-3/(5*2)+1", "3*4-2*5", "1+2+3+4+5");
}

void test1()
{
  auto fixture = testFixture1();
  Solution sol;
  cout << "Test 1 - 2-3/(5*2)+1 " << endl;
  auto tree = sol.build(get<0>(fixture));
  cout << "result - use debugger to verify the result";
}

main()
{
  test1();

  return 0;
}