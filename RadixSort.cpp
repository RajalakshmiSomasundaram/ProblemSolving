/******************************************************************************
Radix Sort 

Sample input

5
77 23 17 5 12

Output

12 23 5 17 7
5 12 17 23 77


*******************************************************************************/

#include <iostream>
#include <cmath>
#include<string>

using namespace std;

#define MAX 100

void swap(int *x, int *y) 
{ 
    int temp = *x; 
    *x = *y; 
    *y = temp; 
}

int findDigit(int num,int n)
{
    int divider=pow(10,(n-1));
    if(n==1)
        return num%10;
    else
    {
        int digit = (num/divider)%10;
        return digit;
    }
}

int findLen(int num)
{
    int count=0;
    do {
        count ++;
        num = num/10;
    }while(num);
    return count;
}

int main()
{
    int  input[MAX];
    int num_of_input,maxLen=0;
   
    
    cin >> num_of_input; 
    
    if ( num_of_input <=0  || num_of_input >= MAX)
    {
        cout << "Invalid range!";
    }
    else
    {
        for ( int i=0; i<num_of_input; i++)
        {
            
            cin>>input[i];
            int len=findLen(input[i]);
            if(maxLen<=len)
            {
                maxLen=len;
            }
        }

        int num[num_of_input][maxLen];
        for (int i=0; i<num_of_input; i++)
        {
            int len=findLen(input[i]);
            if (len < maxLen)
            {
              int pad_count=maxLen-len;
              int k=0;
              for (;k<pad_count;k++)
              {
                  num[i][k]=0;
              }
              for (int l=maxLen-1,m=1;l>=k,m<=len;l--,m++)
              { 
                  num[i][l]=findDigit(input[i],m);
              }
            }
            else
            {
                for(int l=maxLen-1,m=1;l>=0,m<=len;l--,m++)
                {
                    num[i][l] = findDigit(input[i],m);
                }
            }
        }
            int i, j; 
            bool swapped;
            int le=maxLen-1;
            while(le>=0)
            {
                for (i = 0; i < num_of_input-1; i++) 
                { 
                  swapped = false; 
                  for (j = 0; j < num_of_input-i-1; j++) 
                    { 
                        if (num[j][le] > num[j+1][le])
                        { 
                          for(int k=0;k<maxLen;k++)
                          {
                            swap(&num[j][k], &num[j+1][k]);
                          }
                          swapped = true; 
                        } 
                    } 
          
                    // IF no two elements were swapped by inner loop, then break 
                    if (swapped == false) 
                     break; 
                }
                std::string str[num_of_input];
                for (int i=0; i<num_of_input; i++)
                {
                  for(int j=0; j<maxLen; j++)
                  {
                     str[i].append(std::to_string(num[i][j]));
                  }
                  std::cout << std::stoi(str[i]) << '\t';
                  
                }
                cout << endl;
                le--;
            }
    }
    return 0;
}



