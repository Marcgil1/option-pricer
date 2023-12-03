#include "leastSquaresSolver.hh"

#include <iostream>

#include <assert.h>
#include <stdlib.h>

#include <cblas.h>
#include <lapacke.h>


std::unique_ptr<Vector>
LeastSquaresSolver::solve(
	Matrix const& mat, Vector const& vec) {
	auto adjMat = getAdjMat(mat);
	auto coeMat = getCoeMat(mat, *adjMat);
	auto rhsVec = getRhsVec(vec, *adjMat);

	return std::move(
		linSolve(*coeMat, *rhsVec)
	);
}

std::unique_ptr<Matrix>
LeastSquaresSolver::getAdjMat(Matrix const& mat) {
	if (std::empty(mat))
		return std::make_unique<Matrix>();

	auto numRows = std::size(mat);
	auto numCols = std::size(mat.front());

	auto  res    = std::make_unique<Matrix>();
	auto& adjMat = *res;

	adjMat.resize(numCols);
	for (size_t col = 0; col < numCols; col++) {
		adjMat[col].resize(numRows);
		for (size_t row = 0; row < numRows; row++)
			adjMat[col][row] = mat[row][col];
	}
	
	return std::move(res);
}

std::unique_ptr<Matrix>
LeastSquaresSolver::getCoeMat(Matrix const& mat, Matrix const& adjMat) {
	if (std::empty(mat) or std::empty(adjMat))
		return std::make_unique<Matrix>();

	auto dim1 = std::size(adjMat);
	auto dim2 = std::size(adjMat.front());
	auto dim3 = std::size(mat.front());

	assert(dim2 == std::size(mat));

	auto  res    = std::make_unique<Matrix>(dim1);
	auto& coeMat = *res;
	for (size_t i1 = 0; i1 < dim1; i1++) {
		auto& row = coeMat[i1];

		row.resize(dim3);
		for (size_t i3 = 0; i3 < dim3; i3++) {
			auto& x = row[i3];

			x = 0;
			for (size_t i2 = 0; i2 < dim2; i2++)
				x += adjMat[i1][i2] * mat[i2][i3];
		}
	}

	return std::move(res);
}

std::unique_ptr<Vector>
LeastSquaresSolver::getRhsVec(Vector const& vec, Matrix const& adjMat) {
	if (std::empty(adjMat))
		return std::make_unique<Vector>();

	auto numRows = std::size(adjMat);
	auto numCols = std::size(adjMat.front());

	assert(std::size(vec) == numCols);

	auto  res    = std::make_unique<Vector>(numRows);
	auto& rhsVec = *res;
	for (size_t row = 0; row < numRows; row++) {
		auto& x = rhsVec[row];

		x = 0;
		for (size_t col = 0; col < numCols; col++)
			x += adjMat[row][col]*vec[col];
	}

	return std::move(res);
}

std::unique_ptr<Vector>
LeastSquaresSolver::linSolve(Matrix const& coeMat, Vector const& rhsVec) {
	int dim1 = static_cast<int>(std::size(coeMat));
	int dim2 = static_cast<int>(std::size(coeMat.front()));

	assert(static_cast<int>(std::size(rhsVec)) == dim1);

	double* rawCoeMat = static_cast<double*>(
		std::malloc(sizeof(double) * dim1 * dim2));
	for (size_t i1 = 0; i1 < dim1; i1++)
		for (size_t i2 = 0; i2 < dim2; i2++)
			rawCoeMat[i1*dim2 + i2] = coeMat[i1][i2];

	double* rawRhsVec = static_cast<double*>(
		std::malloc(sizeof(double) * dim1));
	for (size_t i1 = 0; i1 < dim1; i1++)
		rawRhsVec[i1] = rhsVec[i1];

    int info = LAPACKE_dgels(
		LAPACK_ROW_MAJOR, // Row matrix order.
		'N',		 	  // Do not transpose rawCoeMat.
		dim1, dim2,       // Input dimensions.
		1,				  // Number of right-hand-sides
		rawCoeMat, dim1,  // Coeficient matrix and its leading dimension.
		rawRhsVec, dim1); // RHS and its leading dimensionl.
	if (info != 0) {
		std::cerr << "There was some error when solving a least squares ";
		std::cerr << "problem:" << info << std::endl;
	}

	auto res = std::make_unique<Vector>();
	res->resize(dim1);
	for (size_t i1 = 0; i1 < dim1; i1++)
		res->at(i1) = rawRhsVec[i1];

	return std::move(res);
}
