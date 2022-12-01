#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
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
    bool minus = (x < 0);
    x = abs(x);

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

    if (minus) ans = double(1) / ans;

    return ans;
}

int main() {
    cout << scientific;
    cout << setw(5) << "x" << '|' << setw(12) << "calculated" << '|' << setw(12) << "exp(x)" << '|'
        << setw(12) << "fault" << "|fault (%)" << endl;

    vector<int> test_vals{-50, -25, -10, 0, 10, 25, 50};
    for (int i : test_vals) {
        cout << setw(5) << i << '|' << setw(12) << calc_exp(i) << '|' << setw(12) << exp(i) << '|'
        << setw(12) << abs(calc_exp(i) - exp(i)) << '|' << fixed << abs(calc_exp(i) - exp(i))/exp(i)*100 << "%" << endl;
        cout << scientific;
    }

    return 0;
}
