#include <iostream>  
using namespace std;  

int main()  
{  
int a[10][10],m,n,i,j,k=0;    
int nnz = 0;
cout<<"enter the number of row = ";    
cin>>m;    
cout<<"enter the number of column = ";    
cin>>n;    
cout<<"enter the sparse matrix element =\n";    
for(i=0;i<m;i++)    
{    
    for(j=0;j<n;j++)    
        {    
            cin>>a[i][j];  
        }    
} 
for(i=0; i<m; i++ ){
    for(j=0; j<n; j++){
        if(a[i][j]!=0)
        {
            nnz++;
        }
    }
}  
cout << "non zero elements: " << nnz << endl;
int b[3][nnz];
for(i=0; i<m; i++ ){
    for(j=0; j<n; j++){
        if(a[i][j]!=0)
        {
            b[0][k]=i;
            b[1][k]=j;
            b[2][k]= a[i][j];
            k++;
        }
    }
}  
cout<< "COO Representation"<<endl;
for(i=0; i<3; i++){
    for(j=0; j<nnz; j++){
        cout<< b[i][j] << " ";
    }
    cout<< endl;
}
cout << "enter vector elements" << endl;
int p[n];
for(i=0; i<n; i++){
    cin>> p[i];
}
//print vector elements
for(i=0; i<n; i++){
    cout<< p[i] <<" ";
}
cout<< endl;
int y[n];

return 0;
}