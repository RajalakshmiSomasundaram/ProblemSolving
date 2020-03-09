/******************************************************************************
Write a C++ program to solve the Coin Row problem. 
The program should read the number of coins and coin values.
 Then it should display the best set of coins and max value.

sample input
6
5 1 2 10 6 2

output 
Best Set: 1 4 6 
Max value: 17


*******************************************************************************/

#include <iostream>
#include <string.h>
#include <bits/stdc++.h>

using namespace std;

int flag=0;
/* finMax - returns the maximum value*/
int findMax(int x, int y)
{
    if(x>=y)
    {
       flag=1;
       return x;
    }
    else
    {
        flag=0;
        return y;
    }
}

int main()
{
    int num_of_coins, *coins=NULL, *coins_func=NULL;
    cin>>num_of_coins;
    if(num_of_coins >0)
    {
        coins = new int [num_of_coins];
        coins_func = new int [num_of_coins+1];
    }
    else
    {
        cout<<"invalid input" << endl;
        return 0;
    }
    if ((coins == nullptr) || (coins_func == nullptr))
    {
        cout << "Error: memory could not be allocated";
        return 0;
    }
    else
    {
        for(int i=0;i<num_of_coins;i++)
        {
            cin>>coins[i];
        }
        
        int bestSet [num_of_coins+1][2];

        coins_func[0] = 0;
        bestSet[0][0] = 0;
        bestSet[0][1] = 0;
        
        coins_func[1] = coins[0];
        bestSet[1][0] = 1;
        bestSet[1][1] = 0;

        for(int i=2, j=0; i<=num_of_coins ; i++)
        {
            coins_func[i]= findMax((coins[i-1]+coins_func[i-2]), coins_func[i-1]);
            if(flag == 1 )
            {
                if (i-2)
                {
                    bestSet[i][0] = i;
                    bestSet[i][1] = i-2;
                }
                else
                    bestSet[i][0] = i;
                flag=0;
            }
            else
            {
                bestSet[i][0] = 0;
                bestSet[i][1] = i-1;
            }
        }

       int result[num_of_coins], bestSet_len=0;
       int func_index = num_of_coins;
       for (int i=0,j=0; i<=num_of_coins;i++)
       {
           if(bestSet[func_index][0] == 0)
           {
               func_index = bestSet[func_index][1];
           }
           else
           {
               if(bestSet[func_index][0])
               {
                    result[j] = bestSet[func_index][0];
                    j++;
               }
               func_index = bestSet[func_index][1];
           }
           bestSet_len=j;
       } 
       cout << "Best set:";
       for (int i=bestSet_len-1; i>=0; i--)
       {
           cout << result[i] << '\t';
       }

        cout << endl <<"Max value:"<<coins_func[num_of_coins];
        
    }
    delete[] coins, coins_func;
    return 0;
}
