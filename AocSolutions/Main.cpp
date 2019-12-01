
#include "stdafx.h"
#include "SolutionDay.h"

#include "Day2.h"

using namespace std;

int main(int argc, char** argv)
{
  map<int, unique_ptr<ISolutionDay>> solutions;
  solutions[2] = static_cast<unique_ptr<ISolutionDay>>(new Day2());
 
  int dayToRun = 2;

  bool runPartOne = true;

  auto & runner = solutions[dayToRun];
  string result;
  if (runPartOne)
  {
    cout << "Running Day " << dayToRun << " PART 1 " << endl;
    result = runner->Part1();
  }
  else
  {
    cout << "Running Day " << dayToRun << " PART 2 " << endl;
    result = runner->Part2();
  }
  pic(result);

  // ------------

  int t = 0;
  rff(KINPUT "1\\input.txt", [&t](string s) { int n = stoi(s); t += int(n / 3) - 2; });
  cout << endl;
  cout << t << endl;
 
  auto tokens = tok("first second 123");

  return 0;
}
