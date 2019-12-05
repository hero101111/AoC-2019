
#include "stdafx.h"
#include "SolutionDay.h"

#include "days/2/Day2.h"
#include "days/3/Day3.h"
#include "days/4/Day4.h"
#include "days/5/Day5.h"

using namespace std;

// ##############################

static int partControl = 1;

  // ##############################


int main(int argc, char** argv)
{
  map<int, unique_ptr<ISolutionDay>> solutions;
  solutions[2] = static_cast<unique_ptr<ISolutionDay>>(new Day2());
  solutions[3] = static_cast<unique_ptr<ISolutionDay>>(new Day3());
  solutions[4] = static_cast<unique_ptr<ISolutionDay>>(new Day4());
  solutions[5] = static_cast<unique_ptr<ISolutionDay>>(new Day5());
 
  int dayToRun = 5;

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
