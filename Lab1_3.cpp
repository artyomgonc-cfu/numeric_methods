#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <cmath>
#include <string>
using namespace std;

const int w = 15;
const int sz = 30;

vector<double> get_integral(double eps) {
	double e = exp(-1) + eps;
	vector<double> e_vals{ e };
	for (int i = 2; i <= sz; i++) {
		e = 1.0 - double(i) * e;
		e_vals.push_back(e);
	}

	return e_vals;
}

double factorial(int k) {
	double ans = 1;
	for (int i = 2; i <= k; i++)
		ans *= i;
	return ans;
}

vector<double> get_optimal(double eps) {
	double e = eps;
	vector<double> e_vals{ e };
	for (int i = sz - 1; i >= 0; i--) {
		e = (double(1) - e) / (i + 1);
		e_vals.push_back(e);
	}
	return e_vals;
}

int main() {
	
	vector<double> epss{ 0, 1e-7, 1e-6, 1e-5 };
	vector<pair<double, vector<double>>> ans;
	for (double eps : epss)
		ans.push_back(make_pair(eps, get_integral(eps)));

	cout << "Unstable algorithm\n";

	cout << setw(2) << "k";
	for (int i = 0; i < ans.size(); i++)
		cout << "|" << setw(w - (!i ? 1 : 5)) << string("eps=") << ans[i].first;
	cout << endl;
	for (int i = 0; i <= 65; i++) cout << '-';
	cout << endl;

	for (int k = 1; k <= sz; k++) {
		cout << setw(2) << k;
		for (int i = 0; i < ans.size(); i++)
			cout << '|' << setw(w) << scientific << ans[i].second[k-1];
		cout << endl;
	}

	cout << "\nFor eps=(1e-5): diff/30! = " << (ans[0].second[29] - ans[3].second[29])/factorial(30) << " = eps" << endl;

	cout << "\nStable algorithm\n";

	epss = vector<double>{ 0, 1e-2, 1e-1, 1 };
	ans.clear();
	for (double eps : epss)
		ans.push_back(make_pair(eps, get_optimal(eps)));

	cout << setw(2) << "k";
	for (int i = 0; i < ans.size(); i++) {
		if (!i) cout << defaultfloat;
		else cout << scientific << setprecision(0);
		cout << "|" << setw(w - (!i ? 1 : 5)) << string("eps=") << ans[i].first;
	}
	cout << setprecision(6) << endl;
	for (int i = 0; i <= 65; i++) cout << '-';
	cout << endl;

	for (int k = 0; k <= sz; k++) {
		cout << setw(2) << sz-k;
		for (int i = 0; i < ans.size(); i++)
			cout << '|' << setw(w) << scientific << ans[i].second[k];
		cout << endl;
	}

	return 0;
}
