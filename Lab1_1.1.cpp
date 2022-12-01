#include <iostream>
using namespace std;

int main() {
    double e = 1.0;
    double old;
    while (e > 0.0) {
        old = e;
        e = e/2.0;
    }
    cout << old << endl;

    return 0;
}
