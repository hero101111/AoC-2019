#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day7 : public ISolutionDay
{
private:

  vector<string> mdata;

public:

  Day7(){ }

  ~Day7() override { }

  int Compute(vector<int>& values, int phase, int input, int& output, bool & stopped, bool suspendAtOutput = false, int instrOffset = 0)
  {
    vector<int>& memory = values;

    int& ret = output;
    bool readPhase = instrOffset > 0 ? true: false;

    auto it = values.begin() + instrOffset;
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
      {
        stopped = true;
        break;
      }
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
        if (readPhase)
          memory[pos1] = input;
        else
        {
          memory[pos1] = phase;

          readPhase = true;
        }
      }
      if (instr == 4)
      {
        int pos1 = *++it;
        int v = mode1 == 0 ? memory[pos1] : pos1;
        ret = v;
        if (suspendAtOutput)
        {
          stopped = false;
          return it - begin(values);
        }
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

  void ReadData()
  {
    mdata.clear();
    vector<string> inp = rff(KINPUT "7\\input.txt");
    mdata = tok(inp[0], ',');
  }

  int SimulateAmplifier(int phase, int input)
  {

    vector<int> values(mdata.size());
    for (size_t i = 0; i < mdata.size(); ++i)
      values[i] = stoi(mdata[i]);
    
    int output = 0;
    bool stopped = false; // useful only for part 2
    return Compute(values, phase, input, output, stopped, false, 0);
  }

  int Simulate(int a, int b, int c, int d, int e)
  {  
    int outputA = SimulateAmplifier(a, 0);
    int outputB = SimulateAmplifier(b, outputA);
    int outputC = SimulateAmplifier(c, outputB);
    int outputD = SimulateAmplifier(d, outputC);
    int outputE = SimulateAmplifier(e, outputD);
    return outputE;
  }

  int Simulate2(int a, int b, int c, int d, int e)
  {
    vector<int> valuesA(mdata.size());
    for (size_t i = 0; i < mdata.size(); ++i)
      valuesA[i] = stoi(mdata[i]);
    vector<int> valuesB = valuesA;
    vector<int> valuesC = valuesA;
    vector<int> valuesD = valuesA;
    vector<int> valuesE = valuesA;

    int val = 0;

    int offsetA = 0, offsetB = 0, offsetC = 0, offsetD = 0, offsetE = 0;
    int outA = 0, outB = 0, outC = 0, outD = 0, outE = 0;
    bool stopA = false, stopB = false, stopC = false, stopD = false, stopE = false;
    while (true)
    {
      offsetA = Compute(valuesA, a, outE, outA, stopA, true, offsetA);
      offsetB = Compute(valuesB, b, outA, outB, stopB, true, offsetB);
      offsetC = Compute(valuesC, c, outB, outC, stopC, true, offsetC);
      offsetD = Compute(valuesD, d, outC, outD, stopD, true, offsetD);
      offsetE = Compute(valuesE, e, outD, outE, stopE, true, offsetE);
      
      if (stopA && stopB && stopC && stopD && stopE)
      {
        val = outE;
        break;
      }
    }
    
    return val;
  }

  int DoWorkPart1()
  {
    int maxval = numeric_limits<int>::min();

    vector<int> phases = { 0, 1, 2, 3, 4 };
    
    while (next_permutation(begin(phases), end(phases)))
    {
      int val = Simulate(phases[0], phases[1], phases[2], phases[3], phases[4]);
      if (val > maxval)
        maxval = val;
    }

    return maxval;
  }

  int DoWorkPart2()
  {
    int maxval = numeric_limits<int>::min();
    vector<int> phases = { 5, 6, 7, 8, 9 };

    while (next_permutation(begin(phases), end(phases)))
    {
      int val = Simulate2(phases[0], phases[1], phases[2], phases[3], phases[4]);
      if (val > maxval)
        maxval = val;
    }

    return maxval;
  }

  string Part1() override
  {
    ReadData();
    return std::to_string(DoWorkPart1());
  }
  
  string Part2() override
  {
    ReadData();
    return std::to_string(DoWorkPart2());
  }
};
