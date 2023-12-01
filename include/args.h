#ifndef __ARGS_H__
#define __ARGS_H__
#include <iostream>


void process_args(int argc, char ** argv) {
    if (argc != 2) { 
        std::cout << "Usage: " << argv[0] << " <file>\n";
        exit(1);
    }
}

#endif

