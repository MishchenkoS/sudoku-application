
#ifndef SOME_UNIQUE_SUDOKU
#define SOME_UNIQUE_SUDOKU


using namespace std;

class Sudoku {
  private:


  protected:
    int table[9][9];
    int tableSudoku[9][9];

    public:

    Sudoku() {
      init();
    }

    void init() {
      int n = 3;
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++){
          table[i][j] = (i * n + i / n + j) % (n * n) + 1;
          tableSudoku[i][j] = (i * n + i / n + j) % (n * n) + 1;
        }
      }


    }

    void transposing() {
      int n = 3;
      for (int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
          table[j][i] = (i * n + i / n + j) % (n * n) + 1;
          tableSudoku[j][i] = (i * n + i / n + j) % (n * n) + 1;
        }
      }
    }

    void swapRowsSmall() {
      int nBlock = rand() % 3;
      int nRow1 = (rand() % 3) + nBlock * 3;
      int nRow2 = (rand() % 3) + nBlock * 3;

      while(nRow1 == nRow2) {
        nRow2 = (rand() % 3) + nBlock * 3;
      }

      int value;
      for(int i = 0; i < 9; i++) {
        value = table[nRow2][i];
        table[nRow2][i] = table[nRow1][i];
        tableSudoku[nRow2][i] = tableSudoku[nRow1][i];
        table[nRow1][i] = value;
        tableSudoku[nRow1][i] = value;
      }
    }

    void swapColumnsSmall() {
      int nBlock = rand() % 3;
      int nColumn1 = (rand() % 3) + nBlock * 3;
      int nColumn2 = (rand() % 3) + nBlock * 3;

      while(nColumn1 == nColumn2) {
        nColumn2 = (rand() % 3) + nBlock * 3;
      }

      int value;
      for(int i = 0; i < 9; i++) {
        value = table[i][nColumn2];
        table[i][nColumn2] = table[i][nColumn1];
        tableSudoku[i][nColumn2] = tableSudoku[i][nColumn1];
        table[i][nColumn1] = value;
        tableSudoku[i][nColumn1] = value;
      }
    }

    void swapRowsArea() {
      int nArea1 = rand() % 3;
      int nArea2 = rand() % 3;
      while (nArea1 == nArea2)
      {
        nArea2 = rand() % 3;
      }
      
      int value;
      for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 9; j++) {
          value = table[i+nArea1*3][j];
          table[i+nArea1*3][j] = table[i+nArea2*3][j];
          tableSudoku[i+nArea1*3][j] = tableSudoku[i+nArea2*3][j];
          table[i+nArea2*3][j] = value;
          tableSudoku[i+nArea2*3][j] = value;
        }
      }
    }

    void swapColumnsArea() {
      int nArea1 = rand() % 3;
      int nArea2 = rand() % 3;
      while (nArea1 == nArea2)
      {
        nArea2 = rand() % 3;
      }
      
      int value;
      for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 3; j++) {
          value = table[i][j+nArea1*3];
          table[i][j+nArea1*3] = table[i][j+nArea2*3];
          tableSudoku[i][j+nArea1*3] = tableSudoku[i][j+nArea2*3];
          table[i][j+nArea2*3] = value;
          tableSudoku[i][j+nArea2*3] = value;
        }
      }
    }

    void mix() {
      int count = rand() % 10 + 50;
      for(int i = 0; i < count; i++) {
        int val = rand() % 5;
        switch (val)
        {
        case 0:
          transposing();
          break;
        case 1:
          swapRowsSmall();
          break;
        case 2:
          swapColumnsSmall();
          break;
        case 3:
          swapRowsArea();
          break;
        case 4:
          swapColumnsArea();
          break;
        default:
          break;
        }
      }
    }

    void deleteCells(int diff) {
      //int difficult = 46 + (5*diff);
      int difficult = 30  + (10*diff);
      int itterator = 0;
      short int flag=0,flag1=0;
      int flook[9][9] = {
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0}
      };

      while ((itterator < difficult) && (flag1 != 81)) {
        int i = rand() % 9;
        int j = rand() % 9;
        flag = 0;
        flag1 = 0;
        while(flag != 81){
          flag++;
          flag1++;
          if(flook[i][j] == 0){
            flook[i][j] = 1;
            if(solver(i, j) == 0){
              table[i][j] = 0; 
              itterator++;
              flag = 81;
            }
          }
          j = (j + 1) % 9;
          if (!j){
            i = (i + 1) % 9;
          }
        }
      }
    }

    int solver(int y, int x) {
      int arr[9] = {1,2,3,4,5,6,7,8,9};
      int count = 9;
      for (int i = 0; i < 9; i++) {
        if ((table[i][x] != 0) && (findArr(table[i][x], arr))) {
          count--;
        }
        if ((table[y][i] != 0) && (findArr(table[y][i], arr))) {
          count--;
        }
      }

      int modx = x - (x % 3);
      int mody = y - (y % 3);

      for(int i = 0; (i < 3) && ((mody + i) != y); i++) {
        for(int j = 0; (j < 3) && ((modx + j) != x) && (table[mody + i][modx + j] != 0) && (findArr(table[mody + i][modx + j], arr)); j++) {
            count--;
        }
      }
      return count;

    }

    bool findArr(int val, int arr[]) {
      for(int j = 0; j < 9; j++) {
        if(arr[j] == val){
          arr[j] = 0;
          return true;
        }
      }
      return false;
    }
};

#endif
