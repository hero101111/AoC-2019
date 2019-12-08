#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day9 : public ISolutionDay
{
private:

  vector<string> mData;
  objmap<string> omap;

public:

  Day9(){ }

  ~Day9() override { }

  void ReadData()
  {
    auto data = rff(KINPUT "9\\input.txt");
    mData = tok(data[0], ',');
  }
  long long DoWork(int input)
  {
    long long relBase = 0;

    vector<long long> values(mData.size() * 100, 0);
    for (size_t i = 0; i < mData.size(); ++i)
      values[i] = stoll(mData[i]);

    vector<long long>& memory = values;

    long long ret = 0;

    auto it = values.begin();
    while (it != values.end())
    {
      long long instr = 0;
      long long mode1 = 0;
      long long mode2 = 0;
      long long mode3 = 0;
      {
        auto digits = GetDigits(*it);
        instr = digits.back();
        digits.pop_back();
        if (!digits.empty())
        {
          instr = digits.back() * 10 + instr;
          digits.pop_back();
        }
        if (!digits.empty())
        {
          mode1 = digits.back();
          digits.pop_back();
        }
        if (!digits.empty())
        {
          mode2 = digits.back();
          digits.pop_back();
        }
        if (!digits.empty())
        {
          mode3 = digits.back();
          digits.pop_back();
        }
      }

      if (instr == 99)
        break;
      else if (instr == 1)
      {
        long long pos1 = *++it;
        long long pos2 = *++it;
        long long where = *++it;

        long long v1 = mode1 == 0 ? memory[pos1] : (mode1 == 2 ? memory[pos1 + relBase] : pos1);
        long long v2 = mode2 == 0 ? memory[pos2] : (mode2 == 2 ? memory[pos2 + relBase] : pos2);

        where += mode3 == 2 ? relBase : 0;
        memory[where] = v1 + v2;
      }
      else if (instr == 2)
      {
        long long pos1 = *++it;
        long long pos2 = *++it;
        long long where = *++it;
        long long v1 = mode1 == 0 ? memory[pos1] : (mode1 == 2 ? memory[pos1 + relBase] : pos1);
        long long v2 = mode2 == 0 ? memory[pos2] : (mode2 == 2 ? memory[pos2 + relBase] : pos2);

        where += mode3 == 2 ? relBase : 0;
        memory[where] = v1 * v2;
      }
      else if (instr == 3)
      {
        long long where = *++it;
        where += mode1 == 2 ? relBase : 0;
        memory[where] = input;
      }
      else if (instr == 4)
      {
        long long pos1 = *++it;
        long long v = mode1 == 0 ? memory[pos1] : (mode1 == 2 ? memory[pos1 + relBase] : pos1);
        ret = v;
      }
      else if (instr == 5)
      {
        long long pos1 = *++it;
        long long pos2 = *++it;
        long long v1 = mode1 == 0 ? memory[pos1] : (mode1 == 2 ? memory[pos1 + relBase] : pos1);
        long long v2 = mode2 == 0 ? memory[pos2] : (mode2 == 2 ? memory[pos2 + relBase] : pos2);
        if (v1 != 0)
        {
          it = values.begin() + v2;
          continue;
        }
      }
      else if (instr == 6)
      {
        long long pos1 = *++it;
        long long pos2 = *++it;
        long long v1 = mode1 == 0 ? memory[pos1] : (mode1 == 2 ? memory[pos1 + relBase] : pos1);
        long long v2 = mode2 == 0 ? memory[pos2] : (mode2 == 2 ? memory[pos2 + relBase] : pos2);
        if (v1 == 0)
        {
          it = values.begin() + v2;
          continue;
        }
      }
      else if (instr == 7)
      {
        long long pos1 = *++it;
        long long pos2 = *++it;
        long long where = *++it;
        long long v1 = mode1 == 0 ? memory[pos1] : (mode1 == 2 ? memory[pos1 + relBase] : pos1);
        long long v2 = mode2 == 0 ? memory[pos2] : (mode2 == 2 ? memory[pos2 + relBase] : pos2);

        where += mode3 == 2 ? relBase : 0;
        memory[where] = (long long)(v1 < v2);

      }
      else if (instr == 8)
      {
        long long pos1 = *++it;
        long long pos2 = *++it;
        long long where = *++it;
        long long v1 = mode1 == 0 ? memory[pos1] : (mode1 == 2 ? memory[pos1 + relBase] : pos1);
        long long v2 = mode2 == 0 ? memory[pos2] : (mode2 == 2 ? memory[pos2 + relBase] : pos2);

        where += mode3 == 2 ? relBase : 0;
        memory[where] = (long long)(v1 == v2);
      }
      else if (instr == 9)
      {
        long long pos1 = *++it;
        long long v1 = mode1 == 0 ? memory[pos1] : (mode1 == 2 ? memory[pos1 + relBase] : pos1);
        relBase += v1;
      }

      it++;
      if (it == values.end())
        break;
    }

    return ret;
  }

  string Part1() override
  {
    ReadData();

    long long t = DoWork(1);
    return std::to_string(t);
  }
  
  string Part2() override
  {
    ReadData();

    long long t = DoWork(2);
    return std::to_string(t);
  }
};
