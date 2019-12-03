
#include "stdafx.h"
#include "SolutionDay.h"

#include "days/2/Day2.h"
#include "days/3/Day3.h"

using namespace std;

// ##############################

static int partControl = 11;

  // ##############################


int main(int argc, char** argv)
{
  map<int, unique_ptr<ISolutionDay>> solutions;
  solutions[2] = static_cast<unique_ptr<ISolutionDay>>(new Day2());
  solutions[3] = static_cast<unique_ptr<ISolutionDay>>(new Day3());
 
  int dayToRun = 3;

  auto & runner = solutions[dayToRun];
  string result;

  bool runPartOne = partControl == 1;
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

  cout << endl << endl << result << endl << endl << "copied to clipboard" << endl;

  // store result in clipboard
  pic(result);

  return 0;
}
