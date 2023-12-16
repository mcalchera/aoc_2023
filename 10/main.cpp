#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <map>
#include "../include/args.h"

using namespace std;

struct coord {
  int x;
  int y;
};

inline bool operator==(const coord &c1, const coord &c2) {
   return c1.x == c2.x && c1.y == c2.y;
}
inline bool operator!=(const coord &c1, const coord &c2) {
   return !(c1 == c2);
}

int dist(coord c1, coord c2) {
  int radicand = ((c2.x - c1.x)*(c2.x - c1.x)) + ((c2.y - c1.y)*(c2.y - c1.y));
  return static_cast<int>(sqrt(static_cast<double>(radicand)));
}

bool is_traversible(vector<vector<char>> grid, coord start, coord next) {
  int x = next.x;
  int y = next.y;
  if ( x < 0 || y < 0 || x >= grid[y].size() || y >= grid.size()) {
    return false;
  }
  char c_next = grid[y][x];
  char c_start = grid[start.y][start.x];
  switch (c_next) {
    case '|':
      return (x == start.x);
      break;
    case '-':
      return (y == start.y);
      break;
    case 'L':
      return (x < start.x && y == start.y) || (y > start.y && x == start.x && c_start != '-');
      break;
    case 'J':
      return (x > start.x && y == start.y) || (y > start.y && x == start.x && c_start != '-');
      break;
    case '7':
      return (x > start.x && y == start.y && c_start != '|') || (y < start.y && x == start.x);
      break;
    case 'F':
      return (y < start.y && x == start.x && c_start != '|') || (y == start.y && x < start.x);
      break;
    case 'S':
      return true;
      break;
    default:
      return false;
  }  
}

coord travel(vector<vector<char>> grid, coord start, coord & prev) {
  vector<coord> vec;
  vec.push_back({ start.x, start.y-1 });
  vec.push_back({ start.x, start.y+1 });
  vec.push_back({ start.x+1, start.y });
  vec.push_back({ start.x-1, start.y });

  for ( auto dir : vec ) {
    // don't go backwards
    if (dir == prev) { 
      continue;
    }
    if (is_traversible(grid, start, dir)) {
      prev = start;
      return dir;
    }
  }
  return { 0, 0 }; // shouldn't hit this
}
// For debugging
void print_grid(vector<vector<char>> grid, coord c1, coord c2) {
  grid[c1.y][c1.x] = '#';
  grid[c2.y][c2.x] = '#';

  for (int y = 0; y < grid.size(); ++y) {
    for (int x = 0; x < grid[y].size(); ++x) {
      cout << grid[y][x];
    }
    cout << endl;
  }
}

int main (int argc, char ** argv) {
  process_args(argc, argv);
  auto start = chrono::high_resolution_clock::now();
  vector<vector<char>> grid;
  int x = 0;
  int y = 0;
  map<coord,int> distances;
  coord origin;
  coord curr;
  coord prev;

  ifstream in(argv[1]);

  if (!in.good())
    return -1;

  string str;
  while (getline(in, str)) {
    x = 0;
    vector<char> l;
    for (auto c : str) {
      if ( c == 'S' ) {
        origin = { x, y };
      }
      l.push_back(c);
      ++x;
    }
    grid.push_back(l);
    ++y;
  }
  in.close();

  // traverse the maze from both sides
  vector<coord> dirs;
  int part1 = 0;
  
  // Look north, south, east, and west of start to find the directions we can go.
  coord north = { origin.x, origin.y-1 };
  coord south = { origin.x, origin.y+1 };
  coord east = { origin.x+1, origin.y };
  coord west = { origin.x-1, origin.y };
  if (is_traversible(grid,origin, north))
    dirs.push_back(north);
  if (is_traversible(grid,origin, south))
    dirs.push_back(south);
  if (is_traversible(grid,origin, west))
    dirs.push_back(west);
  if (is_traversible(grid,origin, east))
    dirs.push_back(east);

  coord prev0 = origin;
  coord prev1 = origin;
  ++part1;
  coord dir0 = dirs[0];
  coord dir1 = dirs[1];
  while (dir0 != dir1) {
    //print_grid(grid, dir0, dir1);
    dir0 = travel(grid, dir0, prev0);
    dir1 = travel(grid, dir1, prev1);
    
    ++part1;

  } 

  cout << "Part 1: " << part1 << endl;
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Clock time: " << duration.count() << " ms" << endl;
  return 0;
}
