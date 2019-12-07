#pragma once

#include "SolutionDay.h"
#include "util/util.h"

class Day8 : public ISolutionDay
{
private:
  int width{ 25 };
  int height{ 6 };
  vector<DynamicMap<int>> layers;

public:

  Day8(){ }

  ~Day8() override { }

  void ReadData()
  {
    vector<string> data = rff(KINPUT "8\\input.txt");
    string d = data[0];
    
    int crtx = 0, crty = 0;
    int crtlayer = 0;

    auto newLayer = DynamicMap<int>();
    layers.push_back(newLayer);

    for (size_t i = 0; i < d.size(); ++i)
    {
      layers.back().set({ crty, crtx }, d[i] - '0');
      crtx++;
      if (crtx >= width)
      {
        crty++;
        crtx = 0;
      }
      if (crty >= height)
      {
        crtlayer++;
        crtx = 0;
        crty = 0;
        auto newLayer = DynamicMap<int>();
        layers.push_back(newLayer);
      }
    }

    if (layers.back().empty())
      layers.erase(layers.end() - 1);
  }

  string Part1() override
  {
    ReadData();

    auto countDigits = [&](auto& l1, int what)
    {
      int t = 0;
      for (int j : l1.range_x())
        for (int i : l1.range_y())
        {
          int v = 0;
          if (l1.at({ j, i }, &v) && v == what)
            t++;
        }
      return t;
    };

    auto minEl = min_element(begin(layers), end(layers), [&](auto& l1, auto& l2)
    {
      return countDigits(l1, 0) < countDigits(l2, 0);
    });

    int count1 = countDigits(*minEl, 1);
    int count2 = countDigits(*minEl, 2);

    return std::to_string(count1 * count2);
  }
  
  string Part2() override
  {
    ReadData();
    int t = 82;

    DynamicMap<int> finalLayer = *layers.rbegin();

    for (auto layerIt = layers.rbegin() + 1; layerIt != layers.rend(); ++layerIt)
    {
      auto& crtLayer = *layerIt;

      for (int j : finalLayer.range_x())
        for (int i : finalLayer.range_y())
        {
          int newPixel = 0;
          if (crtLayer.at({ j, i }, &newPixel))
          {
            int oldPixel = 0;
            finalLayer.at({ j, i }, &oldPixel);
            if (newPixel != 2)
              finalLayer.set({ j ,i }, newPixel);
          }
        }
    }

    finalLayer.printf(KOUTPUT "out.txt", ' ');
    // you need to look at the output file to see what's written
    return std::to_string(t);
  }
};
