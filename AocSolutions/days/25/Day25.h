#pragma once

#include "SolutionDay.h"

class Day25 : public ISolutionDay
{
private:

public:

  ~Day25() override { }

  string Part1() override
  {
    IntComputer cpu{ rff(KINPUT "25\\input.txt")[0] };

    cpu.mInputFunction = [&]() 
    {
      char c;
      cin >> noskipws >> c;
      return c;
    };

    cpu.mOutputCallback = [&](int output) 
    {
      cout << (char)output;
    };

    cpu.Execute();

    // after a lot of mazing around the ship
    // for this input you'll need :
    // MUG, HYPERCUBE, COIN, ASTROLABE
    
    // this unlocks the answer below
    return std::to_string(1077936448);
  }

  string Part2() override
  {
    return "50 STARS, HO HO HO. MERRY CHRISTMAS!";
  }
};
