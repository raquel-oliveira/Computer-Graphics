template<typename TField>
void LinearSystemSolver<TField>::back_substitution (const Matrix<TField> A,
		const Matrix<TField> b,
		Matrix<TField> & x) {
	Matrix<TField> xTemp {b.rows, 1, 0};
	for (int i = A.rows - 1; i >= 0; --i) {
		xTemp[i][0] = b[i][0];
		for (int j = i + 1; j < A.cols; ++j) {
			xTemp[i][0] = xTemp[i][0] - xTemp[j][0]*A[i][j];
		}
		xTemp[i][0] = xTemp[i][0]/A[i][i];
	}
	x = xTemp;
}

template<typename TField>
void LinearSystemSolver<TField>::forward_substitution (const Matrix<TField> A,
		const Matrix<TField> b,
		Matrix<TField> & x) {

	//Matrix<TField> xTemp {b.rows, 1, 0};
	for (int i = 0; i < A.rows; ++i) {
		x[i][0] = b[i][0];
		for (int j = 0; j < i; ++j) {
			x[i][0] = x[i][0] - x[j][0]*A[i][j];
		}
		x[i][0] = x[i][0]/A[i][i];
	}
	//x = xTemp;
}


template<typename TField>
void LinearSystemSolver<TField>::solve_by_lu(const Matrix<TField> A,
					  Matrix<TField> b,
					  Matrix<TField> & x,
					  bool partial_piv) {
	Matrix<TField> L {A.rows, A.rows, 1, 0};
	Matrix<TField> U {A};
	Matrix<TField> P {A.rows, A.rows, 1, 0};
	Matrix<TField> y {A.rows, 1, 0.0};
	MatrixDecomposer<TField>::lu(A, L, U, P, partial_piv);
	LinearSystemSolver<TField>::forward_substitution(L, P*b, y);
	LinearSystemSolver<TField>::back_substitution(U, y, x);
}
