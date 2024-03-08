#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

const double XMIN = -2.0;
const double XMAX =  2.0;
const double TOL  =  0.00001;

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


double eval(double x, vector<double> c) {
 double result = 0.0;
    for (unsigned long int i = 0; i < c.size(); i++) {
        result += c.at(i) * pow(x, i);
    }
    return result;
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
   vector<double> coefficients;
    string input;
    
    while (true) {
        getline(cin, input);
        if (input.empty()) {
            break; 
        }
        coefficients.push_back(stod(input));
    }
    return coefficients ;
}


double estimate(double step, vector<double> c) {
  double result = 0.0;
    for (double x = XMIN; x < XMAX; x += step) {
        result += eval(x, c) * step;
    }
    return result;
}
int main(void) {


    vector<double> coefficients = read_coefficients();
    
    double newApproximation = 0.0;
    double prevApproximation;
    
    double rectangle = 10.0;

    double step = (XMAX - XMIN) / rectangle;
    
    double val = 1.0;
    

    int iterations = 0;
    while (val > TOL) {
        prevApproximation = newApproximation;
        rectangle *= 2;
        step = (XMAX - XMIN) / rectangle;
        newApproximation = estimate(step, coefficients);
        iterations++;
        val = abs(prevApproximation - newApproximation);
    }

    cout << "Solution:"<< endl;
    print_polynomial(coefficients);
    cout << endl; 
    cout << "Estimate = " << fixed << setprecision(8) << newApproximation << endl;
    cout << "Exact = " << fixed << setprecision(8) << exact(coefficients) << endl;
    cout << "Error = " << fixed << setprecision(8) << abs(prevApproximation - exact(coefficients)) << endl;
    cout << "Iterations = " << iterations << endl;
    cout << "Step = " << step << endl;
    return 0;
}