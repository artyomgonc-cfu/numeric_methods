#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

double f(double x) {
	return cos(x)/(1.0+x);
}
double a = 0, b = acos(-1)/2;

double rect(int n) {
	double s = 0;
	double h = (b - a) / n;
	for (double x = a; x < b; x += h) {
		s += f(x + h / 2);
	}
	return s * h;
}

double trapeze(int n) {
	double s = 0;
	double h = (b - a) / n;
	for (double x = a + h; x < b - h / 2; x += h) {
		s += f(x);
	}
	return (s + (0.5 + f(b)) / 2) * h;
}

double simpson(int n) {
	double h = (b - a) / n;
	double s4 = 0;
	for (double x = a; x <= b - h / 2; x += h) {
		s4 += f(x + h / 2);
	}

	double s2 = 0;
	for (double x = a + h; x <= b - h / 2; x += h) {
		s2 += f(x);
	}

	return (0.5 + f(b) + 4.0 * s4 + 2.0 * s2) * h / 6;
}

void calc(double (*func)(int), const vector<int>& n, const string& label) {
	for (int nval : n) {
		cout << fixed << setprecision(8);
		cout << "|" << setw(9) << label << "|";
		cout << setw(4) << nval << "|";
		cout << setw(10) << (*func)(nval) << endl;
	}
	cout << endl;
}

double n_c_calc(const vector<vector<double>>& H, int n) {
	double ans = 0;

	for (double x = a, i = 0; x < b + 1e-7; x += (b - a) / n, i++)
		ans += H[n][i] * f(x);

	return (b-a)*ans;
}

void n_c() {
	vector<vector<double>> H(8);
	H[3] = vector<double>{ 1.0 / 8, 3.0 / 8, 3.0 / 8, 1.0 / 8 };
	H[4] = vector<double>{ 7.0/90, 32.0/90, 12.0/90, 32.0/90, 7.0/90 };
	H[5] = vector<double>{ 19.0/288, 25.0/96, 25.0/144, 25.0/144, 25.0/96, 19.0/288 };
	H[6] = vector<double>{ 41.0/840, 9.0/35, 9.0/280, 34.0/105, 9.0 / 280, 9.0 / 35, 41.0 / 840 };
	H[7] = vector<double>{ 751.0/17280, 3577.0/17280, 1323.0/17280, 2989.0/17280, 2989.0 / 17280, 1323.0 / 17280, 3577.0 / 17280, 751.0 / 17280 };

	vector<int> ns{ 3, 4, 5, 6, 7 };
	for (int nval : ns) {
		cout << fixed << setprecision(8);
		cout << "|" << setw(9) << "N-C" << "|";
		cout << setw(4) << nval << "|";
		cout << setw(10) << n_c_calc(H, nval) << endl;
	}
	cout << endl;
}

int main() {

	vector<int> n{ 10, 20, 50, 100 };

	cout << "|" << setw(9) << "Method" << "|";
	cout << setw(4) << "N" << "|";
	cout << setw(10) << "S" <<  endl << endl;

	cout << fixed << setprecision(8);
	cout << "|" << setw(9) << "True val" << "|";
	cout << setw(4) << "inf" << "|";
	cout << setw(10) << "0.67362109" << endl << endl;

	calc(&rect, n, "Rectangle");
	calc(&trapeze, n, "Trapezoid");
	calc(&simpson, n, "Simpson");

	n_c();

	return 0;
}
