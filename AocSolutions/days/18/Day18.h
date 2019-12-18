#pragma once

#include "SolutionDay.h"

// types for caching
using KeySetVector                = vector<set<char>>;
using KeySetsAndLocations         = pair<KeySetVector, vector<Point>>;
using KeySetAndLocationsCostCache = unordered_map<KeySetsAndLocations, int>;

template <>
struct hash<KeySetsAndLocations>
{
  std::size_t operator()(const KeySetsAndLocations& k) const
  {
    string s;
    for (auto c : k.first)
    {
      for (auto cc : c)
        s += cc;
    }
    for (auto p : k.second)
      s += p.ToString();

    return hash<string>()(s);
  }
};

class Day18 : public ISolutionDay
{
private:

  DynamicMap<char>            m;
  objmap<Point>               mapper;
  unique_ptr<Graph>           mapGraph;
  map<char, Point>            keys;
  map<char, Point>            doors;
  vector<Point>               position;
  int                         nodeCount = 0;
  KeySetAndLocationsCostCache costCache;

public:

  ~Day18() override { }

  void ConstructMapGraph()
  {
    if (mapGraph)
      return;

    // construct a graph
    mapGraph = make_unique<Graph>(nodeCount);

    // generate mapping indexes
    for (int y : m.range_y())
    {
      for (int x : m.range_x())
      {
        Point p{ x, y };
        if (m.hasAt(p, '#'))
          continue;

        // add to mapping hash
        int nodeIndex = mapper(p);
        nodeIndex;

        auto right = p.Right();
        if (!m.hasAt(right, '#'))
        {
          int rightIndex = mapper(right);
          mapGraph->AddEdgeSymmetrical(nodeIndex, rightIndex, 1);
        }

        auto down = p.Down();
        if (!m.hasAt(down, '#'))
        {
          int downIndex = mapper(down);
          mapGraph->AddEdgeSymmetrical(nodeIndex, downIndex, 1);
        }
      }
    }
  }

  void ReadData(string filePath)
  {
    vector<string> data = rff(filePath);

    int line = 0;
    for (auto lineStr : data)
    {
      int col = 0;
      for (char c : lineStr)
      {
        Point pos{ col, line };
        m[pos] = c;

        if (c == '@')
          position.push_back(pos);
        else if (c >= 'a' && c <= 'z')
        {
          keys[c] = pos;
        }
        else if (c >= 'A' && c <= 'Z')
        {
          doors[c] = pos;
        }

        if (c != '#')
          nodeCount++;

        col++;
      }
      line++;
    }
  }

  void CloseDoorAt(Graph& g, Point p)
  {
    int doorIndex = mapper[p];
    auto edgesTo = g.GetEdgesFrom(doorIndex);
    auto edgesFrom = g.GetEdgesFrom(doorIndex);
    for (auto eto : edgesTo)
      g.ClearEdge(doorIndex, eto);
  }

  void OpenDoorAt(Graph& g, Point p)
  {
    int doorIndex = mapper[p];
    
    vector<Point> nextTo = { p.Left(), p.Right(), p.Up(), p.Down() };
    for (auto n : nextTo)
    {
      int nIndex = mapper[n];
      if (!m.hasAt(n, '#'))
        g.AddEdgeSymmetrical(nIndex, doorIndex, 1);
    }
  }

  void OpenDoor(Graph& g, char d)
  {
    char crtDoor = toupper(d);
    auto found = doors.find(crtDoor);
    if (found != end(doors))
      OpenDoorAt(g, found->second);
  }

  void CloseDoor(Graph& g, char d)
  {
    char crtDoor = toupper(d);
    auto found = doors.find(crtDoor);
    if (found != end(doors))
      CloseDoorAt(g, found->second);
  }

  unordered_map<char, int> GetToKeyCosts(Graph & g, const set<char> & remainingKeys, Point p)
  {
    unordered_map<char, int> ret;
    int startNode = mapper[p];

    unordered_set<int> remainingKeyNodes;
    for (auto k : remainingKeys)
      remainingKeyNodes.insert(mapper[keys[k]]);

    for (auto k : remainingKeys)
    {
      int cost = -1;
      int kNode = mapper[keys[k]];

      if (keys[k] != p)
      {
        auto path = g.GetShortestPath(startNode, kNode);

        cost = path.size() - 1;

        for (auto pathNode : path)
        {
          if (pathNode != kNode && remainingKeyNodes.find(pathNode) != end(remainingKeyNodes))
          {
            // key is hidden by another key
            cost = -1;
            break;
          }
        }        
      }
      if (cost >= 0)
        ret[k] = cost;
    }

    return ret;
  }

  int FindSolution(Graph & crtG, const vector<Point> & currentPos, const KeySetVector & remainingKeys)
  {
    int remainingCount = 0;
    for (auto& rk : remainingKeys)
      remainingCount += rk.size();
    if (remainingCount == 0)
      return 0;

    KeySetsAndLocations id = make_pair(remainingKeys, currentPos);

    auto alreadyCalc = costCache.find(id);
    if (alreadyCalc != end(costCache))
      return alreadyCalc->second;

    vector<unordered_map<char, int>> whereCanRobotsGo;

    for (int i : rangeint(0, currentPos.size() - 1))
      whereCanRobotsGo.push_back(GetToKeyCosts(crtG, remainingKeys[i], currentPos[i]));

    int wMin = 99999999;

    for (auto robotGo : rangeint(0, whereCanRobotsGo.size() - 1))
    {
      for (auto whereGo : whereCanRobotsGo[robotGo])
      {
        const auto [crtKey, crtCost] = whereGo;

        auto rkeys = remainingKeys;

        for (auto& rk : rkeys)
          rk.erase(crtKey);

        OpenDoor(crtG, crtKey);

        Point keyPos = keys[crtKey];

        auto newPos = currentPos;
        newPos[robotGo] = keyPos;
        int wCost = crtCost + FindSolution(crtG, newPos, rkeys);

        CloseDoor(crtG, crtKey);

        if (wCost < wMin)
          wMin = wCost;
      }     
    }

    costCache[id] = wMin;
    return wMin;
  }
  
  string Part1() override
  {
    ReadData(KINPUT "18\\input.txt");
    ConstructMapGraph();

    set<char> remainingKeys;
    for (auto k : keys)
      remainingKeys.insert(k.first);

    Graph crtG = *mapGraph;

    auto answer = FindSolution(crtG, { position[0] }, { remainingKeys });

    //assert(answer == 4204);
    return std::to_string(answer);
  }

  void TransformPart2Input()
  {
    assert(position.size() == 1);
    Point pos = position[0];

    position.resize(4);

    m[pos] = m[pos.Up()] = m[pos.Down()] = m[pos.Left()] = m[pos.Right()] = '#';
    position[0] = pos.Left().Up();
    position[1] = pos.Right().Up();
    position[2] = pos.Left().Down();
    position[3] = pos.Right().Down();
    
    for (auto p : position)
      m[p] = '@';
  }

  string Part2() override
  {
    ReadData(KINPUT "18\\input.txt");
    ConstructMapGraph();
    TransformPart2Input();
    
    KeySetVector remainingKeys(4);

    Point sepPoint{ position[0].x + 1, position[0].y + 1 };

    for (auto k : keys)
    {
      Point pointK = k.second;
      int bucket = 0;

      if (pointK.x > sepPoint.x && pointK.y < sepPoint.y)
        bucket = 1;
      if (pointK.x < sepPoint.x && pointK.y >= sepPoint.y)
        bucket = 2;
      if (pointK.x > sepPoint.x && pointK.y >= sepPoint.y)
        bucket = 3;
      
      remainingKeys[bucket].insert(k.first);
    }

    auto answer = FindSolution(*mapGraph, position, remainingKeys);
    //assert(answer == 1682);
    return std::to_string(answer);
  }
};
