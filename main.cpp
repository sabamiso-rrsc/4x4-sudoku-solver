#include <stdio.h>
#include <vector>
#include <iostream>
#include "solve_sudoku.cpp"
#include <fstream>


int main(){
    // ファイルから4x4の0-5で構成されたvectorを読み込む
    std::vector<std::vector<uint8_t>> board(4, std::vector<uint8_t>(4));
    std::ifstream infile("input.txt");
    if (!infile) {
        std::cerr << "ファイルが開けません" << std::endl;
        return 1;
    }
    for(int i=0; i<4; ++i){
        for(int j=0; j<4; ++j){
            int val;
            infile >> val;
            if(val < 0 || val > 5){
                std::cerr << "値が不正です: " << val << std::endl;
                return 1;
            }
            board[i][j] = static_cast<uint8_t>(val);
        }
    }
    infile.close();
    // solve_sudokuで表示
    show_sudoku(board);
    board = solve_sudoku(board);
    show_sudoku(board);
    return 0;
}