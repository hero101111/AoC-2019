#pragma once

#include "util.h"

class IntComputer
{
public:
   
  bool                        mSuspendOnOutput{ false };
  long long                   mOutput         {   0   };
  long long                   mInput          {   0   };

private:

  vector<long long>           values;
  long long                   relBase         {   0    };
  bool                        mHalted         {  false };

  vector<long long>::iterator mIP;


public:

  IntComputer(string instructions) 
  {
    SetInstructions(instructions);
  }

  ~IntComputer() { }

  void SetInstructions(string instructions)
  {
    vector<string> data = tok(instructions, ',');

    values.resize(data.size() * 100, 0);
    for (size_t i = 0; i < data.size(); ++i)
      values[i] = stoll(data[i]);

    mIP = values.begin();
  }

  long long Execute()
  {
    vector<long long>& memory = values;

    long long ret = 0;

    auto it = mIP;
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

      auto readMem = [&memory, this, &it, &digits]()
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

      auto writeMem = [&memory, this, &it, &digits](long long val)
      {
        long long where = *++it;
        int mode = digits.empty() ? 0 : digits.back();
        if (!digits.empty())
          digits.pop_back();

        where += mode == 2 ? relBase : 0;
        memory[where] = val;
      };

      if (instr == 99)
      {
        mHalted = true;
        break;        
      }
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
        writeMem(mInput);
      }
      else if (instr == 4)
      {
        ret = readMem();
        mOutput = ret;

        if (mSuspendOnOutput)
        {
          mIP = ++it;
          return ret;
        }
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

  bool IsHalted() const
  {
    return mHalted;
  }

};
