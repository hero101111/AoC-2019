#pragma once

#include "SolutionDay.h"

struct ChemicalData
{
  string chemical;
  int quantity{ 0 };
};

struct Reaction
{
  vector<ChemicalData> inputs;
  ChemicalData output;
};

class Day14 : public ISolutionDay
{
private:

  objmap<string>        mapping;
  map<string, Reaction> mchem;
  vector<string>        topoSorted;

public:

  Day14() { }

  ~Day14() override { }

  ChemicalData ProcessChemical(string data)
  {
    auto tokens = RegexMatch(data, R"((\d+) (\S+))");
    ChemicalData ret;
    ret.chemical = trim(tokens[1]);
    ret.quantity = stoi(tokens[0]);

    return ret;
  }

  void ReadData()
  {
    vector<string> mdata = rff(KINPUT "14\\input.txt");
    for (auto& line : mdata)
    {
      auto tokens1 = RegexMatch(line, R"((.+) => (.+))");
      vector<string> inputs = tok(tokens1[0], ',');
      string output = tokens1[1];

      Reaction reaction;
      reaction.output = ProcessChemical(output);

      for (auto& input : inputs)
        reaction.inputs.push_back(ProcessChemical(input));

      mchem[reaction.output.chemical] = reaction;
    }
  }

  void Initialize()
  {
    ReadData();
    int ret = 141;

    Graph g(mchem.size() + 1);
    for (auto d : mchem)
    {
      int outIndex = mapping[d.first];
      for (auto input : d.second.inputs)
      {
        int inIndex = mapping[input.chemical];
        g.AddEdge(inIndex, outIndex, input.quantity);
      }
    }

    auto order = g.SortTopologically();
    for (auto o : order)
      topoSorted.push_back(mapping.translate(o));
  }

  long long Solve(int n)
  {
    auto graphWalk = topoSorted;

    map<string, long long> requirements;
    requirements["FUEL"] = n;

    while (graphWalk.size() > 1)
    {
      auto top = graphWalk.back();
      long long required = requirements[top];
      for (auto i : mchem[top].inputs)
      {
        long long factor = mchem[top].output.quantity;
        long long quant = ceil(required / (double)factor) * i.quantity;
        requirements[i.chemical] += quant;
      }
      graphWalk.pop_back();
    }
    return requirements["ORE"];
  }

  string Part1() override
  {
    Initialize();
    return to_string(Solve(1));
  }

  string Part2() override
  {
    Initialize();

    long long fuel = 1000000000000;

    long long minval = fuel / Solve(1);
    long long maxval = minval * 10;

    while (maxval > minval + 1)
    {
      long long searchPoint = minval + (maxval - minval) / 2;
      long long res = Solve(searchPoint);
      if (res > fuel) maxval = searchPoint;
      if (res < fuel) minval = searchPoint;
    }

    return std::to_string(minval);
  }
};
