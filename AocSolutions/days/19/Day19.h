#pragma once

#include "SolutionDay.h"

class Day19 : public ISolutionDay
{
public:

  ~Day19() override { }

  string Part1() override
  {
    int x = 0, y = 0, total = 0;
    bool fedX = false;

    int targetDimension = 50;

    while (x < targetDimension && y < targetDimension)
    {
      IntComputer cpu = IntComputer{ rff(KINPUT "19\\input.txt")[0] };
      cpu.mInputFunction = [&]()
      {
        if (!fedX)
        {
          fedX = true;
          return x;
        }
        else
        {
          fedX = false;
          return y;
        }
      };

      cpu.mOutputCallback = [&](int output)
      {
        total += output;
        ++x;
        if (x >= targetDimension)
        {
          ++y;
          x = 0;
        }
      };

      cpu.Execute();
    }

    return to_string(total);
  }

  string Part2() override
  {
    DynamicMap<char> m;
    int x = 0;
    int y = 0;

    bool fedX = false;

    Point crtPoint;

    auto haveSquare = [&](int line, int squareN) 
    {
      m.printf(KVERBOSE, '.');

      int startx = 0;
      for (int x : m.range_x())
      {
        if (m.hasAt({ x, line }, '#'))
        {
          startx = x;
          break;
        }
      }

      int crtx = startx;

      while (true)
      {
        bool isDud = false;
        for (int downy : rangeint(line + 1, line + squareN - 1))
        {
          if (!m.hasAt({ crtx, downy }, '#'))
          {
            isDud = true;
            break;
          }
        }

        if (!isDud)
        {
          for (int rightx : rangeint(crtx, crtx + squareN - 1))
          {
            if (!m.hasAt({ rightx, line }, '#'))
            {
              isDud = true;
              break;
            }
          }
        }
        
        if (!isDud)
          return crtx;

        crtx++;
        if (!m.hasAt({ crtx, line }, '#'))
          break;
      }

      return 0;
    };

    bool haveBeamOnLine = false;
    bool nextLine = false;
    int startx = 0;
    int endx = 0;

    while (true)
    {
      IntComputer cpu = IntComputer{ rff(KINPUT "19\\input.txt")[0] };
      cpu.mInputFunction = [&]()
      {
        if (!fedX)
        {
          fedX = true;
          return x;
        }
        else
        {
          fedX = false;
          return y;
        }
      };

      cpu.mOutputCallback = [&](int output)
      {
        crtPoint = { x, y };
        m[crtPoint] = output == 1 ? '#' : '.';

        int tractorWidth = endx - startx;


        x++;

        if (output == 1 && !haveBeamOnLine)
        {
          haveBeamOnLine = true;
          startx = crtPoint.x;
        }

        if (output == 0 && haveBeamOnLine)
        {
          haveBeamOnLine = false;
          nextLine = true;
          x = startx;
          endx = crtPoint.x;
          y++;
        }

        if (output == 0 && !haveBeamOnLine && crtPoint.x > endx + 10)
        {
          nextLine = true;
          haveBeamOnLine = false;
          x = startx;
          y++;
        }
      };

      if (nextLine)
      {
        int n = 100;
        int checkLine = y - n;

        if (checkLine >= 0)
        {
          int hS = haveSquare(checkLine, n);
          if (hS > 0)
          {
            return to_string(checkLine + hS * 10000);
          }
        }
        nextLine = false;
        cout << endx - startx << " ";
      }

      cpu.Execute();
    }

    return std::to_string(0);
  }
};
