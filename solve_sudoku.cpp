#pragma once

#include <vector>
#include <iostream>


using namespace std;

typedef unsigned char uint8_t;

//0=unsolved
//その他はその他
#define UNSOLVED 0

// 指定座標(x, y)に入る可能性をビット列で返す（1-4の数字用、4ビット）
uint8_t get_candidates(const vector<vector<uint8_t>>& board, int x, int y) {
    if(board[x][y] != UNSOLVED) return 0; // 既に埋まっている場合は候補なし
    uint8_t mask = 0b11110; // 1-4の4ビット(1,2,3,4)が1
    // 行・列・ブロックに既に使われている数字を除外
    for(int i=0; i<4; ++i) {
        if(board[x][i] >= 1 && board[x][i] <= 4) mask &= ~(1 << (board[x][i]));
        if(board[i][y] >= 1 && board[i][y] <= 4) mask &= ~(1 << (board[i][y]));
    }
    // 2x2ブロック内の数字を除外
    int bx = (x/2)*2, by = (y/2)*2;
    for(int i=0; i<2; ++i) for(int j=0; j<2; ++j) {
        uint8_t v = board[bx+i][by+j];
        if(v >= 1 && v <= 4) mask &= ~(1 << v);
    }
    // 下位4ビット(1-4)を返す
    return mask >> 1;
}

// 1手だけ確定マスを埋めて返す関数
vector<vector<uint8_t>> solve_sudoku_asquare(vector<vector<uint8_t>> board){
    for(int i=0; i<4; ++i){
        for(int j=0; j<4; ++j){
            if(board[i][j] == UNSOLVED){
                uint8_t cand = get_candidates(board, i, j);
                // 候補が1つだけならその値で確定
                if(cand && (cand & (cand-1)) == 0){
                    // candは1,2,4,8のいずれか
                    for(int v=1; v<=4; ++v){
                        if(cand == (1<<(v-1))){
                            board[i][j] = v;
                            return board;
                        }
                    }
                }
            }
        }
    }
    // どこも確定できなければそのまま返す
    return board;
}

// 盤面が変化しなくなるまで1マス確定埋めを繰り返す関数
vector<vector<uint8_t>> solve_sudoku(vector<vector<uint8_t>> board) {
    while (true) {
        vector<vector<uint8_t>> next = solve_sudoku_asquare(board);
        if (next == board) break;
        board = next;
    }
    return board;
}


void show_sudoku(vector<vector<uint8_t>> board){
    // 盤面を表示
    for(const auto& row : board){
        for(const auto& v : row){
            if(v == 0){
                cout << "  "; // 0は空白2つ
            }else if(v >= 1 && v <= 4){
                cout << (int)v << ' ';
            }else{
                cout << "? "; // 0-4以外は?で表示
            }
        }
        cout << endl;
    }
}