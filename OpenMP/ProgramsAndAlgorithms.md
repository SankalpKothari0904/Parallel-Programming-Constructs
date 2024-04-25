# Programs And Algorithms
## Matrix Multiplication
```c++
#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;
const int N = 1000;
int main() {
	vector<vector<int>> A(N, vector<int>(N));
	vector<vector<int>> B(N, vector<int>(N));
	vector<vector<int>> C(N, vector<int>(N));

	// Initialize matrices A and B with random values
	for (int i = 0; i < N; i++) {
    		for (int j = 0; j < N; j++) {
        		A[i][j] = rand() % 100;
        		B[i][j] = rand() % 100;
    		}	
	}

	// Serial computation of matrix product.
	auto start_serial = chrono::high_resolution_clock::now();
	for (int i = 0; i < N; i++) {
    		for (int j = 0; j < N; j++) {
        		int sum = 0;
        		for (int k = 0; k < N; k++) {
            			sum += A[i][k] * B[k][j];
       			}
        		C[i][j] = sum;
    		}	
	}

	auto end_serial = chrono::high_resolution_clock::now();
	auto duration_serial = chrono::duration_cast<chrono::milliseconds>(end_serial - start_serial);

	// Perform matrix multiplication in parallel using OpenMP
   	auto start_parallel = chrono::high_resolution_clock::now();
   
	#pragma omp parallel for
   	for (int i = 0; i < N; i++) {
        	for (int j = 0; j < N; j++) {
            	int sum = 0;
            		for (int k = 0; k < N; k++) {
                		sum += A[i][k] * B[k][j];
            		}
            		C[i][j] = sum;
        	}
    	}

    	auto end_parallel = chrono::high_resolution_clock::now();
    	auto duration_parallel = chrono::duration_cast<chrono::milliseconds>(end_parallel - start_parallel);

   	cout << "Time taken for serial matrix multiplication: " << duration_serial.count() << " milliseconds" << endl;
	cout << "Time taken for parallel matrix multiplication: " << duration_parallel.count() << " milliseconds" << endl;
    	return 0;
}
```

The program is simple to understand, we first compute the matrix product between `A` AND `B` serially and then in parallel (using the `PARALLEL FOR` directive). Finally, we output the time taken in both these scenarios.

Output (Using 8 threads):
```
Time taken for serial matrix multiplication: 5997 milliseconds
Time taken for parallel matrix multiplication: 1652 milliseconds
```
## Vector Dot Product
```c++
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
    cout << "  Number of processors available = " << omp_get_num_procs() << "\n";
    cout << "  Number of threads =              " << omp_get_max_threads() << "\n";

    //  Set up the vector data.
    //  N may be increased to get better timing data.

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
        
        //  Test #1
        wtime = omp_get_wtime();
        xdoty = test01(n, x, y);
        wtime = omp_get_wtime() - wtime;

        cout << "  Sequential"
             << "  " << setw(8) << n
             << "  " << setw(14) << xdoty
             << "  " << setw(15) << wtime << "\n";

        //  Test #2
        wtime = omp_get_wtime();
        xdoty = test02(n, x, y);
        wtime = omp_get_wtime() - wtime;  

        cout << "  Parallel  "
             << "  " << setw(8) << n
             << "  " << setw(14) << xdoty
             << "  " << setw(15) << wtime << "\n";

        delete[] x;
        delete[] y;
    }

    cout << "  Normal end of execution.\n\n";
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
```

The function `double test02(int n, double x[], double y[])` computes the dot product `xdoty` of `x` and `y` in a parallel manner using the `PARALLEL` directive. The variables `n`, `x`, and `y` (the length of the vectors, and the vectors themself) are shared across threads, specified by the `SHARED` clause. The loop iteration variable `i` is private (using the `PRIVATE` clause), and each thread has its own separate copy of `i`.  Finally, the `REDUCTION` clause is used to accumulate the final result.
The rest of the code is simple to understand.

Output, shows a comparison of runtimes between serial and parallel computation (printing `n`, `xdoty`, `wtime`):
```
  Number of processors available = 16
  Number of threads =              8

  Sequential      1000            1000        3.727e-06
  Parallel        1000            1000      0.000507893

  Sequential     10000           10000       3.2312e-05
  Parallel       10000           10000      0.000285293

  Sequential    100000          100000      0.000330169
  Parallel      100000          100000       7.8592e-05

  Sequential   1000000           1e+06        0.0032386
  Parallel     1000000           1e+06      0.000957203

  Sequential  10000000           1e+07        0.0435151
  Parallel    10000000           1e+07        0.0117223
  Normal end of execution.
```
