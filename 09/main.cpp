#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include "../include/args.h"

using namespace std;

int main (int argc, char ** argv) {
  process_args(argc, argv);
  auto start = chrono::high_resolution_clock::now();
  ifstream in(argv[1]);
  vector<vector<int>> lines;
  vector<vector<int>> reverse_lines;
  long part1 = 0, part2 = 0;

  if (!in.good()){
    return -1;
  }

  string line;
  while (getline(in,line)) {
    vector<int> nums;
    vector<int> rnums;
    istringstream ss(line);
    int num;
    while (ss >> num) {
      nums.push_back(num);
      rnums.push_back(num);
    }
    reverse(rnums.begin(), rnums.end());
    lines.push_back(nums); 
    reverse_lines.push_back(rnums);
  }

  in.close();

  for (auto nums : lines) {
    vector<int> solution;
    solution.push_back(nums.back());
    while (nums.size() > 0) {
      for (int i = 0; i < nums.size()-1; ++i) {
        nums[i] = nums [i+1] - nums[i];
      }
      nums.pop_back();
      solution.push_back(nums.back());

      bool is_zeroes = true;

      for (int n : nums) {
        if (n != 0) {
          is_zeroes = false;
          break;
        }
      }
      if (is_zeroes) {
        break;
      }
    }
    for (int n : solution) {
      part1 += n;
    }
  }
  
  cout << "Part 1: " << part1 << endl;
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Clock time: " << duration.count() << " ms" << endl;
  return 0;
}
