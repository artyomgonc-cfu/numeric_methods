#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

double f(double x) {
	return (1.0 - cos(x)) / pow(x, 2);
}
double a = 0, b = 1;

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
	for (double x = a+h; x < b-h/2; x += h) {
		s += f(x);
	}
	return (s + (0.5+f(b))/2) * h;
}

double simpson(int n) {
	double h = (b - a) / n;
	double s4 = 0;
	for (double x = a; x <= b-h/2; x += h) {
		s4 += f(x+h/2);
	}

	double s2 = 0;
	for (double x = a+h; x <= b - h / 2; x += h) {
		s2 += f(x);
	}

	return (0.5 + f(b) + 4.0*s4 + 2.0*s2) * h/6;
}

void get_n(double (*func)(int), const vector<double>& eps, int order, const string& label) {
	for (double e : eps) {
		int curn = 1;
		while (abs((*func)(curn * 2) - (*func)(curn)) / (pow(2.0, order) - 1) >= e) {
			curn *= 2;
		} 
		cout << fixed << setprecision(8);
		cout << "|" << setw(9) << label << "|";
		cout << setw(10) << e << "|";
		cout << setw(10) << (*func)(2 * curn) << "|";
		cout << setw(4) << 2*curn << "|" << endl;
	}
	cout << endl;
}

int main() {

	vector<double> eps{ 1e-2, 1e-4, 1e-8 };

	cout << "|" << setw(9) << "Method" << "|";
	cout << setw(10) << "Eps" << "|";
	cout << setw(10) << "S" << "|";
	cout << setw(4) << "N" << "|" << endl << endl;

	get_n(&rect, eps, 2, "Rectangle");
	get_n(&trapeze, eps, 2, "Trapezoid");
	get_n(&simpson, eps, 4, "Simpson");

	return 0;
}
