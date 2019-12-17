#pragma once

#include "SolutionDay.h"
#include "util/util.h"
#include "util/IntComputer.h"

class Day17 : public ISolutionDay
{
public:

  ~Day17() override { }

  DynamicMap<char> m;
  Point robot;
  char  robotDir;

  vector<string> movements;
  int crtMoveCount = 0;

  bool isIntersection(Point crt)
  {
    return (m.hasAt(crt,         '#') && 
            m.hasAt(crt.Up(),    '#') && 
            m.hasAt(crt.Down(),  '#') &&
            m.hasAt(crt.Left(),  '#') && 
            m.hasAt(crt.Right(), '#'));
  }

  vector<Point> findIntersections()
  {
    vector<Point> ret;
    for (int i : m.range_x())
    {
      for (int j : m.range_y())
      {
        Point crt{ i, j };
        if (isIntersection(crt))
          ret.push_back(crt);
      }
    }
    return ret;
  }

  void GenerateMap()
  {
    IntComputer cpu2{ rff(KINPUT "17\\input.txt")[0] };
    cpu2.mInputFunction = []() { return 0; };

    int crtLine = 0;
    int crtCol = 0;

    cpu2.mOutputCallback = [&](int output) {
      if (output == 10)
      {
        crtLine++;
        crtCol = 0;
        return;
      }
      else
      {
        if (output != '#' && output != '.')
        {
          char data = output;
          robot = { crtCol, crtLine };
          robotDir = output;
        }
        m.set({ crtCol++, crtLine }, output);
      }
    };
    cpu2.Execute();
  }

  string Part1() override
  {
    int ret = 171;

    GenerateMap();

    auto intersections = findIntersections();

    int sum = 0;
    for (auto inter : intersections)
      sum += inter.x * inter.y;

    m.printf(KVERBOSE, ' ');

    return std::to_string(sum);
  }

  void ExploreMap()
  {
    map<Point, int> visited;
    while (true)
    {
      Point nextMove = robot.FromDirection(robotDir);
      bool validMove = m.hasAt(nextMove, '#');
     
      vector<Point> aroundMe;
      {
        vector<Point> cand { robot.Left(), robot.Up(), robot.Right(), robot.Down() };
        for (auto c : cand)
        {
          if (m.hasAt(c, '#'))
            aroundMe.push_back(c);
        }
      } 
      sort(begin(aroundMe), end(aroundMe), [&](auto& c1, auto& c2) {return visited[c1] < visited[c2]; });

      bool atIntersection = isIntersection(robot);

      bool rotated = false;

      if (validMove && !atIntersection)
      {
      }
      else
      {
        if (!aroundMe.empty())
        {
          nextMove = aroundMe.front();

          bool turnLeft = false;

          char dirRotL = Point::RotateDirection(robotDir, true);
          char dirRotR = Point::RotateDirection(robotDir, false);
          if (robot.FromDirection(dirRotL) == nextMove)
          {
            if (crtMoveCount > 0 ) movements.push_back(to_string(crtMoveCount));

            movements.push_back("L");
            crtMoveCount = 1;
            robotDir = dirRotL;
            rotated = true;
          }
          if (robot.FromDirection(dirRotR) == nextMove)
          {
            if (crtMoveCount > 0) movements.push_back(to_string(crtMoveCount));

            movements.push_back("R");
            crtMoveCount = 1;
            robotDir = dirRotR;
            rotated = true;
          }
        }
        else
        {
         
        }
      }

      if (m[nextMove] == '.')
      {
        if (crtMoveCount > 0) movements.push_back(to_string(crtMoveCount));
        cout << "FINISHED" << endl;
        return;
      }

      if (!rotated)
        crtMoveCount++;

      m[robot] = '@';
      visited[robot]++;
      robot = nextMove;
      m[robot] = robotDir;

      m.printf(KVERBOSE, ' ');
      int k = 0;
    }
  }

  string Part2() override
  {
    GenerateMap();    
    
   /* ifstream inputRobot(R"(C:\Users\Gabriel\Desktop\robotinput.txt)");
    string crtInputLine;
    inputRobot >> crtInputLine;

    IntComputer cpu{ rff(KINPUT "17\\input.txt")[0] };
    cpu.SetMemoryAt(0, 2);

    bool eol = false;
    cpu.mInputFunction = [&]()
    {
      if (eol)
      {
        eol = false;
        return 10;
      }

      if (inputRobot.eof() && crtInputLine.empty())
      {
        eol = true;
        return (int)'n';
      }

      if (crtInputLine.empty() && !inputRobot.eof())
        inputRobot >> crtInputLine;

      int c = crtInputLine.front();
      crtInputLine.erase(begin(crtInputLine));

      if (crtInputLine.empty())
        eol = true;

      return c; 
    };

    int result = 0;
    cpu.mOutputCallback = [&](int output) {
      result = output;
    };

    cpu.Execute();*/

    
    ExploreMap();
    for (auto m : movements)
      cout << m << ",";
     


    return std::to_string(1);
  }
};
