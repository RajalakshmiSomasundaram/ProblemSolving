/**************************************************************************************
Coin Board problem
 
Write a C++ program to collect maximum number of coins on an nxm board.However, note 
that the board has several inaccessible cells in this problem. If you meet inaccessable
cell on the board, you cannot move to the cell because it is not accessible.

0 means no coin. 2 indicates that the cell is not accessible.
Board size is less than or equal to 25x25

sample input and output
4 4
0 2 1 1
0 1 2 1
0 0 1 2
1 2 0 1

***************************************************************************************/

#include <iostream>
#include <string>

using namespace std;

/**
 * collect the coins in nxm board.
 *
 * It displays the maximum coins collected and also the path to collect them.
 * 
 *
 * @maxRows - n in nxm 
 * @maxCols - m in nxm
 * @coin_board - nxm matrix
 **/

void collect_coin(int maxRows, int maxCols, int **coin_board)

{
    int temp[maxRows+1][maxCols+1];
    temp[maxRows][maxCols] = 0;
    
    string arrow= "->";
    string path[maxRows+maxCols+2];
    
    
    for (int i=0;i<=maxCols;i++)
    {
        temp[0][i] = 0;
    }
    for (int i=0;i<=maxRows;i++)
    {
        temp[i][0]=0;
    }

    for(int i=1;i<=maxRows;i++)
    {
        for(int j=1;j<=maxCols;j++)
        {
            if(coin_board[i-1][j-1] != 2)
            {
                temp[i][j] = max(temp[i-1][j],temp[i][j-1]) + coin_board[i-1][j-1];
            }
            else
            {
                temp[i][j] =-1;
            }
        }
    }

    int l=0;
    path[0] = "(" + to_string(maxCols) + ","+ to_string(maxRows) + ")";
    l++; int flag=0;
    
    int i=maxRows, j=maxCols;
    while( (i>=1) && (j>=1))
    {
        if(temp[i-1][j] > temp[i][j-1])
        {
            if((i-1>=1) && (j>=1))
            {
                path[l] = "(" + to_string(j) + ","+to_string(i-1) + ")";
                l++;
            }
            i=i-1;
        }
        else
        {
            if((temp[i-1][j] == 0) && (temp[i][j-1]==0))
            {
                if((i-1==1) || (j-1==1))
                {
                      path[l] = "(" + to_string(1) + ","+to_string(1) + ")";
                      l++;
                      flag=1;
                }
            }
            if((i>=1) && (j-1>=1) && (flag==0))
            {
                path[l] = "(" + to_string(j-1) + ","+to_string(i) + ")";
                l++;
            }
            j=j-1;
        }
        
    }

    cout <<"Max coins:" <<temp[maxRows][maxCols] << endl;
    cout <<"Path:";
    for (int i=l-1; i>=0; i--)
    {
        cout << path[i];
        if (i>0)
        {
            cout<< "->";
        }
    }
    cout << endl;
    
}


int main()
{
    int rows=0,cols=0, **coin_board = NULL;
    
    cin >> cols >> rows;
    if ((rows!=0)&& (cols!=0))
    {
        coin_board = new int *[rows];
        for (int i=0;i<rows; ++i)
            coin_board[i] = new int[cols];
    }
    else
    {
        cout<<"invalid input";
        return 0;
    }
    if (coin_board == nullptr)
    {
        cout << "Error: memory could not be allocated";
        return 0; 
    }
    else
    {
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
            {
                cin >> coin_board[i][j];
            }
        }

        collect_coin(rows,cols, coin_board);
        
        for(int i = 0; i < rows; ++i)
        {
            delete [] coin_board[i];
        }
        delete [] coin_board;
    }

    return 0;
}



