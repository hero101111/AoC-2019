#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day2 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day2(){ }

  ~Day2() override { }

  void DoWork()
  {
    mData = rff(KINPUT "2\\input.txt");
  }
  
  string Part1() override
  {
    int ret = 0;
    DoWork();

    return std::to_string(ret);
  }

  string Part2() override
  {
    int ret = 0;
    DoWork();

    return std::to_string(ret);
  }
};
