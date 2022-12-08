#include <iostream>
using namespace std;

int main() {
    double e = 1.0;
    double old;
    while (1.0+e > 1.0) {
        old = e;
        e = e/2.0;
    }
    cout << old << endl;
    
    float e1 = 1.0;
    float old1;
    while (1.0+e1 > 1.0) {
        old1 = e1;
        e1 = e1/2.0;
    }
    cout << old1 << endl;

    return 0;
}
