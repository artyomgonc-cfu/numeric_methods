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

	for (int k = 1; k <= 20; k++) {
		cout << setw(2) << k << '|' << scientific << setw(15) << l(k) << '|'
			<< setw(15) << l(k) * da << '|' << setw(15) << double(k) + l(k) * da << endl;
	}

	return 0;
}
