#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day6 : public ISolutionDay
{
private:

  vector<string> mData;

  set<pair<string, string>> orbits;
  set<string> objects;

public:

  Day6(){ }

  ~Day6() override { }

  int CalcOrbit(string k, vector<string> * out)
  {
    int count = 0;
    for (auto o : objects)
    {
      if (o == k)
        continue;

      if (orbits.find(make_pair(o, k)) != end(orbits))
      {
        count++;

        if (out != nullptr)
          out->push_back(o);

        count += CalcOrbit(o, out);
      }
    }

    return count;
  }

  void ReadData()
  {
    mData.clear();
    mData = rff(KINPUT "6\\input.txt");

    for (auto d : mData)
    {
      vector<string> tokens = RegexMatch(d, "(.+)\\)(.+)");
      orbits.insert(make_pair(tokens[0], tokens[1]));
      objects.insert(tokens[0]);
    }
  }

  string Part1() override
  {
    ReadData();

    int total = 0;
    vector<string> totalOrbits;
    for (auto o : orbits)
      total += CalcOrbit(o.second, nullptr);

    return std::to_string(total);
  }
  
  string Part2() override
  {
    ReadData();

    vector<string> vecYou;
    CalcOrbit("YOU", &vecYou);
    
    vector<string> vecSanta;
    CalcOrbit("SAN", &vecSanta);

    string target;

    for (size_t i = 0; i < vecYou.size(); ++i)
    {
      for (size_t j = 0; j < vecSanta.size(); ++j)
      {
        if (vecYou[i] == vecSanta[j])
        {
          target = vecYou[i];
          break;
        }
      }
      if (!target.empty())
        break;
    }

    int total = 0;
    for (size_t i = 0; i < vecYou.size(); ++i)
    {
      if (vecYou[i] != target)
        total++;
      else
        break;
    }

    for (size_t i = 0; i < vecSanta.size(); ++i)
    {
      if (vecSanta[i] != target)
        total++;
      else
        break;
    }

    return std::to_string(total);
  }
};
