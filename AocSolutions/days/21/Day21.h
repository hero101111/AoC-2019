#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/IntComputer.h"

class Day21 : public ISolutionDay
{
private:

  vector<string>  mdata;

public:

  Day21() { }

  ~Day21() override { }

  void ReadData()
  {
    mdata = rff(KINPUT "21\\input.txt");
  }

  string Part1() override
  {
    int ret = 211;
    return std::to_string(ret);
  }

  string Part2() override
  {
    int ret = 212;
    return std::to_string(ret);
  }
};
