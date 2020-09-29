//Sudoku Solver
//  By Zachary Chapman
//
//  This progarm will solve any given 9x9 sudoku board using backtracking.
//  The rules of sudoku are no same number can be place in the same column, row, or sub square. 
//  The sub square is a smaller 3x3 square inside of the larger 9x9 board. 
//  Once a number is in every space all all condition are met the sudoku board is successfully solved. 

#include <iostream>
#include <cstdlib>

using namespace std;

//Print function
void print(int sudoku[9][9])
{
    for(int i = 0;i != 9; i++) 
    {
        if(i%3 == 0) 
        {
            for(int j = 0;j != 13; j++)
                cout << "- ";
            cout << '\n';
        }
        for(int j = 0;j != 9; j++) 
        {
            if(j%3 == 0) 
                cout << "| ";
            cout << sudoku[i][j] << ' ';
            if(j == 8) 
                cout << "|";
        }
        cout << '\n';
    }
    for(int j = 0;j != 13; j++)
        cout << "- ";
}

//Function to see if num is being placed in a valid location
bool success(int sudoku[9][9], int row, int col, int num) 
{
    //Loop to see if num is already in that row or col
    for(int i = 0;i != 9; i++) 
    {
        if(sudoku[row][i] == num || sudoku[i][col] == num) 
            return false;   //Return false because num is already in that row or col
    }
    
    //Variables for the bounds of the sub square
    int sub_r = (row/3);
    int sub_c = col/3;
    sub_r *= 3;
    sub_c *= 3;
    
    //Loop to see if num is already in the sub square of the board
    for(int i = sub_r;i != sub_r+3; i++) 
    {
        for(int j = sub_c;j != sub_c+3; j++) 
        {
            if(sudoku[i][j] == num)
                return false;   //return false becasue num is already in the sub square 
        }
    }
    
    //return tue if num is not in that col, row, or sub square
    return true;
}

//Function to solve the sudoku board using backtracking and recursion
bool solve(int sudoku[9][9], int index = 0) 
{
    //return true if the sudoku board is full
    if(index == 81) 
        return true;
    
    //Row and Column variables
    int row = index/9;
    int col = index%9;
    
    //If the space has a number already in it move to the next space
    if(sudoku[row][col] != 0)
        return solve(sudoku, index+1);
        
    //Print statment to show the board at every step for trouble shooting
    //print(sudoku);    
    //cout << row << ',' << col << '\n';
   
   
    for(int i = 1;i != 10; i++) 
    {
        if(sudoku[row][col] == 0 && success(sudoku, row, col, i)) //If space is empty and i is a valid number
        {
            sudoku[row][col] = i;
            if(solve(sudoku, index+1))  //Move to solve the next space
                return true;
            sudoku[row][col] = 0;   //Set to zero to check a previous number
        }
    }
    
    return false;   //return false if the sudoku board is impossible to solve
}


int main() {
    // change this grid to your sudoku board
    int sudoku[9][9] = 
    {
        {0, 3, 0, 0, 1, 0, 0, 6, 0},
        {7, 5, 0, 0, 3, 0, 0, 4, 8},
        {0, 0, 6, 9, 8, 4, 3, 0, 0},
        {0, 0, 3, 0, 0, 0, 8, 0, 0},
        {9, 1, 2, 0, 0, 0, 6, 7, 4},
        {0, 0, 4, 0, 0, 0, 5, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    if(!solve(sudoku)) 
    {
        cout << "Impossible to solve";
        return 0;
    }
    
    
    print(sudoku);  //print solved sudoku board to console.
    
    return 0;
}
