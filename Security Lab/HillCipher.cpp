#include <bits/stdc++.h>
using namespace std;

#define N 100

int m;
int K[100][100];
int IK[100][100];



// Function to get cofactor of A[p][q] in temp[][]. n is current 
// dimension of A[][] 
void getCofactor(int A[N][N], int temp[N][N], int p, int q, int n) 
{ 
    int i = 0, j = 0; 
  
    // Looping for each element of the matrix 
    for (int row = 0; row < n; row++) 
    { 
        for (int col = 0; col < n; col++) 
        { 
            //  Copying into temporary matrix only those element 
            //  which are not in given row and column 
            if (row != p && col != q) 
            { 
                temp[i][j++] = A[row][col]; 
  
                // Row is filled, so increase row index and 
                // reset col index 
                if (j == n - 1) 
                { 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 
} 
  
/* Recursive function for finding determinant of matrix. 
   n is current dimension of A[][]. */
int determinant(int A[N][N], int n) 
{ 
    int D = 0; // Initialize result 
  
    //  Base case : if matrix contains single element 
    if (n == 1) 
        return A[0][0]; 
  
    int temp[N][N]; // To store cofactors 
  
    int sign = 1;  // To store sign multiplier 
  
     // Iterate for each element of first row 
    for (int f = 0; f < n; f++) 
    { 
        // Getting Cofactor of A[0][f] 
        getCofactor(A, temp, 0, f, n); 
        D += sign * A[0][f] * determinant(temp, n - 1); 
  
        // terms are to be added with alternate sign 
        sign = -sign; 
    } 
  
    return D; 
} 
  
// Function to get adjoint of A[N][N] in adj[N][N]. 
void adjoint(int A[N][N],int adj[N][N]) 
{ 
    if (m == 1) 
    { 
        adj[0][0] = 1; 
        return; 
    } 
  
    // temp is used to store cofactors of A[][] 
    int sign = 1, temp[N][N]; 
  
    for (int i=0; i<m; i++) 
    { 
        for (int j=0; j<m; j++) 
        { 
            // Get cofactor of A[i][j] 
            getCofactor(A, temp, i, j, m); 
  
            // sign of adj[j][i] positive if sum of row 
            // and column indexes is even. 
            sign = ((i+j)%2==0)? 1: -1; 
  
            // Interchanging rows and columns to get the 
            // transpose of the cofactor matrix 
            adj[j][i] = (sign)*(determinant(temp, m-1)); 
        } 
    } 
} 

int GCD_Extended(int a,int b,int *x,int *y)
{
	if(a==0)
	{
		*x=0;
		*y=1;
		return b;
	}
	int x1,y1;
	int gcd=GCD_Extended(b%a,a,&x1,&y1);
	*x=y1-(b/a)*x1;
	*y=x1;
	return gcd;
}

void findInverseOfKeyMatrix()
{
	int inv[N][N];
	adjoint(K,inv);
	int D = determinant(K,m)%26;
	if(D<0) D+=26;
	int DI=0; int y;
	int gcd = GCD_Extended(D,26,&DI,&y);
	//Multiplying each element of adjoint transpose with modulo inverse of determinant
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<m;j++)
		{
			inv[i][j]=(inv[i][j] * DI)%26;
			if(inv[i][j]<0) inv[i][j]+=26;
			IK[i][j]=inv[i][j];
		}
		cout<<endl;
	}

}

void multiply(int K[N][N], int a[],int res[])
{
	
	for(int i=0;i<m;i++)
	{
		int sum=0;
		for(int k=0;k<m;k++)
		{
			sum+=K[i][k]*a[k];
		}
		res[i]=sum%26;
	}
}

string encrypt(string plain_text)
{
	string cipher_text="";
	int blocks = plain_text.length()/m;
	for(int b=0;b<blocks;b++)
	{
		int a[m]={ plain_text[b*m]-'A' , plain_text[b*m+1]-'A' , plain_text[b*m+2] - 'A' };
		int res[m]; memset(res,0,sizeof res);
		multiply(K,a,res);
		cipher_text+=res[0]+'A'; cipher_text+=res[1]+'A'; cipher_text+=res[2]+'A';
	}
	return cipher_text;
}

string decrypt(string cipher_text)
{
	string plain_text="";
	int blocks = cipher_text.length()/m;
	for(int b=0;b<blocks;b++)
	{
		int a[m]={ cipher_text[b*m]-'A' , cipher_text[b*m+1]-'A' , cipher_text[b*m+2] - 'A' };
		int res[m]={0};
		multiply(IK,a,res);
		plain_text+=res[0]+'A'; plain_text+=res[1]+'A'; plain_text+=res[2]+'A';
	}
	return plain_text;
}

int main(int argc, char const *argv[])
{
	string plain_text;
	cout<<"Enter the value of m : ";
	cin>>m;
	cout<<"Enter the key matrix "<<endl;
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<m;j++) cin>>K[i][j];
	}
	cout<<"Enter plain text : "; 
	cin>>plain_text;
	findInverseOfKeyMatrix();
	for(int i=0;i<plain_text.length();i++)
	{
		plain_text[i]=toupper(plain_text[i]);
	}
	string C = encrypt(plain_text);
	cout<<"cipher text = "<<C<<endl;
	return 0;
}

/*

3
17 17 5
21 18 21
2 2 19

paymoremoney

*/