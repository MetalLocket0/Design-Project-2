#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

const double XMIN = -2.0;
const double XMAX =  2.0;
const double TOL  =  0.00001;

// pretty-print polynomial
void print_polynomial(vector<double> c) {
    double ci;
    bool flag = true;

    cout << "p(x) = ";
    for(unsigned long int i = c.size()-1; i >= 0; i--) {
        ci = c.at(i);  // current coefficient
        if (c.size() == 1) cout << ci; // always print at least one coefficient
        if (ci != 0) {
            // Print signs. Only print first sign if it is negative.
            if (flag) {
                // handle first minus sign
                flag = false;
                if (ci < 0) cout << "-";
            } else {
                if (ci < 0) cout << " - ";
                else cout << " + ";
            }
            // Print coefficient
            if (i == 0)
                cout << abs(ci); // always print last coefficient
            else if (abs(ci) != 1)
                cout << abs(ci); // don't print ones
            // Print x, except for last coefficient
            if (i != 0)
                cout << "x";
            // Print exponent, except for last two coefficients
            if (i > 1)
                cout << "^" << i;
        }
    }
    cout << endl;
}

// exact (theoretical) area
double exact(vector<double> c) {
    vector<double> c_int;  // coefficients of integral

    c_int.push_back(0.0); // integral of polynomial has no zero-degree term
    for (unsigned long int i = 0; i < c.size(); i++) {
        c_int.push_back(c.at(i)/(i+1));  // integrate term-by-term
    }
    return eval(XMAX, c_int) - eval(XMIN, c_int); // fundamental theorem of calculus
}

// read coefficients from cin, until empty newline
vector<double> read_coefficients(void) {
    string userInput; 
    getline ( cin , userInput);

    double userCoe = stod (userInput);

    return userCoe;
}

// evaluate polynomial given by coefficients c at x
double eval(double x, vector<double> c) {
    // your code here
}

double estimate(double step, vector<double> c) {
    // your code here
}

int main(void) {


    return 0;
}