#pragma once

void pic(string data)
{
  const char* output = data.c_str();
  const size_t len = strlen(output) + 1;
  HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
  memcpy(GlobalLock(hMem), output, len);
  GlobalUnlock(hMem);
  OpenClipboard(0);
  EmptyClipboard();
  SetClipboardData(CF_TEXT, hMem);
  CloseClipboard();
}

template<class T>
void pic(T v)
{
  return pic(std::to_string(v));
}

struct Point
{
  int x{ 0 }, y{ 0 };

  bool operator ==(const Point& other) const
  {
    return x == other.x && y == other.y;
  }

  bool operator != (const Point& other) const
  {
    return !operator ==(other);
  }

  bool operator < (const Point& other) const
  {
    if (other.y < y) return true;
    if (y == other.y && x < other.x)
      return true;
    return false;
  }

  Point Down() const
  {
    return Point{ x, y - 1 };
  }

  Point Left() const
  {
    return Point{ x - 1, y };
  }

  Point Right() const
  {
    return Point{ x + 1, y };
  }

  Point Up() const
  {
    return Point{ x, y + 1 };
  }

  Point FromOrientation(char orientation) const
  {
    switch (orientation)
    {
    case 'N':
    case 'n':
      return Up();
    case 'e':
    case 'E':
      return Right();
    case 'w':
    case 'W':
      return Left();
    case 's':
    case 'S':
      return Down();
    }
    return *this;
  }

  Point FromDirection(char orientation) const
  {
    switch (orientation)
    {
    case 'u':
    case 'U':
      return Up();
    case 'r':
    case 'R':
      return Right();
    case 'l':
    case 'L':
      return Left();
    case 'd':
    case 'D':
      return Down();
    }
    return *this;
  }

  vector<Point> GetNeighbours() const
  {
    vector<Point> ret;
    ret.push_back(Left());
    ret.push_back(Up());
    ret.push_back(Right());
    ret.push_back(Down());

    ret.push_back(Up().Left());
    ret.push_back(Up().Right());
    ret.push_back(Down().Left());
    ret.push_back(Down().Right());

    return ret;
  }

  int ManhattanDist(const Point& p) const
  {
    return abs(x - p.x) + abs(y - p.y);
  }

  bool IsInGrid(int width, int height) const
  {
    return x >= 0 && y >= 0 && x < width && y < height;
  }
};

vector<string> RegexMatch(string s, string regex)
{
  std::regex re2(regex);
  std::smatch match2;
  std::regex_search(s, match2, re2);
  vector<string> ret;
  for (size_t i = 1; i < match2.size(); ++i)
    ret.push_back(match2.str(i));
  return ret;
}

string RegexReplace(string s, string rgx, string replace)
{
  regex re(rgx);
  return regex_replace(s, re, replace);
}

template<class T>
vector<T> GetDigits(T n)
{
  if (n == 0)
    return { 0 };

  vector<T>  ret;
  while (n > 0)
  {
    ret.insert(begin(ret), n % 10);
    n /= 10;
  }
  return ret;
}

vector<string> rff(string filePath, function<void(string &)> func = nullptr)
{
  vector<string> ret;
  ifstream f;
  f.open(filePath);
  string s;
  
  while (getline(f, s))
  {
    if (func != nullptr) func(s);
    ret.push_back(s);
  }

  return ret;
}

vector<string> tok(string str, char sep = ' ')
{
  stringstream s(str); // Used for breaking words 
  string word; // to store individual words 

  vector<string> ret;

  while (getline(s, word, sep))
    ret.push_back(word);

  return ret;
}

string ltrim(string str)
{
  while (!str.empty() && str.front() == ' ')
    str.erase(begin(str));
  return str;
}

string rtrim(string str)
{
  while (!str.empty() && str.back() == ' ')
    str.pop_back();
  return str;
}

string trim(string str)
{
  return ltrim(rtrim(str));
}

int manhattan(int x1, int y1, int x2, int y2)
{
  return abs(x1 - x2) + abs(y1 - y2);
}

string tolower_str(string s)
{
  string newS = s;
  transform(begin(newS), end(newS), begin(newS), ::tolower);
  return newS;
}

string replacestr(string str, const string & search, string replace) {
  size_t pos = 0;
  while ((pos = str.find(search, pos)) != std::string::npos) 
  {
    str.replace(pos, search.length(), replace);
    pos += replace.length();
  }
  return str;
}

template<class T>
class DynamicMap
{
public:
  using DT = unordered_map<int, unordered_map<int, T>>;

  DT data;

  int max_y = numeric_limits<int>::min();
  int max_x = numeric_limits<int>::min();
  int min_x = numeric_limits<int>::max();
  int min_y = numeric_limits<int>::max();

  bool at(Point p, T * aOutVal)
  {
    auto xData = data.find(p.x);
    if (xData == end(data))
      return false;
    auto yData = xData->second.find(p.y);
    if (yData == end(xData->second))
      return false;

    if (aOutVal != nullptr)
      *aOutVal = yData->second;

    return true;
  }

  void set(Point p, T value)
  {
    if (p.x < min_x)
      min_x = p.x;
    if (p.x > max_x)
      max_x = p.x;
    if (p.y < min_y)
      min_y = p.y;
    if (p.y > max_y)
      max_y = p.y;

    data[p.x][p.y] = value;
  }

  vector<int> range_x() const
  {
    vector<int> ret(width());
    iota(begin(ret), end(ret), min_x);
    return ret;
  }

  vector<int> range_y() const
  {
    vector<int> ret(height());
    iota(begin(ret), end(ret), min_y);
    return ret;
  }

  bool empty() const
  {
    return data.empty();
  }

  int width() const
  {
    return abs(max_x - min_x) + 1;
  }

  int height() const
  {
    return abs(max_y - min_y) + 1;
  }

  void printf(string filePath, char empty= ' ', bool append = false, string prologue = "")
  {
    ofstream fOut;
    fOut.open(filePath, append ? ios_base::app : ios_base::out);

    if(append)
      fOut << endl;
    if (prologue.size() > 0)
      fOut << prologue << endl;

    for (int i = min_x; i <= max_x; ++i)
    {
      for (int j = min_y; j <= max_y; ++j)
      {
        T data;
        if (!at({ i, j }, &data))
          data = empty;

        fOut << data;
      }
      fOut << endl;
    }
    fOut.close();
  }
};

template<class T>
struct objmap
{
  int crtIndex{ 0 };
  unordered_map<T, int> mapping;
  
  int add(const T& obj)
  {
    auto found = mapping.find(obj);
    if (found != mapping.end())
      return found->second;
    else
    {
      mapping[obj] = crtIndex;
      return crtIndex++;
    }
  }

  int operator() (const T& obj) 
  {
    return add(obj);
  }

  int operator [](const T& obj)
  {
    return add(obj);
  }

  T translate(int index)
  {
    for (auto m : mapping)
      if (m.second == index)
        return m.first;
    return T();
  }
};

//--------------------------------------

template <>
struct hash<Point>
{
  std::size_t operator()(const Point& k) const
  {
    return (size_t)k.y * 10000ull + k.x;
  }
};

vector<int> rangeint(int from, int to)
{
  vector<int> ret((long long)to - (long long)from + 1);
  iota(begin(ret), end(ret), from);
  return ret;
}

template<class T>
void printvec(vector<T>& v)
{
  cout << endl;
  for (auto& el : v)
    cout << el << " ";
}

template<class T>
void printset(set<T>& v)
{
  cout << endl;
  for (auto& el : v)
    cout << el << " ";
}

template<class T>
void printset(unordered_set<T>& v)
{
  cout << endl;
  for (auto& el : v)
    cout << el << " ";
}

template<class T, class U>
void printmap(map<T, U>& m)
{
  cout << endl;
  for (auto& el : m)
  {
    cout << "[" << el.first << "] = " << el.second << endl;
  }
}

template<class T, class U>
void printmap(unordered_map<T, U>& m)
{
  cout << endl;
  for (auto& el : m)
  {
    cout << "[" << el.first << "] = " << el.second << endl;
  }
}

class Graph
{

  typedef pair<int, int> WeightNodePair;

  int vertexCount;

  vector<list< pair<int, int>>> adjacency;

  void DoTopoSort(int v, bool visited[],
    stack<int>& Stack)
  {
    // Mark the current node as visited. 
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex 
    list<pair<int, int>>::iterator i;
    for (i = adjacency[v].begin(); i != adjacency[v].end(); ++i)
      if (!visited[i->first])
        DoTopoSort(i->first, visited, Stack);

    // Push current vertex to stack which stores result 
    Stack.push(v);
  }

public:

  Graph(int aVertexCount)
  {
    this->vertexCount = aVertexCount;
    adjacency.resize(aVertexCount);
  }

  void AddEdge(int node1, int node2, int weight)
  {
    adjacency[node1].push_back(make_pair(node2, weight));
    adjacency[node2].push_back(make_pair(node1, weight));
  }

  void ClearEdge(int node1, int node2)
  {
    for (auto node1edge = adjacency[node1].begin(); 
         node1edge != adjacency[node1].end(); node1edge++)
    {
      if (node1edge->first == node2)
      {
        adjacency[node1].erase(node1edge);
        break;
      }
    }
    for (auto node2edge = adjacency[node2].begin(); 
         node2edge != adjacency[node2].end(); node2edge++)
    {
      if (node2edge->first == node1)
      {
        adjacency[node2].erase(node2edge);
        break;
      }
    }
  }

  void AddAdjacencyMatrix(DynamicMap<int>& aMap)
  {
    adjacency.clear();
    adjacency.resize(vertexCount);

    for (int i = aMap.min_x; i <= aMap.max_x; ++i)
    {
      for (int j = aMap.min_y; j <= aMap.max_y; ++j)
      {
        int val = 0;
        if (aMap.at({ i , j }, &val))
        {
          if (val > 0)
          {
            AddEdge(i, j, val);
          }
        }
      }
    }
  }

  map<int, int> GetDistances(int src)
  {
    priority_queue<WeightNodePair, vector<WeightNodePair>, greater<WeightNodePair>> pq;

    vector<int> dist(vertexCount, numeric_limits<int>::max() - 1);

    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty())
    {
      int u = pq.top().second;
      pq.pop();

      for (auto i = adjacency[u].begin(); i != adjacency[u].end(); ++i)
      {
        int v = (*i).first;
        int weight = (*i).second;

        if (dist[v] > dist[u] + weight)
        {
          dist[v] = dist[u] + weight;
          pq.push(make_pair(dist[v], v));
        }
      }
    }

    map<int, int> distanceMap;
    for (int i = 0; i < vertexCount; ++i)
      distanceMap[i] = dist[i];
    return distanceMap;
  }

  vector<int> GetShortestPath(int src, int dest)
  {
    priority_queue<WeightNodePair, vector<WeightNodePair>, greater<WeightNodePair>> pq;

    vector<int> dist(vertexCount, numeric_limits<int>::max() - 1);
    vector<int> prev( vertexCount, -1 );

    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty())
    {
      int u = pq.top().second;
      pq.pop();
      if (u == dest)
        break;

      for (auto i = adjacency[u].begin(); i != adjacency[u].end(); ++i)
      {
        int v = (*i).first;
        int weight = (*i).second;

        if (dist[v] > dist[u] + weight)
        {
          dist[v] = dist[u] + weight;
          pq.push(make_pair(dist[v], v));
          prev[v] = u;
        }
      }
    }

    vector<int> retNodes;
    int u = dest;
    while (prev[u] >= 0 || u == src)
    {
      retNodes.insert(begin(retNodes), u);
      u = prev[u];
      if (u < 0)
        break;
    }

    return retNodes;
  }

  vector<int> SortTopologically()
  {
    stack<int> Stack;

    // Mark all the vertices as not visited 
    bool* visited = new bool[vertexCount];
    for (int i = 0; i < vertexCount; i++)
      visited[i] = false;

    // Call the recursive helper function to store Topological 
    // Sort starting from all vertices one by one 
    for (int i = 0; i < vertexCount; i++)
      if (visited[i] == false)
        DoTopoSort(i, visited, Stack);

    vector<int> ret;
    // Print contents of stack 
    while (Stack.empty() == false) {
      ret.push_back(Stack.top());
      Stack.pop();
    }
    return ret;
  }
};


//--------------------------------------

#define KINPUT "C:\\aoc-2019\\AocSolutions\\inputs\\Day"
#define KOUTPUT "C:\\aoc-2019\\AocSolutions\\output\\"
