#include <iostream>
#include <cmath>
#include <vector>
#include <array>
using namespace std;

int main()
{
    int row = 100;
    int n =10;
    array<double , 100> MatrixA = {0};
    for (int i = 0 ; i < n ;i++ ){
        MatrixA[i*(n+1)] = -2;
    }
    for (int i = 0 ; i < n ;i++ ){
        MatrixA[(i*(n+1))+1] = 1;
    }
     for (int i = 1 ; i < n ;i++ ){
        MatrixA[(i*(n+1))-1] = 1;
    }
   for (int j= 0 ; j<n ; j++) //rows
        {
            for(int i = 0 ; i < n; i++) //cols
            {
                cout<<MatrixA[(j*n+ i)]<<" ";
            }
            cout<<endl;
        }
cout << endl;
    return 0;
}
