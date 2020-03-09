/******************************************************************************
Write a Knapsack problem using the dynamic programming technique.
The Program should read a weight and a value of each item from a user
and determinse the best subset.

The number of items and knapsack capacity are less than or equal to 15

sample input

4 
5
2 12
1 10
3 20
2 15

4 indicates 4 items for the knapsack problem
5 indicates the knapsack's capacity.

item 1 has capacity 2 and the value 12
item 2 has capacity 1 and the value 10 
so on

Output

Final step: 0 10 15 25 30 37
Max value: 7
Items: 1 2 4 

*******************************************************************************/

#include <iostream>

using namespace std;

void findProfit(int num_of_items, int knapsack_capacity,int *weight,int *profit)
{
    int temp[num_of_items+1][knapsack_capacity+1];
    
    for(int i=0; i<=num_of_items; i++)
    {
        temp[i][0] = 0;
    }
    for(int i=0; i<=knapsack_capacity; i++)
    {
        temp[0][i] = 0;
    }
    
    for (int i=1; i<=num_of_items; i++)
    {
        for(int j=1; j<=knapsack_capacity; j++)
        {
            int j_temp = j-weight[i-1];
            if(j_temp >=0)
            {
                temp[i][j] = max(temp[i-1][j], (temp[i-1][j_temp]+profit[i-1]));
            }
            else
            {
                temp[i][j] = temp[i-1][j];
            }
        }
    }
    
    //display
    cout << "Final step:";
    for(int j=0; j<=knapsack_capacity; j++)
    {
        cout << temp[num_of_items][j] <<'\t';
    } 
    cout << endl << "Max value:" << temp[num_of_items][knapsack_capacity]<< endl; 
    cout << "Items:";
    string result[num_of_items];
    int k=0;
    int findValue=temp[num_of_items][knapsack_capacity];
    for(int i=1; i<=num_of_items; i++)
    {
        for (int j=1; j<=knapsack_capacity; j++)
        {
            if(temp[i][j] == findValue)
            {
                result[k] += to_string(i);
                k++;
                findValue = findValue-profit[i-1];
                if(findValue!=0)
                    i=0;
                break;
            }
            
        }
        if(findValue==0)
            break;
        
    }
    if(temp[num_of_items][knapsack_capacity] !=0)
    {
        for(int i=k-1; i>=0; i--)
        {
            cout << result[i] << " ";
        }
    }
    
}


int main()
{
    int num_of_items, knapsack_capacity, *weight =NULL, *profit = NULL;
    
    cin>>num_of_items;
    cin>>knapsack_capacity;
    
    if((num_of_items>=15) && (knapsack_capacity>=15))
    {
        cout << "Invalid input";
        return 0;
    }
    
    weight = new int [num_of_items];
    profit = new int [num_of_items];
    if ((weight!=NULL) && (profit != NULL))
    {
        for (int i=0; i<num_of_items;i++)
        {
            cin >> weight[i];
            cin >> profit[i];
        }
    }
    else
    {
        cout << "memory allocation issue";
        return 0;
    }
    
    
    findProfit(num_of_items, knapsack_capacity, weight, profit);

    delete[] weight;
    delete[] profit;
    

    return 0;
}

