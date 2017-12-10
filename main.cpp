#include <iostream>
#include <vector>
#include <set>

using namespace std;

void display(vector<int> vect){
    for (vector<int>::iterator it=vect.begin(); it != vect.end(); it++){
        *it = (*it) + 1;
        cout<< *it <<' ';
    }
    cout<<endl;
}

int main() {
    cout << "Hello, World!" << endl;
    vector<int> test(10);
    display(test);
    vector<int> test2(test.begin(), test.begin()+5);
    display(test2);
    for (vector<int>::iterator it=test2.begin(); it != test2.end(); it++){
        *it = (*it) + 1;
    }
    display(test);
    display(test2);
    set<int> testSet;
    testSet.insert(10);
    set<int>::iterator it =  testSet.find(10);
    cout<<*it<<endl;
    return 0;
}