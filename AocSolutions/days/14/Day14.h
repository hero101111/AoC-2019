#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/IntComputer.h"

class Day14 : public ISolutionDay
{
private:

  vector<string>  mdata;

public:

  Day14() { }

  ~Day14() override { }

  void ReadData()
  {
    mdata = rff(KINPUT "14\\input.txt");
  }

  string Part1() override
  {
    int ret = 141;
    return std::to_string(ret);
  }

  string Part2() override
  {
    int ret = 142;
    return std::to_string(ret);
  }
};
