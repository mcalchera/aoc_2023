#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <sstream>
#include "../include/args.h"

using namespace std;

map<char,int> face_values = {
  { 'A', 14 },
  { 'K', 13 },
  { 'Q', 12 },
  { 'J', 11 },
  { 'T', 10 }
};

int main (int argc, char ** argv) {
  process_args(argc, argv);
  auto start = chrono::high_resolution_clock::now();

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Clock time: " << duration.count() << " ms" << endl;
  return 0;
}
