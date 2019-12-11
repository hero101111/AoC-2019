#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/IntComputer.h"

class Day16 : public ISolutionDay
{
private:

  vector<string>  mdata;

public:

  Day16() { }

  ~Day16() override { }

  void ReadData()
  {
    mdata = rff(KINPUT "16\\input.txt");
  }

  string Part1() override
  {
    int ret = 161;
    return std::to_string(ret);
  }

  string Part2() override
  {
    int ret = 162;
    return std::to_string(ret);
  }
};
