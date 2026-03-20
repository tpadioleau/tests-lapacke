/*
   LAPACKE Example : Calling DGELS using col-major layout
   =====================================================

   The program computes the solution to the system of linear
   equations with a square matrix A and multiple
   right-hand sides B, where A is the coefficient matrix
   and b is the right-hand side matrix:

   Description
   ===========

   In this example, we wish solve the least squares problem min_x || B - Ax ||
   for two right-hand sides using the LAPACK routine DGELS. For input we will
   use the 5-by-3 matrix

         ( 1  1  1 )
         ( 2  3  4 )
     A = ( 3  5  2 )
         ( 4  2  5 )
         ( 5  4  3 )
    and the 5-by-2 matrix

         ( -10 -3 )
         (  12 14 )
     B = (  14 12 )
         (  16 16 )
         (  18 16 )
    We will first store the input matrix as a static C two-dimensional array,
    which is stored in col-major layout, and let LAPACKE handle the work space
    array allocation. The LAPACK base name for this function is gels, and we
    will use double precision (d), so the LAPACKE function name is
  LAPACKE_dgels.

    lda=5 and ldb=5. The output for each right hand side is stored in b as
    consecutive vectors of length 3. The correct answer for this problem is
    the 3-by-2 matrix

         ( 2 1 )
         ( 1 1 )
         ( 1 2 )

    A complete C program for this example is given below. Note that when the
  arrays are passed to the LAPACK routine, they must be dereferenced, since
  LAPACK is expecting arrays of type double *, not double **.


   LAPACKE Interface
   =================

   LAPACKE_dgels (col-major, high-level) Example Program Results

  -- LAPACKE Example routine (version 3.7.0) --
  -- LAPACK is a software package provided by Univ. of Tennessee,    --
  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
     December 2016

*/
/* Calling DGELS using col-major layout */

/* Includes */
#include <cstdio>
#include <lapacke.h>

/* Auxiliary routine: printing a matrix */
void print_matrix_rowmajor(char const *desc, lapack_int m, lapack_int n,
                           double *mat, lapack_int ldm) {
  std::printf("\n %s\n", desc);

  for (lapack_int i = 0; i < m; i++) {
    for (lapack_int j = 0; j < n; j++) {
      std::printf(" %6.2f", mat[i * ldm + j]);
    }
    std::printf("\n");
  }
}

/* Auxiliary routine: printing a matrix */
void print_matrix_colmajor(char const *desc, lapack_int m, lapack_int n,
                           double *mat, lapack_int ldm) {
  std::printf("\n %s\n", desc);

  for (lapack_int i = 0; i < m; i++) {
    for (lapack_int j = 0; j < n; j++) {
      std::printf(" %6.2f", mat[i + j * ldm]);
    }
    std::printf("\n");
  }
}

/* Auxiliary routine: printing a vector of integers */
void print_vector(char const *desc, lapack_int n, lapack_int *vec) {
  std::printf("\n %s\n", desc);
  for (lapack_int j = 0; j < n; j++) {
    std::printf(" %6i", vec[j]);
  }
  std::printf("\n");
}

/* Main program */
int main(int argc, char const *argv[]) {
  /* Locals */
  double A[5][3] = {{1, 2, 3}, {4, 5, 1}, {3, 5, 2}, {4, 1, 4}, {2, 5, 3}};
  double b[5][2] = {{-10, 12}, {14, 16}, {18, -3}, {14, 12}, {16, 16}};

  /* Initialization */
  lapack_int const m = 5;
  lapack_int const n = 3;
  lapack_int const nrhs = 2;
  lapack_int const lda = 5;
  lapack_int const ldb = 5;

  /* Print Entry Matrix */
  print_matrix_colmajor("Entry Matrix A", m, n, *A, lda);
  /* Print Right Rand Side */
  print_matrix_colmajor("Right Hand Side b", n, nrhs, *b, ldb);
  std::printf("\n");

  /* Executable statements */
  std::printf(
      "LAPACKE_dgels (col-major, high-level) Example Program Results\n");
  /* Solve least squares problem*/
  lapack_int const info =
      LAPACKE_dgels(LAPACK_COL_MAJOR, 'N', m, n, nrhs, *A, lda, *b, ldb);

  /* Print Solution */
  print_matrix_colmajor("Solution", n, nrhs, *b, ldb);
  std::printf("\n");
  std::exit(info);
} /* End of LAPACKE_dgels Example */