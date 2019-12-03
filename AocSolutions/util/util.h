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

vector<string> tok(string str)
{
  stringstream s(str); // Used for breaking words 
  string word; // to store individual words 

  vector<string> ret;

  while (s >> word)
    ret.push_back(word);

  return ret;
}

int manhattan(int x1, int y1, int x2, int y2)
{
  return abs(x1 - x2) + abs(y1 - y2);
}

#define KINPUT "C:\\aoc-2019\\AocSolutions\\inputs\\Day"
