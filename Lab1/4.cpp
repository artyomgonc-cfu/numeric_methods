#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <cmath>
#include <string>
using namespace std;

double l(int i) {
	double den = 1;
	for (int j = 1; j <= 20; j++)
		if (j != i)
			den *= i - j;
	return pow(i, 19) / den;
}

int main() {

	double da = 1e-7;

	cout << setw(2) << "k" << '|' << setw(15) << "l(k)" << '|'
		<< setw(15) << "dx(k)" << '|' << setw(15) << "x(k)" << endl;
	for (int k = 1; k <= 20; k++) {
		cout << setw(2) << k << '|' << scientific << setw(15) << l(k) << '|'
			<< setw(15) << l(k) * da << '|' << setw(15) << double(k) + l(k) * da << endl;
	}

	int counter = -8;
	for (da = da / 10; true; da /= 10, counter--) {
		bool ok = true;
		for (int k = 1; k <= 20; k++) {
			double fault = abs(l(k) * da);
			if ((k < 10 && fault > 5e-6) || (k >= 10 && fault > 5e-5)) {
				ok = false;
				break;
			}
		}
		if (ok) {
			cout << "Allowed da = " << setprecision(0) << da << endl;
			break;
		}
	}

	return 0;
}
