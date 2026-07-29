#include<iostream>
using namespace std;

int add(int a, int b){
    return a+b;
  
}
    double adddoub(double a, double b){
        return a+b;
      
    }

int main(){
int num1=add(1,2);
double num2=adddoub(1.5,3.45);

cout<<num1<<endl;
cout<<num2<<endl;

// funtion overloading majurly stands for ki add krre ap 2 intgers ko caliing again and again 
// ek baar int ka sum kiya and second time double decimal ka sum kiya 
}
