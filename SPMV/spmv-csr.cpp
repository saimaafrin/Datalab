#include <iostream>  
using namespace std;  
#include <cstdbool>
#include <cstdlib>

typedef struct Sparse_CSR {
    int n_rows;
    int n_cols;
    int n_nz;
    int* row_ptrs;
    int* col_indices;
    double* values;
} Sparse_CSR;


int create_sparse_csr(
    const double* A,
    int n_rows,
    int n_cols,
    int n_nz,
    Sparse_CSR* A_csr
);

int print_sparse_csr(const Sparse_CSR* A_csr);

int matrix_vector_sparse_csr(
    const Sparse_CSR* A_coo,
    const double* vec,
    double* res
);

int free_sparse_csr(Sparse_CSR* A_csr);


int main (int argc, char** argv) {
    int n_rows = 5;
    int n_cols = 5;
    int n_nz = 12;

    double A[] = {
        1,  0,  0,  2,  0,
        3,  4,  2,  5,  0,
        5,  0,  0,  8, 17,
        0,  0, 10, 16,  0,
        0,  0,  0,   0, 14
    };
    double x[] = {
        1,
        2,
        3,
        4,
        5
    };
    double Ax[5];

    Sparse_CSR A_csr;

    create_sparse_csr(A, n_rows, n_cols, n_nz, &A_csr);

    print_sparse_csr(&A_csr);

    matrix_vector_sparse_csr(&A_csr, x, Ax);
    
    cout<< "\n" << endl;
    for (int i=0; i<n_rows; ++i) {
        cout<< Ax[i] << endl;
    }

    free_sparse_csr(&A_csr);

    return EXIT_SUCCESS;
}


int create_sparse_csr(
    const double* A,
    int n_rows,
    int n_cols,
    int n_nz,
    Sparse_CSR* A_csr
) {
    A_csr->n_rows = n_rows;
    A_csr->n_cols = n_cols;
    A_csr->n_nz = n_nz;
    A_csr->row_ptrs = (int *) calloc(n_rows+1, sizeof(int));
    A_csr->col_indices = (int *) calloc(n_nz, sizeof(int));
    A_csr->values = (double *) calloc(n_nz, sizeof(double));

    int nz_id = 0;

    for (int i=0; i<n_rows; ++i) {
        A_csr->row_ptrs[i] = nz_id;
        for (int j=0; j<n_cols; ++j) {
            if (A[i*n_cols + j] != 0.0) {
                A_csr->col_indices[nz_id] = j;
                A_csr->values[nz_id] = A[i*n_cols + j];
                nz_id++;
            }
        }
    }

    A_csr->row_ptrs[n_rows] = nz_id;

    return EXIT_SUCCESS;
}

int print_sparse_csr(const Sparse_CSR* A_csr) {
    cout<< "row\tcol\tval\n" << endl;
    
    for (int i=0; i<A_csr->n_rows; ++i) {
        int nz_start = A_csr->row_ptrs[i];
        int nz_end = A_csr->row_ptrs[i+1];
        for (int nz_id=nz_start; nz_id<nz_end; ++nz_id) {
            int j = A_csr->col_indices[nz_id];
            double val = A_csr->values[nz_id];
            cout<<  i <<"\t" << j << "\t"<< val << endl;
        }
    }
    return EXIT_SUCCESS;
}

int matrix_vector_sparse_csr(
    const Sparse_CSR* A_csr,
    const double* vec,
    double* res
) {
    for (int i=0; i<A_csr->n_rows; ++i) {
        res[i] = 0.0;
        int nz_start = A_csr->row_ptrs[i];
        int nz_end = A_csr->row_ptrs[i+1];
        for (int nz_id=nz_start; nz_id<nz_end; ++nz_id) {
            int j = A_csr->col_indices[nz_id];
            double val = A_csr->values[nz_id];
            res[i] = res[i] + val * vec[j];
        }
    }
    return EXIT_SUCCESS;
}

int free_sparse_csr(Sparse_CSR* A_csr) {
    free(A_csr->row_ptrs);
    free(A_csr->col_indices);
    free(A_csr->values);

    return EXIT_SUCCESS;
}