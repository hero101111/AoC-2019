#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day9 : public ISolutionDay
{
private:

  vector<string> mData;
  objmap<string> omap;

public:

  Day9() { }

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
      auto digits = GetDigits(*it);
      {
        instr = digits.back();
        digits.pop_back();
        if (!digits.empty())
        {
          instr = digits.back() * 10ll + instr;
          digits.pop_back();
        }
      }

      auto readMem = [&memory, &relBase, &it, &digits]()
      {
        int mode = digits.empty() ? 0 : digits.back();
        if (!digits.empty())
          digits.pop_back();

        long long pos = *++it;
        if (mode == 0)
        {
          return memory[pos];
        }
        else if (mode == 1)
        {
          return pos;
        }
        else if (mode == 2)
        {
          return memory[pos + relBase];
        }
        assert(!"Invalid path");
        return pos;
      };

      auto writeMem = [&memory, &relBase, &it, &digits](long long val)
      {
        long long where = *++it;
        int mode = digits.empty() ? 0 : digits.back();
        if (!digits.empty())
          digits.pop_back();

        where += mode == 2 ? relBase : 0;
        memory[where] = val;
      };

      if (instr == 99)
        break;
      else if (instr == 1)
      {
        vector<long long> params = { readMem(), readMem() };
        writeMem(params[0] + params[1]);
      }
      else if (instr == 2)
      {
        vector<long long> params = { readMem(), readMem() };
        writeMem(params[0] * params[1]);
      }
      else if (instr == 3)
      {
        writeMem(input);
      }
      else if (instr == 4)
      {
        ret = readMem();
      }
      else if (instr == 5)
      {
        vector<long long> params = { readMem(), readMem() };
        if (params[0] != 0)
        {
          it = values.begin() + params[1];
          continue;
        }
      }
      else if (instr == 6)
      {
        vector<long long> params = { readMem(), readMem() };
        if (params[0] == 0)
        {
          it = values.begin() + params[1];
          continue;
        }
      }
      else if (instr == 7)
      {
        vector<long long> params = { readMem(), readMem() };

        writeMem((long long)(params[0] < params[1]));
      }
      else if (instr == 8)
      {
        vector<long long> params = { readMem(), readMem() };

        writeMem((long long)(params[0] == params[1]));
      }
      else if (instr == 9)
      {
        relBase += readMem();
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
