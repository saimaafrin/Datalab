#include <iostream>  
using namespace std;  
#include <cstdbool>
#include <cstdlib>

typedef struct Sparse_Coordinate {
    int n_rows;
    int n_cols;
    int nnz;
    int* row_indices;
    int* col_indices;
    double* values;
} Sparse_Coordinate;


int create_sparse_coordinate(
    const double* A,
    int n_rows,
    int n_cols,
    int nnz,
    Sparse_Coordinate* A_coo
);

int print_sparse_coordinate(const Sparse_Coordinate* A_coo);

int matrix_vector_sparse_coordinate(
    const Sparse_Coordinate* A_coo,
    const double* vec,
    double* res
);

int free_sparse_coordinate(Sparse_Coordinate* A_coo);


int main (int argc, char** argv) {
    int n_rows = 5;
    int n_cols = 5;
    int nnz = 12;

    double A[] = {
        2,  0,  0,  2,  0,
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

    Sparse_Coordinate A_coo;

    create_sparse_coordinate(A, n_rows, n_cols, nnz, &A_coo);

    print_sparse_coordinate(&A_coo);

    matrix_vector_sparse_coordinate(&A_coo, x, Ax);
    
    cout<< "\n" << endl;
    for (int i=0; i<n_cols; ++i) {
        cout<< Ax[i]<< endl;
    }


    free_sparse_coordinate(&A_coo);

    return EXIT_SUCCESS;
}


int create_sparse_coordinate(
    const double* A,
    int n_rows,
    int n_cols,
    int nnz,
    Sparse_Coordinate* A_coo
) {
    A_coo->n_rows = n_rows;
    A_coo->n_cols = n_cols;
    A_coo->nnz = nnz;
   // twod = malloc(rows * sizeof(int *));
    A_coo->row_indices = (int *) calloc( nnz, sizeof(int));
    A_coo->col_indices = (int *) calloc(nnz, sizeof(int));
    A_coo->values = (double *) calloc(nnz, sizeof(double));

    int nnz_id = 0;

    for (int i=0; i<n_rows; ++i) {
        for (int j=0; j<n_cols; ++j) {
            if (A[i*n_cols + j] != 0) {
                A_coo->row_indices[nnz_id] = i;
                A_coo->col_indices[nnz_id] = j;
                A_coo->values[nnz_id] = A[i*n_cols + j];
                nnz_id++;
            }
        }
    }

    return EXIT_SUCCESS;
}

int print_sparse_coordinate(const Sparse_Coordinate* A_coo) {
    cout<<"\n"<< endl;
    cout<< "row\tcol\tval\n"<< endl;
    
    for(int nnz_id=0; nnz_id<A_coo->nnz; ++nnz_id) {
        int row_id = A_coo->row_indices[nnz_id];
        int col_id = A_coo->col_indices[nnz_id];
        double value = A_coo->values[nnz_id];

        cout<<  row_id <<"\t" << col_id << "\t"<< value << endl;
    }

    return EXIT_SUCCESS;
}

int matrix_vector_sparse_coordinate(
    const Sparse_Coordinate* A_coo,
    const double* vec,
    double* res
) {
    for (int i=0; i<A_coo->n_cols; ++i) {
        res[i] = 0.0;
    }

    for (int nnz_id=0; nnz_id<A_coo->nnz; ++nnz_id) {
        int row_id = A_coo->row_indices[nnz_id];
        int col_id = A_coo->col_indices[nnz_id];
        double value = A_coo->values[nnz_id];

        res[row_id] += value * vec[col_id];
    }

    return EXIT_SUCCESS;
}

int free_sparse_coordinate(Sparse_Coordinate* A_coo) {
    free(A_coo->row_indices);
    free(A_coo->col_indices);
    free(A_coo->values);

    return EXIT_SUCCESS;
}