#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/IntComputer.h"

class Day16 : public ISolutionDay
{
private:

  vector<int>  mdata;

  unordered_map<int, vector<int>> patterns;

  vector<int> phaseVector;

  vector<int> basePattern = { 0, 1, 0, -1 };

public:

  Day16() { }

  ~Day16() override { }

  void ReadData()
  {
    string data = rff(KINPUT "16\\input2.txt")[0];
    for (auto c : data)
      mdata.push_back(stoi(string() + c));
  }

  void advancePatternIt(int & repeat, int & outputPos, vector<int>::iterator & patternIt)
  {
    if (repeat >= outputPos)
    {
      patternIt++;
      repeat = 1;
    }
    else
      ++repeat;

    if (patternIt == end(basePattern))
      patternIt = begin(basePattern);
  };

  void Phase(vector<int> * input, vector<int> * outCache)
  {
    vector<int> sums(input->size());
    sums[0] = (*input)[0];
    for (int i = 1; i < sums.size(); ++i)
      sums[i] = sums[i - 1] + (*input)[i];

    for (int i = 0; i < input->size(); ++i)
    {
      int outputPos = i + 1;

      int retV = 0;

      int repeat = outputPos;
      auto patternIt = basePattern.begin();

      auto offset = i;
      for (; offset < input->size();)
      {
        advancePatternIt(repeat, outputPos, patternIt);

        int sum = (*input)[offset];
        if (outputPos != 1)
        {
          int right = offset + outputPos - 1;
          if (right > input->size() - 1)
            right = input->size() - 1;
          if (*patternIt != 0)
            sum = sums[right] - sums[offset - 1];
        }

        offset += outputPos;
        switch (*patternIt)
        {
        case 1:
          retV += sum;
          break;
        case -1:
          retV -= sum;
          break;
        }

        if (offset > input->size() - 1)
          break;

        patternIt++;
        repeat = 0;
      }

      (*outCache)[i] = abs(retV) % 10;
    }
  }

  vector<int> * RunPhases(int count)
  {
    phaseVector.resize(mdata.size());
    vector<int>* input = &phaseVector;
    vector<int>* cache = &mdata;

    for (int i : rangeint(1, count))
    {
     cout << "phase " << i << endl;

      vector<int>* t = input;
      input = cache;
      cache = t;

      Phase(input, cache);
    }
    return cache;
  }

  string Part1() override
  {
    ReadData();

    vector<int> * finaldata = RunPhases(100);

    string ret;
    for (int i : rangeint(0, 7))
      ret += to_string((*finaldata)[i]);

    return ret;
  }

  void MultiplyInputData(int count)
  {
    auto clone = mdata;
    for (int i : rangeint(1, count - 1))
      copy(begin(clone), end(clone), back_inserter(mdata));
  }

  string Part2() override
  {
    ReadData();

    string offset;
    for (int i : rangeint(0, 6))
      offset += to_string(mdata[i]);
    int offsetVal = stoi(offset);

    cout << "Offset is " << offsetVal << endl;

    MultiplyInputData(10000);

    auto * signal = RunPhases(100);

    string ret;
    for (int i = 0; i < 8; ++i)
      ret += to_string((*signal)[i + offsetVal]);

    return ret;
  }
};
