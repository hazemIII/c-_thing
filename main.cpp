#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <array>
using namespace std;

int n = 10;

void print (vector <double> MatrixA)
{

    //print function
    //int n = 10;
    for (int j= 0 ; j<n ; j++) //rows
    {
        for(int i = 0 ; i < n; i++) //cols
        {
            cout<<MatrixA[(j*n+ i)]<<" ";
        }
        cout<<endl;
    }
    cout << endl;
}

int main()
{
    int row = 100;
    //int n =10;
    float sx = (2* M_PI)/n;
    // create vector F :
    vector <double> F(10,0);    // vector with 10 elements all = 0
    F[10] = 2 * M_PI;           // the last element = 2* pi
    for(int i = 1 ; i < 10 ; i++)
        F[i] = F[i-1] + sx ; // fill the Uex vector

    // Create Uex vector
    vector<double> Uex(10,0);
    Uex[10] = 2 * M_PI;
    for (int i = 1 ; i< 10 ; i++)
    Uex[i] = sin(sx * i);                // I have problem here ... What is X ?!

    for(int i = 0 ; i <= 10 ; i++){
    cout << F[i] << "   "<< Uex[i];
    cout <<endl;}



    vector<double> MatrixA(100 ,0);
    for (int i = 0 ; i < n ; i++ )
    {
        MatrixA[i*(n+1)] = -2;
    }
    for (int i = 0 ; i < n ; i++ )
    {
        MatrixA[(i*(n+1))+1] = 1;
    }
    for (int i = 1 ; i < n ; i++ )
    {
        MatrixA[(i*(n+1))-1] = 1;
    }
    //print(MatrixA);
    return 0;
}
