#ifndef _MATRIX_FACTORIZATION_
#define _MATRIX_FACTORIZATION_

#include "matrix.h"
#include <cmath>

	/*!
	 * Contains methods for factoring matrices.
	 *
	 * */
	template <typename TField>
	class MatrixDecomposer {

		public:

		/*!
		 * Performs LU factorization with partial pivoting.
		 *
		 * Method based in the one presented in the book 'Numerical Analysis', Burden et al.
		 * Basically, returns two matrices, L and U, with L being
		 * lower triangular and U, upper triangular, such that
		 * source = L*U. Besides the basic factorization, performs also
		 * a partial pivoting to avoid round-off problems.
		 *
		 * @param source		Matrix to be factored.
		 * @param L				Lower triangular matrix.
		 * @param U				Upper triangular matrix.
		 * */
		static void lu (const Matrix<TField> & source,
				Matrix<TField> & L,
				Matrix<TField> & U,
				Matrix<TField> & P,
				bool partial_piv = true);
};

#include "../src/matrixDecomposer.inl"
#endif
