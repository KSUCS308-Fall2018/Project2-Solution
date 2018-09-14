//
//  core.h
//  Project 2 
//
//  Created by Ashley Coleman on 7/5/18.
//  Copyright © 2018 Ashley Coleman. All rights reserved.
//

#ifndef core_h
#define core_h

#include <stdio.h>

#include "types.h"

#define TRUE 1
#define FALSE 0

int core_main(int argc, const char * argv[]);

int neighbor_count(Board * board, int j, int i); 
int write_board(Board * board, FILE * fp); 
int read_board(Board * board, FILE * fp); 

#endif /* core_h */
