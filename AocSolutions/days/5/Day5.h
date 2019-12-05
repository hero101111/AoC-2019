#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day5 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day5(){ }

  ~Day5() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(KINPUT "5\\input.txt");
  }

  int DoWork(int input)
  {
    vector<int> values(mData.size());
    for (size_t i = 0; i < mData.size(); ++i)
      values[i] = stoi(mData[i]);

    vector<int>& memory = values;

    int ret = 0;

    auto it = values.begin();
    while (it != values.end())
    {
      int instr = 0;
      int mode1 = 0;
      int mode2 = 0;
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
      }

      if (instr == 99)
        break;
      if (instr == 1)
      {
        int pos1 = *++it;
        int pos2 = *++it;
        int where = *++it;

        int v1 = mode1 == 0 ? memory[pos1] : pos1;
        int v2 = mode2 == 0 ? memory[pos2] : pos2;
        memory[where] = v1 + v2;
      }
      if (instr == 2)
      {
        int pos1 = *++it;
        int pos2 = *++it;
        int where = *++it;
        int v1 = mode1 == 0 ? memory[pos1] : pos1;
        int v2 = mode2 == 0 ? memory[pos2] : pos2;
        memory[where] = v1 * v2;
      }
      if (instr == 3)
      {
        int pos1 = *++it;
        memory[pos1] = input;
      }
      if (instr == 4)
      {
        int pos1 = *++it;
        int v = mode1 == 0 ? memory[pos1] : pos1;
        ret = v;
      }
      if (instr == 5)
      {
        int pos1 = *++it;
        int pos2 = *++it;
        int v1 = mode1 == 0 ? memory[pos1] : pos1;
        int v2 = mode2 == 0 ? memory[pos2] : pos2;
        if (v1 != 0)
        {
          it = values.begin() + v2;
          continue;
        }
      }
      if (instr == 6)
      {
        int pos1 = *++it;
        int pos2 = *++it;
        int v1 = mode1 == 0 ? memory[pos1] : pos1;
        int v2 = mode2 == 0 ? memory[pos2] : pos2;
        if (v1 == 0)
        {
          it = values.begin() + v2;
          continue;
        }
      }
      if (instr == 7)
      {
        int pos1 = *++it;
        int pos2 = *++it;
        int pos3 = *++it;
        int v1 = mode1 == 0 ? memory[pos1] : pos1;
        int v2 = mode2 == 0 ? memory[pos2] : pos2;
        
        memory[pos3] = (int)(v1 < v2);
        
      }
      if (instr == 8)
      {
        int pos1 = *++it;
        int pos2 = *++it;
        int pos3 = *++it;
        int v1 = mode1 == 0 ? memory[pos1] : pos1;
        int v2 = mode2 == 0 ? memory[pos2] : pos2;

        memory[pos3] = (int)(v1 == v2);
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
    return std::to_string(DoWork(1));
  }
  
  string Part2() override
  {
    ReadData();
    return std::to_string(DoWork(5));
  }
};
