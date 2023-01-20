#include <iostream>  
using namespace std;  

int main()  
{  
int b[10][10],m,n,i,j,k;    
int a[10];
cout<<"enter the number of row = ";    
cin>>m;    
cout<<"enter the number of column = ";    
cin>>n;    
cout<<"enter the sparse matrix element =\n";    
int c[sizeof(int (n))]= { 0 };
for(i=0;i<m;i++)    
{    
    for(j=0;j<n;j++)    
        {    
            cin>>b[i][j];  
        }    
}    
cout << "Enter vector elements = \n";
for(i=0; i<n;i++){
    cin>>a[i];
}

//printing matrix and vector
cout<<"\n Vector A \n";
   //vector 
   for(i=0;i<m;i++){
       cout<<"\n"<<a[i];
   }
   cout<<"\n Matrix B \n";
   //matrix 3*3
   for(i=0;i<m;i++){
       for(j=0;j<n;j++){
           cout<<" "<<b[i][j];
       }
       cout<<"\n";
   }
   //now we multiply a and b
   //no of columns of matrix = no.of rows of vector
   //c[n] = {0};
   for(i=0;i<m;i++){
       for(j=0;j<n;j++){
           c[i]=c[i]+(a[i]* b[i][j]);
       }
   }
cout<<"\n Vector C\n";
for(i=0;i<m;i++){
    cout<<"\n" <<c[i];
}
cout<<"\n";
return 0;
}