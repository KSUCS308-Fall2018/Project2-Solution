//
//  main_test.c
//  Project 2 
//
//  Created by Ashley Coleman on 7/5/18.
//  Copyright © 2018 Ashley Coleman. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "min_unit.h"
#include "core.h"


void init_test_board(Board * b) {
    b->width = 5;
    b->height = 5;

    int board[5][5] = {
        {1, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 1},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0}
    };

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            b->board[i][j] = board[i][j];
        }
    }
}

static char * test_neighbor_count() {
    mu_begin_case("neighbor_count");

    mu_assert_i("neighbor_count(NULL, 0, 0) should return -1", -1, neighbor_count(NULL, 0, 0));
    
    Board b1;
    init_test_board(&b1);
    mu_assert_i("neighbor_count(b1, -1, 0) should return -1", -1, neighbor_count(&b1, -1, 0));

    Board b2;
    init_test_board(&b2);
    mu_assert_i("neighbor_count(b2, 0, -1) should return -1", -1, neighbor_count(&b2, 0, -1));

    Board b3;
    init_test_board(&b3);
    
    int counts[5][5] = {
        {1, 2, 2, 1, 0},
        {2, 4, 2, 3, 1},
        {1, 3, 2, 3, 0},
        {1, 1, 3, 3, 2},
        {1, 1, 2, 0, 1}
    };

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            mu_assert_i("Assert correct count", counts[i][j], neighbor_count(&b3, i, j));
        }
    } 

    mu_end_case("neighbor_count");
    return 0;
}

static char * test_write_board() {
    mu_begin_case("write_board");

    {
        mu_assert_i("write_board(NULL, NULL) should return FALSE", 0, write_board(NULL, NULL));
    }

    {
        Board b;
        init_test_board(&b);
        mu_assert_i("write_board(&b, NULL) should return FALSE", 0, write_board(&b, NULL));
    }

    {
        size_t size = 1000;
        char content_buffer[1000];
        char * contents = content_buffer;
        FILE * fp = open_memstream(&contents, &size);

        Board b;
        init_test_board(&b);

        int r = write_board(&b, fp);

        fflush(fp);

        mu_assert_i("write_board(&b, fp) should return TRUE", 1, r);
        mu_assert_s("Assert correctly written board", "5 5\n**...\n..*..\n..*.*\n.*...\n...*.\n", contents);
    }

    {
        size_t size = 1000;
        char content_buffer[1000];
        char * contents = content_buffer;
        FILE * fp = open_memstream(&contents, &size);

        Board b;
        b.width = 1;
        b.height = 3;

        b.board[0][0] = TRUE;
        b.board[1][0] = FALSE;
        b.board[2][0] = TRUE;

        int r = write_board(&b, fp);

        fflush(fp);

        mu_assert_i("write_board(&b, fp) should return TRUE", 1, r);
        mu_assert_s("Assert correctly written board", "1 3\n*\n.\n*\n", contents);
    }

    mu_end_case("write_board");
    return 0;
}

static char * test_read_board() {
    mu_begin_case("read_board");

    {
        mu_assert_i("read_board(NULL, NULL) should return FALSE", 0, read_board(NULL, NULL));
    }

    {
        Board b;
        mu_assert_i("read_board(&b, NULL) should return FALSE", 0, read_board(&b, NULL));
    }

    {
        char contents[] = "";
        FILE * fp = fmemopen(contents, strlen(contents), "r");
        mu_assert_i("read_board(NULL, fp) should return FALSE", 0, read_board(NULL, fp));
        fclose(fp);
    }

    {
    
        char contents[] = "3 4\n.**\n*..\n...\n***";
        FILE * fp = fmemopen(contents, strlen(contents), "r");

        Board b;
        int r = read_board(&b, fp);

        mu_assert_i("read_board(&b, fp) should return TRUE", 1, r);
        mu_assert_i("Width should be 3", 3, b.width);
        mu_assert_i("Height should be 4", 4, b.height);

        int values[4][3] = {
            {0, 1, 1},
            {1, 0, 0},
            {0, 0, 0},
            {1, 1, 1}
        };

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                mu_assert_i("Assert correct board value", values[i][j], b.board[i][j]);
            }
        }

        fclose(fp);
    }

    {
    
        char contents[] = "10 3\n..*...*...\n*.....***.\n.*..**..*.";
        FILE * fp = fmemopen(contents, strlen(contents), "r");

        Board b;
        int r = read_board(&b, fp);

        mu_assert_i("read_board(&b, fp) should return TRUE", 1, r);
        mu_assert_i("Width should be 10", 10, b.width);
        mu_assert_i("Height should be 3", 3, b.height);

        int values[3][10] = {
            {0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 1, 1, 1, 0},
            {0, 1, 0, 0, 1, 1, 0, 0, 1, 0}
        };

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 10; j++) {
                mu_assert_i("Assert correct board value", values[i][j], b.board[i][j]);
            }
        }

        fclose(fp);
    }

    mu_end_case("read_board");
    return 0;
}

static char * all_tests() {
    test_neighbor_count();
    test_write_board();
    test_read_board();
    return 0;
}

#ifdef TEST
int main(int argc, char **argv) {
    mu_run(all_tests);
    
    return 0;
}
#endif

