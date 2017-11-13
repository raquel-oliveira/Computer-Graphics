template<typename TField>
void MatrixDecomposer<TField>::lu (const Matrix<TField> & source,
		Matrix<TField> & L,
		Matrix<TField> & U,
		Matrix<TField> & P,
		bool partial_piv) {
	int n = source.rows;
	for (int i = 0; i < n - 1; ++i) {
		// Perform partial pivoting
		if (partial_piv) {
			// Select max
			int imax = i;
			for (int j = i + 1; j < n; ++j) {
				if (std::abs(source[j][i]) > std::abs(source[imax][i]))
					imax = j;
			}
			// Exchange
			P.swap_lines(imax, i);
			U.swap_lines(imax, i, i, source.rows - 1);
			L.swap_lines(imax, i, 0, i - 1);
		}
		// Gaussian
		for (int j = i + 1; j < source.rows; ++j) {
			L[j][i] = U[j][i]/U[i][i];
			for (int m = i; m < source.rows; ++m) {
				U[j][m] = U[j][m] - L[j][i]*U[i][m];
			}
		}
	}
}
