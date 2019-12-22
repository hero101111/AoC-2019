#pragma once

#include "SolutionDay.h"

enum class Action
{
  DealNew = 0,
  Cut,
  Increment
};

class Day22 : public ISolutionDay
{
private:

  vector<pair<Action, int>> actions;

public:

  vector<long long> GenerateStack(long long n)
  {
    vector<long long> ret(n + 1);
    for (long long i : rangeint(0, n))
    {
      ret[i] = i;
    }
    return ret;
  }

  vector<long long> DealNew(vector<long long> v)
  {
    reverse(begin(v), end(v));
    return v;
  }

  vector<long long> CutCards(vector<long long> v, long long n)
  {
    //long long negative = n < 0 ? -1 : 1;
    //n = (abs(n) % v.size()) * negative;
    if (n > 0)
    {
      rotate(v.begin(), v.begin() + n, v.end());
    }
    else
    {
      rotate(v.rbegin(), v.rbegin() + abs(n), v.rend());
    }
    return v;
  }

  vector<long long> DealIncrement(vector<long long> v, long long n)
  {
    vector<long long> ret(v.size());
    long long crtPos = 0;
    while (!v.empty())
    {
      ret[crtPos] = v.front();
      crtPos += n;
      crtPos %= ret.size();
      v.erase(begin(v));
    }
    return ret;
  }

  Day22() { }

  ~Day22() override { }

  void ReadData()
  {
    vector<string> data = rff(KINPUT "22\\input.txt");

    for (auto line : data)
    {
      vector<string> tokens = RegexMatch(line, R"((\S)(-?\d+))");
      long long n = stoi(tokens[1]);
      if (tokens[0] == "I")
      {
        // increment
        actions.push_back(make_pair(Action::Increment, n));
      }
      else if (tokens[0] == "N")
      {
        // deal new
        actions.push_back(make_pair(Action::DealNew, 0));
      }
      else if (tokens[0] == "C")
      {
        // cut
        actions.push_back(make_pair(Action::Cut, n));
      }
    }
  }

  string Part1() override
  {
    ReadData();

    auto stack = GenerateStack(10006);

    set<long long> values;

    for (auto line : actions)
    {
      if (line.first == Action::Increment)
      {
        // increment
        stack = DealIncrement(stack, line.second);
      }
      else if (line.first == Action::DealNew)
      {
        // deal new
        stack = DealNew(stack);
      }
      else if (line.first == Action::Cut)
      {
        // cut
        stack = CutCards(stack, line.second);
      }
    }

    long long dist = find(begin(stack), end(stack), 2019) - begin(stack);
    return std::to_string(dist);
  }

  string Part2() override
  {
    // the solution lies in the Powershell script calculate.ps1
    // because the numbers involved go way beyond what LONG LONG offers :(
    // and PowerShell has native support for big numbers

    return "41653717360577";
  }
};
