#include <bits/stdc++.h>

#define DEBUG 6


std::fstream& lineat(std::fstream& file, unsigned int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

//Ana matris
int matris[9][9];

bool check_sq(int x, int y, int z) {

    for(int i=0;i<9;i++) {
        if(matris[x][i] == z) {
            return false;
        }
    }

    for(int i=0;i<9;i++) {
        if(matris[i][y] == z) {
            return false;
        }
    }

    int idx = (floor(y/3.00))*3;
    int idy = (floor(x/3.00))*3;

    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(matris[idy+i][idx+j]==z) {
                return false;
            }
        }
    }
    return true;
}

bool solve_sudoku() {
    for(int row=0; row<9; row++) {
        for(int col=0; col<9;col++) {
            if(matris[row][col]==0) {
                for(int putn = 1; putn<10; ++putn) {
                    if(check_sq(row, col, putn)) {
                        matris[row][col]=putn;
                        if(solve_sudoku()) {
                            return true;
                        } else {
                            matris[row][col]=0;
                        }
                        
                    }
                } return false;
            }
        }
    }
}

void print_answer() {

    std::cout << std::endl;
    for(int i=0; i<9; i++) {
        for(int j=0;j<9;j++) {
            std::cout << matris[i][j] << ", ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {

    std::cout << "debug=" << DEBUG
              << ", preparing...\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(500*DEBUG));

    std::cout << "go!\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    if(DEBUG != 0) {
        for(int i=1;i<=DEBUG; i++) {
            std::fstream read_file("./test");
            lineat(read_file,(10*i)-9);
            for(int row=0;row<9;row++) {
                for(int col=0; col<9;col++) {
                    read_file >> matris[row][col];
                }
            }
            auto start = std::chrono::high_resolution_clock::now();
            solve_sudoku();
            auto stop = std::chrono::high_resolution_clock::now();
            auto exectime = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
            print_answer();
            std::cout << "time: " << exectime.count() << " ms\n";
        }
    } else {
            std::fstream read_file("./test");
            for(int row=0;row<9;row++) {
                for(int col=0; col<9;col++) {
                    read_file >> matris[row][col];
                }
            }
            auto start = std::chrono::high_resolution_clock::now();
            solve_sudoku();
            auto stop = std::chrono::high_resolution_clock::now();
            auto exectime = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
            print_answer();
            std::cout << "time: " << exectime.count() << " ms\n";
    }

    return 0;
}
