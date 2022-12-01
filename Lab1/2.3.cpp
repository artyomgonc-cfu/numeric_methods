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

double calc_sin(double x) {

    double fact = 1;
    int counter = 1;

    double ans = x;
    double old_ans = 1000;
    double acc = accuracy();

    while (abs(ans-old_ans) > acc) {
        old_ans = ans;
        
        fact = fact * 2 * counter * (2 * counter -1);
        double loc_val = pow(x, 2*counter + 1) / (fact * (2 * counter + 1));
        if (counter % 2 == 1) loc_val = -loc_val;

        ans += loc_val;

        counter++;

        //cout << ans << endl;
    }

    return ans;
}

double calc_cos(double x) {

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
    cout << "Cosinus\n";
    cout << scientific;
    cout << setw(5) << "x" << '|' << setw(wid) << "calculated" << '|' << setw(wid) << "cos(x)" << '|'
        << setw(wid) << "abs fault" << "| rel fault" << endl;

    vector<int> test_vals{0};
    for (int i = 5; i <= 50; i+=5) {
        test_vals.push_back(i);
    }
    sort(test_vals.begin(), test_vals.end());

    for (int i : test_vals) {
        cout << setw(5) << i << '|' << setw(wid) << calc_cos(i) << '|' << setw(wid) << cos(i) << '|'
        << setw(wid) << abs(calc_cos(i) - cos(i)) << '|' << abs(calc_cos(i) - cos(i))/abs(cos(i)) << endl;
        cout << scientific;
    }

    cout << endl << "sinus\n";
    cout << setw(5) << "x" << '|' << setw(wid) << "calculated" << '|' << setw(wid) << "sin(x)" << '|'
        << setw(wid) << "abs fault" << "| rel fault" << endl;
    for (int i : test_vals) {
        cout << setw(5) << i << '|' << setw(wid) << calc_sin(i) << '|' << setw(wid) << sin(i) << '|'
        << setw(wid) << abs(calc_sin(i) - sin(i)) << '|' << abs(calc_sin(i) - sin(i))/abs(sin(i)) << endl;
        cout << scientific;
    }

    cout << "\nCorrected cosinus\n";
    cout << setw(5) << "x" << '|' << setw(wid) << "calculated" << '|' << setw(wid) << "cos(x)" << '|'
        << setw(wid) << "abs fault" << "| rel fault" << endl;

    for (int j : test_vals) {
        int factor = double(j) / (2*acos(-1));

        double i = double(j) - (2*acos(-1))*factor;
        cout << setw(5) << j << '|' << setw(wid) << calc_cos(i) << '|' << setw(wid) << cos(i) << '|'
        << setw(wid) << abs(calc_cos(i) - cos(i)) << '|' << abs(calc_cos(i) - cos(i))/abs(cos(i)) << endl;
    }

    cout << "\nCorrected sinus\n";
    cout << setw(5) << "x" << '|' << setw(wid) << "calculated" << '|' << setw(wid) << "sin(x)" << '|'
        << setw(wid) << "abs fault" << "| rel fault" << endl;

    for (int j : test_vals) {
        int factor = double(j) / (2*acos(-1));

        double i = double(j) - (2*acos(-1))*factor;
        cout << setw(5) << j << '|' << setw(wid) << calc_sin(i) << '|' << setw(wid) << sin(i) << '|'
        << setw(wid) << abs(calc_sin(i) - sin(i)) << '|' << abs(calc_sin(i) - sin(i))/abs(sin(i)) << endl;
    }

    return 0;
}
