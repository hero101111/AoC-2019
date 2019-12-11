#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/IntComputer.h"

class Day24 : public ISolutionDay
{
private:

  vector<string>  mdata;

public:

  Day24() { }

  ~Day24() override { }

  void ReadData()
  {
    mdata = rff(KINPUT "24\\input.txt");
  }

  string Part1() override
  {
    int ret = 241;
    return std::to_string(ret);
  }

  string Part2() override
  {
    int ret = 242;
    return std::to_string(ret);
  }
};
