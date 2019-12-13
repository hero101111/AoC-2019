#pragma once

#include "util.h"

class IntComputer
{
public:
   
  bool          mSuspendOnOutput{ false };
  long long     mOutput         {   0   };
  long long     mInput          {   0   };

  function<long long(void)> mInputFunction{ nullptr };
  function<void(long long)> mOutputCallback{ nullptr };

private:
  typedef unordered_map<long long, long long> DT;

  DT            memory;
  long long     relBase         {   0    };
  bool          mHalted         {  false };

  long long     mIP             {   0    } ;

  vector<string> mInitialInstructions;

public:

  IntComputer(string instructions) 
  {
    SetInstructions(instructions);
  }

  ~IntComputer() { }

  void ResetMemory()
  {
    memory.clear();
    for (size_t i = 0; i < mInitialInstructions.size(); ++i)
      memory[i] = stoll(mInitialInstructions[i]);
    mIP = 0;
  }

  void SetInstructions(string instructions)
  {
    mInitialInstructions = tok(instructions, ',');
    ResetMemory();
  }

  long long Execute()
  {
    auto memAt = [this](long long it) {return memory[it]; };

    long long ret = 0;

    auto crtIp = mIP;

    while (true)
    {
      long long instr = 0;
      auto digits = GetDigits(memAt(crtIp));
      {
        instr = digits.back();
        digits.pop_back();
        if (!digits.empty())
        {
          instr = digits.back() * 10ll + instr;
          digits.pop_back();
        }
      }

      auto readMem = [this, &crtIp, &digits, memAt]()
      {
        int mode = digits.empty() ? 0 : digits.back();
        if (!digits.empty())
          digits.pop_back();

        long long pos = memAt(++crtIp);
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

      auto writeMem = [this, &crtIp, &digits, memAt](long long val)
      {
        long long where = memAt(++crtIp);
        int mode = digits.empty() ? 0 : digits.back();
        if (!digits.empty())
          digits.pop_back();

        where += mode == 2 ? relBase : 0;
        memory[where] = val;
      };

      if (instr == 1)
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
        auto inputToUse = mInput;
        if (mInputFunction != nullptr)
          inputToUse = mInputFunction();

        writeMem(inputToUse);
      }
      else if (instr == 4)
      {
        ret = readMem();
        mOutput = ret;

        if (mOutputCallback != nullptr)
          mOutputCallback(ret);

        if (mSuspendOnOutput)
        {
          mIP = ++crtIp;
          return ret;
        }
      }
      else if (instr == 5)
      {
        vector<long long> params = { readMem(), readMem() };
        if (params[0] != 0)
        {
          crtIp = params[1];
          continue;
        }
      }
      else if (instr == 6)
      {
        vector<long long> params = { readMem(), readMem() };
        if (params[0] == 0)
        {
          crtIp = params[1];
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
      else if (instr == 99)
      {
        mHalted = true;
        break;
      }

      ++crtIp;
    }

    return ret;
  }

  bool IsHalted() const
  {
    return mHalted;
  }

  void SetMemoryAt(long long index, long long val)
  {
    memory[index] = val;
  }

};
