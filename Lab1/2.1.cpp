#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

double accuracy() {
    double e = 1.0;
    double old;
    while (1.0+e > 1.0) {
        old = e;
        e = e/2.0;
    }
    return old;
}

double calc_exp(int x) {
    double powv = 1;
    double fact = 1;
    int counter = 1;

    double ans = 0;
    double old_ans = 1000;
    double acc = accuracy();

    while (abs(ans-old_ans) > acc) {
        old_ans = ans;
        ans += powv/fact;
        powv = powv*x;
        fact = fact*counter;
        counter++;

        //cout << ans << endl;
    }

    return ans;
}

int main() {
    cout << scientific;
    cout << setw(5) << "x" << '|' << setw(12) << "calculated" << '|' << setw(12) << "exp(x)" << '|'
        << setw(12) << "abs fault" << "| rel fault" << endl;

    vector<int> test_vals{0};
    for (int i = 10; i <= 50; i+=10) {
        test_vals.push_back(i);
        test_vals.push_back(-i);
    }
    sort(test_vals.begin(), test_vals.end());


    for (int i : test_vals) {
        cout << setw(5) << i << '|' << setw(12) << calc_exp(i) << '|' << setw(12) << exp(i) << '|'
        << setw(12) << abs(calc_exp(i) - exp(i)) << '|' << abs(calc_exp(i) - exp(i))/exp(i) << endl;
    }

    return 0;
}
