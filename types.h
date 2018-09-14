//
//  types.h
//  Project 2 
//
//  Created by Ashley Coleman on 7/5/18.
//  Copyright © 2018 Ashley Coleman. All rights reserved.
//

#ifndef types_h
#define types_h

#define MAX_WIDTH 100
#define MAX_HEIGHT 100

typedef struct
{
    int width;
    int height;
    int board[MAX_WIDTH][MAX_HEIGHT];
} Board;

#endif /* types_h */
