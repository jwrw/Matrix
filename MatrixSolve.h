#include <Matrix.h>

#ifndef MATRIXSOLVE_H
#define MATRIXSOLVE_H

// class Singular {};
// class BadSolveArgs {};

template <class T>

// Solve the matrix equation Ax = v for x; where x, v are column vectors
// will work on copies of A,v so originals are undisturbed
Matrix<T> solveFor(Matrix<T> A, Matrix<T> v)
// throw(Singular)
{
  if (A._row <= 0 || A._column != A._row || A._row != v._row ||
      v._column != 1) {
    //     throw BadSolveArgs();
    return Matrix<T>();
  }

  for (int pivot = 0; pivot < A._row; pivot++) {
    // find best row for pivot - row with largest value in the pivot column
    T maxPivot = 0;
    int bestRow = -1;
    for (int chkRow = pivot; chkRow < A._row; chkRow++) {
      if (A._entity[chkRow][pivot] > maxPivot) {
        bestRow = chkRow;
        maxPivot = A._entity[chkRow][pivot];
      } else if (-A._entity[chkRow][pivot] > maxPivot) {
        bestRow = chkRow;
        maxPivot = -A._entity[chkRow][pivot];
      }
    }

    if (bestRow == -1) {
      // throw Singular(); //error
      return Matrix<T>();
    }

    if (bestRow != pivot) {
      A.swapRow(pivot, bestRow);
      v.swapRow(pivot, bestRow);
    }

    maxPivot = A._entity[pivot][pivot];  // get the sign back if was -ve
    // we've got our pivot row - divide row by maxPivot to make pivot value 1
    A._entity[pivot][pivot] = 1;
    for (int c = pivot + 1; c < A._column; c++) {
      A._entity[pivot][c] /= maxPivot;
    }
    // and do same in vector
    v._entity[pivot][0] /= maxPivot;

    // we'll go full Gaussian on this - as it saves some coding
    // TODO could be more efficient?
    for (int r = 0; r < A._row;
         r++) {  // full gaussian so do all rows but our own
      if (r != pivot) {
        T f = A._entity[r][pivot];
        A._entity[r][pivot] = 0;
        for (int c = pivot + 1; c < A._column; c++) {
          A._entity[r][c] -= f * A._entity[pivot][c];
        }
        v._entity[r][0] -= f * v._entity[pivot][0];
      }
    }
  }

  return v;
}

// Some handy typedefs
typedef Matrix<int16_t> Matrixi;
typedef Matrix<int32_t> Matrixl;
typedef Matrix<float> Matrixf;
typedef Matrix<double> Matrixd;

#endif  // MATRIXSOLVE_H