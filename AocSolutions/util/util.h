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
      return Up();
    case 'E':
      return Right();
    case 'W':
      return Left();
    case 'S':
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

vector<int> GetDigits(int n)
{
  if (n == 0)
    return { 0 };

  vector<int>  ret;
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

  /*T operator [](int p, T* aOutVal)
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
  }*/

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

  int width() const
  {
    return abs(max_x - min_x);
  }

  int height() const
  {
    return abs(max_y - min_y);
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

  int operator() (const T & obj) {
    auto found = mapping.find(obj);
    if (found != mapping.end())
      return found->second;
    else
      return -1;
  }

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
};

//--------------------------------------

template <>
struct hash<Point>
{
  std::size_t operator()(const Point& k) const
  {
    return k.y * 10000 + k.x;
  }
};

template<class T>
class Dijkstra
{
public:

  DynamicMap<T>& mData;

  Dijkstra(DynamicMap<T>& data) : mData(data) { }

  void GetNeighbours(const Point& p, vector<Point>& ret)
  {
    ret.clear();
    Point east = p.FromOrientation('E');
    Point west = p.FromOrientation('W');
    Point north = p.FromOrientation('N');
    Point south = p.FromOrientation('S');

    /*if (!IsWall(east)) ret.push_back(east);
    if (!IsWall(west)) ret.push_back(west);
    if (!IsWall(north)) ret.push_back(north);
    if (!IsWall(south)) ret.push_back(south);*/
  }

  unordered_map<Point, int> dist;
  unordered_map<Point, Point> prevPoint;

  struct MinQueuePred
  {
    Dijkstra& mDij;

    MinQueuePred(Dijkstra& main)
      : mDij(main)
    {
    }

    bool operator()(const Point& a, const Point& b) const
    {
      int da = mDij.dist[a];
      int db = mDij.dist[b];
      bool bb = da < db;
      if (bb)
        return true;
      if (da == db)
        return a < b;

      return bb;
    }
  };

  void FillPaths(const Point& from)
  {
    queue<Point> Q;
    unordered_map<Point, int> visitData;

    Q.push(from);
    visitData[from] = 0;

    vector<Point> neighbours;
    while (!Q.empty())
    {
      Point curr = Q.front();
      Q.pop();
      int currD = visitData[curr];
      GetNeighbours(curr, neighbours);
      for (auto& n : neighbours)
      {
        if (true)//(!IsWall(n) && visitData.find(n) == end(visitData))
        {
          visitData[n] = currD;//+ (IsDoorAt(n) ? 1 : 0);
          Q.push(n);
        }
      }
    }

    /*auto maxE = max_element(begin(visitData), end(visitData), [](auto& e1, auto& e2) { return e1.second < e2.second; });
    cout << maxE->second << endl;

    auto acc = count_if(begin(visitData), end(visitData), [&](auto& e) { return IsRoomAt(e.first) && e.second >= 1000; });

    cout << acc << endl;*/
  }

  void  RunPaths(const Point& from)
  {
    multiset<Point, MinQueuePred> Q;
    vector<Point> neigh;
    Q.clear();

    for (int x = mData.min_x; x <= mData.max_x; ++x)
    {
      for (int y = mData.min_y; y <= mData.max_y; ++y)
      {
        Point p{ x, y };
        if (!mData.at(p)) // xxx
          continue;

        dist[p] = numeric_limits<int>::max() - 1;
        if (x == from.x && y == from.y)
          dist[p] = 0;
        prevPoint[p] = { numeric_limits<int>::max(), numeric_limits<int>::max() };
        Q.insert(p);
      }
    }

    while (!Q.empty())
    {
      Point u = *Q.begin();
      Q.erase(Q.begin());

      GetNeighbours(u, neigh);

      for (auto v : neigh)
      {
        int alt = dist[u] + 1;
        if (alt < dist[v])
        {
          dist[v] = alt;
          prevPoint[v] = u;

          Q.erase(v);
          Q.insert(v);
        }
      }
    }
  }
};

struct Lee
{
  DynamicMap<int>& mdata;

  queue<int> X, Y; // the queues used to get the positions in the matrix

  Lee(DynamicMap<int>& data, int start_x, int start_y)
    : mdata(data)
  {
    X.push(start_x); //initialize the queues with the start position
    Y.push(start_y);
  }

  void operator()()
  {
    int dl[]{ -1, 0, 1, 0 }; // these arrays will help you travel in the 4 directions more easily
    int dc[]{ 0, 1, 0, -1 };

    int x, y, xx, yy;
    while (!X.empty()) // while there are still positions in the queue
    {
      x = X.front(); // set the current position
      y = Y.front();
      for (int i = 0; i < 4; i++)
      {
        xx = x + dl[i]; // travel in an adiacent cell from the current position
        yy = y + dc[i];

        //'position is valid' XXX
        if (1) //here you should insert whatever conditions should apply for your position (xx, yy)
        {
          X.push(xx); // add the position to the queue
          Y.push(yy);
          mdata.set({ xx,yy }, -1); // you usually mark that you have been to this position in the matrix
        }

      }

      X.pop(); // eliminate the first position, as you have no more use for it
      Y.pop();
    }


  }
};

//--------------------------------------

#define KINPUT "C:\\aoc-2019\\AocSolutions\\inputs\\Day"
#define KOUTPUT "C:\\aoc-2019\\AocSolutions\\output\\"
