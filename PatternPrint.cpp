#include<iostream>
using namespace std;
int main() {
    int n; // input by user usko kahhha tak chaiye patttern printing
    int row;
    int col;
    cout<<"ENTER THE LIMIT TO PRINT" << endl;
    cin>> n;

    // majour concept of looping is used here.
cout<<"pattern printing" << endl;
 for(row=0;row<n;row=row+1) {  // this loops tells konsi row chalegi pehle or kahha tak chalegi????
    
    for(col=0;col<row+1;col++) { // this looop tells how the pattern is being printed kese print karn ahia pattern 
        cout<<"* ";
         

    }
     cout<< endl;
}
  
 }



 // the Output of the following code is given  as follows:
//  *
// * *
// * * *
// * * * *
// * * * * *
// * * * * * *
// * * * * * * *
// * * * * * * * *
// * * * * * * * * * 
// * * * * * * * * * *
