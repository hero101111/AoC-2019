#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/IntComputer.h"

class Day12 : public ISolutionDay
{
private:

  vector<string>  mdata;

public:

  Day12() { }

  ~Day12() override { }

  void ReadData()
  {
    mdata = rff(KINPUT "12\\input.txt");
  }

  string Part1() override
  {
    int ret = 121;
    return std::to_string(ret);
  }

  string Part2() override
  {
    int ret = 122;
    return std::to_string(ret);
  }
};
