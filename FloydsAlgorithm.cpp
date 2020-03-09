/******************************************************************************
Write a program that implements Floyd's algorithm to display all pair shortest paths.

sample input

4 
0 -1 3 -1
2 0 -1 -1
-1 7 0 1
6 -1 -1 0

4 indicates there are four vertices in the input graph.
The following 4 lines present distance between all pairs.
the value -1 indicates the infinity.

Output

0 10 3 4
2 0 5 6
7 7 0 1
6 16 9 0

*******************************************************************************/

#include <iostream>

using namespace std;

void applyFloydAlgorithm(int num_of_nodes, int **d_matrix)
{
   int temp[num_of_nodes][num_of_nodes];
   int k=0;
    do
    {
       for (int i=0; i<num_of_nodes; i++)
       {
           for(int j=0;j<num_of_nodes; j++)
           {
               if((d_matrix[i][j]!=-1) && (d_matrix[i][k]!=-1) && (d_matrix[k][j]!=-1))
               {
                  temp[i][j] = min(d_matrix[i][j], (d_matrix[i][k]+d_matrix[k][j])); 
               }
               else if((d_matrix[i][j] ==-1) && (d_matrix[i][k]!=-1) && (d_matrix[k][j]!=-1))
               {
                  temp[i][j] = d_matrix[i][k] + d_matrix[k][j];
               }
               else if((d_matrix[i][j] !=-1) && ((d_matrix[i][k]==-1) || (d_matrix[k][j]==-1)))
               {
                   temp[i][j] = d_matrix[i][j];
               }
               else
               {
                   temp[i][j] = -1;
               }
               if(k==(num_of_nodes-1))
                    cout << temp[i][j] << " ";
           }
           if(k==(num_of_nodes-1))
                cout << endl;
           
       }
       for (int i=0;i<num_of_nodes; i++)
       {
           for(int j=0;j<num_of_nodes; j++)
           {
               d_matrix[i][j] = temp[i][j];
           }
       }
       k++;
   
    }while(k<num_of_nodes);
}

int main()
{
    int num_of_nodes, **d_matrix = NULL;
    
    cin >> num_of_nodes;
    if(num_of_nodes <=0)
    {
        cout << "invalid input" << endl;
        return 0;
    }
    
    d_matrix = new int *[num_of_nodes];
    for (int i=0; i<num_of_nodes; ++i)
        d_matrix[i] = new int[num_of_nodes];
        
    for (int i=0;i<num_of_nodes; i++)
    {
        for(int j=0;j<num_of_nodes;j++)
        {
            cin>>d_matrix[i][j];
        }
    }
    
    applyFloydAlgorithm(num_of_nodes,d_matrix);


    return 0;
}

