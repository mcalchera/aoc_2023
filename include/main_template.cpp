#include <iostream>
#include <fstream>
#include <chrono>
#include "../include/args.h"

using namespace std;

int main (int argc, char ** argv) {
  process_args(argc, argv);
  auto start = chrono::high_resolution_clock::now();

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Clock time: " << duration.count() << " ms" << endl;
  return 0;
}
