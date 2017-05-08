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







//#include <iostream>
//#include <math.h>
//#include <vector>
//#include <stdio.h>
////#include ><array>
//
//using namespace std;
//
//int main()
//{
//    int m = 10;  // nummber of points in interval
//    double h = 2*3.1415/(m+1);
//    double MatrixA[m*m], MatrixAn[m*m];
//	double x[m], F[m], U[m];
//	int a=0, b=0;
////    array<double , 100> MatrixA = {0};
//
//	for (int i=0; i<m*m; i++){
//	 MatrixA[i]=MatrixAn[i]=0;
//	}
//    for (int i = 0 ; i < m ;i++ ){
//        MatrixA[i*(m+1)] = -2;			//b		i*(m+1)
//    }
//    for (int i = 0 ; i < m ;i++ ){
//        MatrixA[(i*(m+1))+1] = 1;		//c		i*(m+1)+1
//    }
//    for (int i = 1 ; i < m ;i++ ){
//        MatrixA[(i*(m+1))-1] = 1;       //a		i*(m+1)-1
//    }
//  	for (int j= 0 ; j<m ; j++) //rows
//        {
//            for(int i = 0 ; i<m; i++) //cols
//            {
//                cout<<MatrixA[(j*m + i)]<<" ";
//            }
//            cout<<endl;
//        }
//
//	// DEFINE HERE X
//	for (int k=0; k<m; k++){
//		x[k]=(k+1)*h;
//	}
//	//cout<<sizeof(x)/sizeof(x[1])<<endl;		CHECKS LENGTH OF X ARRAY
//	cout<<"X set for F vector is equal to:"<<endl;
//	for (int k=0; k<m; k++){
//		printf ("%8.3f", x[k]);
//	}
//	cout<<endl;
//
//	// DEFINE HERE F
//	F[0] = sin(x[0]) - a/pow(h,2);
//	F[m-1] = sin(x[m-1] - b/pow(h,2));    //F[of last element]...
//	for (int k=1; k<m-1; k++){
//		F[k]=sin(x[k]);
//	}
//	cout<<"F vector is equal to:"<<endl;
//		for (int k=0; k<m; k++){
//		printf ("%8.4f", F[k]);
//	}
//	printf("\n\n");
//
//	// MAIN ALGORITHM
//	// STAGE I
//	F[0]=F[0]/MatrixA[0];
//	MatrixAn[0]=1;
//	MatrixAn[1]=MatrixA[1]/MatrixA[0];
//	for (int i=1; i<(m-1); i++){
//		int ai=i*(m+1)-1;
//		int bi=i*(m+1);
//		int ci=i*(m+1)+1;
//
//		MatrixAn[ci]=MatrixA[ci]/(MatrixA[bi]-MatrixA[ai]*MatrixAn[(i-1)*(m+1)+1]);
//		F[i]=(F[i]-MatrixA[ai]*F[i-1])/(MatrixA[bi]-MatrixA[ai]*MatrixAn[(i-1)*(m+1)+1]);
//		MatrixAn[bi]=1;
//	}
//	MatrixAn[m*m-1]=1;
//	F[m-1]=(F[m-1]-MatrixA[m*m-2]*F[m-2])/(MatrixA[m*m-1]-MatrixA[m*m-2]*MatrixAn[m*m-m-1]);
//
//
//	printf ("Connverted matrix A is equal to: \n");
//	for (int j= 0 ; j<m ; j++){
//		for(int i = 0 ; i<m; i++){
//			printf("%5.3f	 ",MatrixAn[(j*m + i)]);
//        }
//        cout<<endl<<endl;
//    }
//    printf ("Converted F vector is equal to: \n");
//    for (int k=0; k<m; k++){
//		printf ("%8.4f", F[k]);
//	}
//	printf("\n");
//
//	//STAGE II
//	U[m-1]=F[m-1];
//	for (int j=m-2 ; j>=0; j--){
//		U[j]=F[j]-MatrixAn[j*(m+1)+1]*U[j+1];
//	}
//	printf ("U vector is equal to:\n");
//	for (int k=0; k<m; k++){
//		printf ("%8.4f", U[k]);
//	}
//	printf("\n");
//    return 0;
//}
