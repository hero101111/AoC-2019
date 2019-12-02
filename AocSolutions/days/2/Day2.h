#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day2 : public ISolutionDay
{
private:

  vector<string> mData;

  int mValue{ 0 };

public:

  Day2(){ }

  ~Day2() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(KINPUT "2\\input.txt");
  }

  int DoWork(int a, int b)
  {
    vector<int> values(mData.size());
    for (int i = 0; i < mData.size(); ++i)
      values[i] = stoi(mData[i]);

    values[1] = a;
    values[2] = b;

    vector<int> mem = values;


    auto it = values.begin();
    while (it != values.end())
    {
      if (*it == 99)
        break;
      if (*it == 1)
      {
        int pos1 = *++it;
        int pos2 = *++it;
        int where = *++it;
        mem[where] = mem[pos1] + mem[pos2];
      }
      if (*it == 2)
      {
        int pos1 = *++it;
        int pos2 = *++it;
        int where = *++it;
        mem[where] = mem[pos1] * mem[pos2];
      }

      it++;
      if (it == values.end())
        break;
    }

    return mem[0];
  }

  
  string Part1() override
  {
    ReadData();

    return std::to_string(DoWork(12, 2));
  }

  string Part2() override
  {
    ReadData();

    int ret = 0;
    for (int i = 0; i <= 99; ++i)
      for (int j = 0; j <= 99; ++j)
      {
        int res = DoWork(i, j);
        if (res == 19690720)
          return to_string(i * 100 + j);
      }

    return "NAN";
  }
};
