#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <omp.h>

using namespace std;

double test01(int n, double x[], double y[]);
double test02(int n, double x[], double y[]);

int main() {
    double factor;
    int i;
    int n;
    double wtime;
    double *x;
    double xdoty;
    double *y;

    cout << "\n";
    cout << "  Number of processors available = " << omp_get_num_procs() << "\n";
    cout << "  Number of threads =              " << omp_get_max_threads() << "\n";
    
    //  Set up the vector data.
    //  N may be increased to get better timing data.
    
    n = 100;

    while (n < 10000000) {
        n = n * 10;

        x = new double[n];
        y = new double[n];

        factor = (double)(n);
        factor = 1.0 / sqrt(2.0 * factor * factor + 3 * factor + 1.0);

        for (i = 0; i < n; i++) {
            x[i] = (i + 1) * factor;
        }

        for (i = 0; i < n; i++) {
            y[i] = (i + 1) * 6 * factor;
        }

        cout << "\n";
        
        //  Test #1
        wtime = omp_get_wtime();
        xdoty = test01(n, x, y);
        wtime = omp_get_wtime() - wtime;

        cout << "  Sequential"
             << "  " << setw(8) << n
             << "  " << setw(14) << xdoty
             << "  " << setw(15) << wtime << "\n";
    
        //  Test #2
        wtime = omp_get_wtime();
        xdoty = test02(n, x, y);
        wtime = omp_get_wtime() - wtime;

        cout << "  Parallel  "
             << "  " << setw(8) << n
             << "  " << setw(14) << xdoty
             << "  " << setw(15) << wtime << "\n";

        delete[] x;
        delete[] y;
    }

    cout << "  Normal end of execution.\n\n";
    return 0;
}

// Serial execution
double test01(int n, double x[], double y[]) {
    int i;
    double xdoty;

    xdoty = 0.0;

    for (i = 0; i < n; i++) {
        xdoty = xdoty + x[i] * y[i];
    }

    return xdoty;
}

// Parallel execution
double test02(int n, double x[], double y[]) {
    int i;
    double xdoty;

    xdoty = 0.0;

    #pragma omp parallel shared(n, x, y) private(i)
    #pragma omp for reduction(+ : xdoty)
    for (i = 0; i < n; i++) {
        xdoty = xdoty + x[i] * y[i];
    }

    return xdoty;
}
