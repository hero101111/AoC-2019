#pragma once

#include "SolutionDay.h"

using DynMap = DynamicMap<char>;

struct DynMapWorld : enable_shared_from_this<DynMapWorld>
{
  DynMap crtState, newState;

  shared_ptr<DynMapWorld> outer{ nullptr };
  shared_ptr<DynMapWorld> inner{ nullptr };

  bool doingWork{ false };

  Point kCenter{ 2,2 };
  const int kLimit{ 4 };

  DynMapWorld()
  {
    for (int x : rangeint(0, 4))
      for (int y : rangeint(0, 4))
        crtState[{x, y}] = '.';
  }

  DynMapWorld(const DynMapWorld& other) = delete;

  vector<Point> TopCells() const
  {
    vector<Point> ret;
    for (int i : rangeint(0, kLimit))
      ret.push_back(Point{ i, 0 });
    return ret;
  }

  vector<Point> BottomCells() const
  {
    vector<Point> ret;
    for (int i : rangeint(0, kLimit))
      ret.push_back(Point{ i, kLimit });
    return ret;
  }

  vector<Point> LeftCells() const
  {
    vector<Point> ret;
    for (int i : rangeint(0, kLimit))
      ret.push_back(Point{ 0, i });
    return ret;
  }

  vector<Point> RightCells() const
  {
    vector<Point> ret;
    for (int i : rangeint(0, kLimit))
      ret.push_back(Point{ kLimit, i });
    return ret;
  }

  int LocalCount(vector<Point> vp)
  {
    int ret = 0;
    for (auto p : vp)
      if (p != kCenter && crtState.hasAt(p, '#'))
        ret++;
    return ret;
  }

  void Print(string filePath)
  {
    doingWork = true;
    if (outer && !outer->doingWork)
      outer->Print(filePath);

    if (crtState.for_each([](int c) { return c == '#'; }))
      crtState.printf(filePath, ' ', true, "\n");

    if (inner && !inner->doingWork)
      inner->Print(filePath);
    doingWork = false;
  }

  int AdjacentCount(Point p)
  {
    int ret = 0;
    vector<Point> neigh = { p.Left(), p.Right(), p.Up(), p.Down() };

    for (auto n : neigh)
    {
      if (n != kCenter && crtState.hasAt(n, '#'))
        ret++;

      if (n == kCenter && inner)
      {
        // go inner up
        if (n.Up() == p)
          ret += inner->LocalCount(inner->TopCells());

        // go inner down
        if (n.Down() == p)
          ret += inner->LocalCount(inner->BottomCells());

        // go inner left
        if (n.Left() == p)
          ret += inner->LocalCount(inner->LeftCells());

        // go inner right
        if (n.Right() == p)
          ret += inner->LocalCount(inner->RightCells());
      }
    }
    if (outer)
    {
      // go outer (left side)
      if (p.x == 0)
        ret += outer->LocalCount(vector<Point>{kCenter.Left()});

      // go outer (right side)
      if (p.x == kLimit)
        ret += outer->LocalCount(vector<Point>{kCenter.Right()});

      // go outer (top side)
      if (p.y == 0)
        ret += outer->LocalCount(vector<Point>{kCenter.Up()});

      // go outer (bottom side)
      if (p.y == kLimit)
        ret += outer->LocalCount(vector<Point>{kCenter.Down()});
    }
    return ret;
  }

  void SimulateStep()
  {
    newState = crtState;
    for (int y : crtState.range_y())
    {
      for (int x : crtState.range_x())
      {
        Point p{ x, y };
        if (p == kCenter)
          continue;

        int adjacent = AdjacentCount(p);

        bool bugDies = adjacent != 1;
        bool becomesInfested = adjacent == 1 || adjacent == 2;

        char atP = crtState[p];
        if (atP == '#' && bugDies)
          newState[p] = '.';
        if (atP == '.' && becomesInfested)
          newState[p] = '#';
      }
    }
    doingWork = true;

    if (inner && !inner->doingWork)
      inner->SimulateStep();
    if (outer && !outer->doingWork)
      outer->SimulateStep();

    crtState = newState;
    doingWork = false;
  }

  void SimulateOneMinute()
  {
    DynMapWorld * mostInner = this;
    {
      while (mostInner->inner)
        mostInner = &*mostInner->inner;
      if (!mostInner->inner && mostInner->CountBugsLocal() > 0)
      {
        mostInner->inner = make_shared<DynMapWorld>();
        mostInner->inner->outer = mostInner->shared_from_this();
      }
    }

    DynMapWorld * mostOuter = this;
    {
      while (mostOuter->outer)
        mostOuter = &*mostOuter->outer;
      if (!mostOuter->outer && mostOuter->CountBugsLocal() > 0)
      {
        mostOuter->outer = make_shared<DynMapWorld>();
        mostOuter->outer->inner = mostOuter->shared_from_this();
      }
    }

    SimulateStep();
  }

  int CountBugsLocal()
  {
    return crtState.for_each([](char c) { return c == '#'; });
  }

  int CountBugs()
  {
    int val = CountBugsLocal();

    doingWork = true;

    if (outer && !outer->doingWork)
      val += outer->CountBugs();
    if (inner && !inner->doingWork)
      val += inner->CountBugs();

    doingWork = false;
    return val;
  }
};

class Day24 : public ISolutionDay
{  
public:

  ~Day24() override { }


  DynMap ReadData()
  {
    vector<string> data = rff(KINPUT "24\\input.txt");

    DynMap m;
    int col = 0; int lineC = 0;
    for (auto line : data)
    {
      col = 0;

      for (char c : line)
      {
        m[{col, lineC}] = c;
        col++;
      }
      lineC++;
    }
    return m;
  }

  string Part1() override
  {
    DynMap m = ReadData();

    shared_ptr<DynMapWorld> world = make_shared<DynMapWorld>();
    world->crtState = m;
    // offset the center so that it doesn't influence results, that's needed for part2 only
    world->kCenter = Point(-999, -999); 

    vector<DynMap> states;

    while (true)
    {
      auto foundState = find(begin(states), end(states), world->crtState);
      if (foundState != end(states))
        break;
      states.push_back(world->crtState);
      world->SimulateStep();
    }

    long long ret = 0;
    long long pow = 1;
    for (int y : world->crtState.range_y())
    {
      for (int x : world->crtState.range_x())
      {
        if (world->crtState.hasAt(Point{ x, y }, '#'))
        {
          ret += pow;
        }
        pow *= 2;
      }
    }

    return std::to_string(ret);
  }

  string Part2() override
  {
    DynMap m = ReadData();
    
    shared_ptr<DynMapWorld> world = make_shared<DynMapWorld>();
    world->crtState = m;

    int CycleCount = 200;

    for (int i : rangeint(1, CycleCount))
    {
      world->SimulateOneMinute();

      //string logPath = "c:\\aoc-2019\\log-step-"s + to_string(i) + ".txt";
      //world->Print(logPath);
    }
    return std::to_string(world->CountBugs());
  }
};
