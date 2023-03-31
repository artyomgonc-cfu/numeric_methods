#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;



int main() {

    double y = -1.25;
    double new_y;
    double diff;
    do {
        new_y = -sqrt(y + 6) / sqrt(2);
        diff = abs(y - new_y);
        y = new_y;
        cout << y << ' ' << diff << endl;
    } while (diff > 0.001);

    //cout << binary(-2, -0.5, *ff, 0.0005);

    return 0;
}
