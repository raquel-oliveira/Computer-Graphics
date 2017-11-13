#ifndef _LSYSTEM_SOLVER
#define _LSYSTEM_SOLVER

#include "matrix.h"
#include "matrixDecomposer.h"
#include "linearSystemSolver.h"


	/*!
	 * Contains methods for solving linear systems.
	 *
	 * */
	template<typename TField>
	class LinearSystemSolver {
		public:

			/**
			 * Performs backward substitution when receives
			 * an upper triangular matrix (solves the system
			 * Ax = b, where A is upper triangular).
			 *
			 * @param A             Matrix of coefficients.
			 * @param b             Vector.
			 * @param x             Solution of the linear system.
			 * */
			static void back_substitution(const Matrix<TField> A,
								  const Matrix<TField> b,
								  Matrix<TField> & x);

			/**
			 * Performs forward substitution when receives
			 * an upper triangular matrix (solves the system
			 * Ax = b, where A is lower triangular).
			 *
			 * @param A             Matrix of coefficients.
			 * @param b             Vector.
			 * @param x             Solution of the linear system.
			 * */
			static void forward_substitution(const Matrix<TField> A,
								  const Matrix<TField> b,
								  Matrix<TField> & x);

			/*!
			 * Solve a linear system by LU decomposition.
			 *
			 * @param A             Matrix of coefficients.
			 * @param b             Vector.
			 * @param x             Solution of the linear system.
			 * */
			static void solve_by_lu(const Matrix<TField> A,
								  Matrix<TField> b,
								  Matrix<TField> & x,
								  bool partial_piv = true);

	};

#include "../src/linearSystemSolver.inl"
#endif
