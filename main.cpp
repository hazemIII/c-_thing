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

int n = 1000;

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

void p (matrix <double>& vec , matrix<double>& mat , matrix<double>& res)
{
    cout << vec.size2() << "   "<<mat.size1() <<endl;
    for (int i = 0; i < vec.size2();i++){
        for (int j = 0 ; j < mat.size1() ; j++){
        cout << vec(0,i) << "   "<< mat(j,i)<<"  "<<endl;
            res(0,i) =res(0,i)+ (vec(0,i) * mat(j,i));
            cout<<vec(0,i) * mat(j,i)<<endl;

        }
    }

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
    //int n =10;
    float sx = (2* M_PI)/n;
   /* // create vector F :   F = -sinx
    std::vector <double> F(10,0);    // vector with 10 elements all = 0
    F[10] = 0;           // the last element = 2* pi
    for(int i = 1 ; i < 10 ; i++)
        F[i] = -1* sin(sx * i) ; // fill the F vector

    // Create Uex vector
    std::vector<double> Uex(10,0);
    Uex[10] = 0;
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
    //print(MatrixA);*/
    matrix<double> A(n,n) , Ainv(n,n);
    //fill matrix A
    for (int i = 0; i < A.size1 (); ++ i)
        for (int j = 0; j < A.size2 (); ++ j)
            A(i,j) = 0 ;                         // initialize
            /*A (i, j) = MatrixA[j + 100* i];*/
    for (int i = 0 ; i <(A.size1()); i++)
        {
            A(i,i) = -2 ;
        }
    for(int row = 0 ; row < (A.size1()-1) ; row ++)
        A(row, row+1) = 1;
    for(int row = 1 ; row < (A.size1()) ; row ++)
        A(row, row-1) = 1;
       InvertMatrix(A,Ainv);
    //cout << Ainv<<endl;
    matrix<double> f(1,n);
    f(0,0) = 0.0;
    f(0,n-1) =0;
    for (int i = 1 ; i< n-1 ; i++){
        f(0,i) = -1 * sin(sx*i);}

    matrix<double> U(1,n);
    U = prod(f,Ainv);
    //cout << f << endl;
    cout<<U<<endl;
    return 0;
}
