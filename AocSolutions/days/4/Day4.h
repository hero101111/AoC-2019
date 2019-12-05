#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day4 : public ISolutionDay
{
private:

  vector<string> mData;

  int start = 240298;
  int end = 784956;

public:

  Day4(){ }

  ~Day4() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(KINPUT "4\\input.txt");
  }

  string Part1() override
  {
    ReadData();

    auto isMatch = [&](int n)
    {
      auto digits = GetDigits(n);
      bool hasAdjacent = false;

      for (size_t i = 0; i < digits.size() - 1; ++i)
      {
        int crtDigit = digits[i];
        if (crtDigit > digits[i + 1])
          return false;

        if (crtDigit == digits[i + 1])
        {
          hasAdjacent = true;
        }
      }
      if (!hasAdjacent)
        return false;

      return true;
    };

    int count = 0;
    for (int i = start; i <= end; ++i)
    {
      if (isMatch(i))
        count++;
    }

    return std::to_string(count);
  }
  
  string Part2() override
  {
    ReadData();

    auto isMatch = [&](int n)
    {
      auto digits = GetDigits(n);
      bool hasAdjacent = false;

      for (size_t i = 0; i < digits.size() - 1;++i)
      {
        if (digits[i] > digits[i + 1])
          return false;
      }
      for (size_t i = 0; i < digits.size() - 1;)
      {
        int crtDigit = digits[i];
        if (i > 0 && crtDigit != digits[i - 1] && hasAdjacent)
          return true;

        bool hasAdvanced = false;
        if (crtDigit == digits[i + 1])
        {
          hasAdjacent = true;

          if (i < digits.size() - 2)
          {
            if (crtDigit == digits[i + 2])
            {
              hasAdjacent = false;

              while (i < digits.size() && digits[i] == crtDigit)
              {
                ++i;
                hasAdvanced = true;
              }
              
              if (i >= digits.size())
                break;
            }
          }
        }
        if (!hasAdvanced)
          ++i;
      }
      if (!hasAdjacent)
        return false;
      

      return true;
    };

    int count = 0;
    for (int i = start; i <= end; ++i)
    { 
      if (isMatch(i))
        count++;      
    }

    return std::to_string(count);
  }
};

