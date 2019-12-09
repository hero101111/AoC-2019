#pragma once

#include "util/util.h"

class ISolutionDay
{
protected:
  ofstream verbose;
public:

  ISolutionDay()
  {
    verbose.open(KVERBOSE, ios_base::out);
  }

  virtual string Part1() = 0;
  virtual string Part2() = 0;

  virtual ~ISolutionDay() { verbose.close(); };
};