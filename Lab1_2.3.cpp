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

double calc_cos(int x) {

    double powv = 1;
    double fact = 1;
    int counter = 1;

    double ans = 1;
    double old_ans = 1000;
    double acc = accuracy();

    while (abs(ans-old_ans) > acc) {
        old_ans = ans;
        
        fact = fact * 2 * counter * (2 * counter -1);
        double loc_val = pow(x, 2*counter) / fact;
        if (counter % 2 == 1) loc_val = -loc_val;

        ans += loc_val;

        counter++;

        //cout << ans << endl;
    }

    return ans;
}

int main() {
    int wid = 15;

    cout << scientific;
    cout << setw(5) << "x" << '|' << setw(wid) << "calculated" << '|' << setw(wid) << "cos(x)" << '|'
        << setw(wid) << "fault" << "|fault (%)" << endl;

    vector<int> test_vals{0};
    for (int i = 5; i <= 50; i+=5) {
        test_vals.push_back(i);
        test_vals.push_back(-i);
    }
    sort(test_vals.begin(), test_vals.end());

    for (int i : test_vals) {
        cout << setw(5) << i << '|' << setw(wid) << calc_cos(i) << '|' << setw(wid) << cos(i) << '|'
        << setw(wid) << abs(calc_cos(i) - cos(i)) << '|' << fixed << abs(calc_cos(i) - cos(i))/abs(cos(i))*100 << "%" << endl;
        cout << scientific;
    }

    return 0;
}
