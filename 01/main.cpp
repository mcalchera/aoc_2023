#include <iostream>
#include <fstream>
#include <string>
#include "../include/args.h"

using namespace std;

int main (int argc, char ** argv) {
  process_args(argc, argv);
  long total = 0;
  ifstream in;
  string str;
  in.open(argv[1]);

  if (in.good()) {
    while ( getline(in,str)) {
      int first,last = -1;
      for (auto it = str.begin(); it != str.end(); ++it) {
        char c = *it;
        if (c >= '0' && *it <= '9') {
          if (first == -1) { // First is not initialized yet
            first = static_cast<int>(c);
            last = first;
          }
          else { // First already initialized, this is another number
            last = static_cast<int>(c);
          }
        }
      }
      total += first * 10 + last;
    }
  }
  cout << total << endl;
  return 0;
}
