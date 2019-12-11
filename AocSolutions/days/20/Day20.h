#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/IntComputer.h"

class Day20 : public ISolutionDay
{
private:

  vector<string>  mdata;

public:

  Day20() { }

  ~Day20() override { }

  void ReadData()
  {
    mdata = rff(KINPUT "20\\input.txt");
  }

  string Part1() override
  {
    int ret = 201;
    return std::to_string(ret);
  }

  string Part2() override
  {
    int ret = 202;
    return std::to_string(ret);
  }
};
