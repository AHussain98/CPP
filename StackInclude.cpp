#include<iostream>
using namespace std;
#include<stack>   //we can also access stack functionality using the include stack 

int main(){
    stack<int> s1;
    s1.push(30);
    s1.push(40);
    cout << s1.top() << endl;
    cout << s1.size() << endl;
    cout << s1.empty() << endl;
    
    
}