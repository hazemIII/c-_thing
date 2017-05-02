#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <array>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
using namespace boost::numeric::ublas;
using namespace std;

int n = 10;

 /* Matrix inversion routine.
 Uses lu_factorize and lu_substitute in uBLAS to invert a matrix */
template<class T>
bool InvertMatrix(const matrix<T>& input, matrix<T>& inverse)
{
	typedef permutation_matrix<std::size_t> pmatrix;

	// create a working copy of the input
	matrix<T> A(input);

	// create a permutation matrix for the LU-factorization
	pmatrix pm(A.size1());

	// perform LU-factorization
	int res = lu_factorize(A, pm);
	if (res != 0)
		return false;

	// create identity matrix of "inverse"
	inverse.assign(identity_matrix<T> (A.size1()));

	// backsubstitute to get the inverse
	lu_substitute(A, pm, inverse);

	return true;
}

void print (std::vector <double> MatrixA)
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
    // create vector F :   F = -sinx
    std::vector <double> F(10,0);    // vector with 10 elements all = 0
    F[10] = 2 * M_PI;           // the last element = 2* pi
    for(int i = 1 ; i < 10 ; i++)
        F[i] = -1* sin(sx * i) ; // fill the F vector

    // Create Uex vector
    std::vector<double> Uex(10,0);
    Uex[10] = 2 * M_PI;
    for (int i = 0 ; i<= 10 ; i++)
    Uex[i] = sin(sx * i);// fill the Uex vector




    std::vector<double> MatrixA(100 ,0);
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
    matrix<double> A(10,10) , Ainv(10,10);
    for (int i = 0; i < A.size1 (); ++ i)
        for (int j = 0; j < A.size2 (); ++ j)
            A (i, j) = MatrixA[j + 10* i];
    //cout << A<<endl;
    InvertMatrix(A,Ainv);
    //cout << Ainv<<endl;
    matrix<double> f(1,10);
    f(0,0) = 0.0;
    f(0,9) = 2 * M_PI;
    for (int i = 1 ; i< 10 ; i++){
        f(0,i) = -1 * sin(sx*i);}

    matrix<double> U(1,10);
    U = prod(f,Ainv);

    cout <<U;
    return 0;
}
