#include "./leastsquaressolver.hh"

#include <iostream>

#include <assert.h>
#include <stdlib.h>

#include <cblas.h>
#include <lapacke.h>


std::unique_ptr<Vector>
LeastSquaresSolver::solve(
	Matrix const& coeMat, Vector const& rhsVec) {
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
		1,  			  // Number of right-hand-sides
		rawCoeMat, dim2,  // Coeficient matrix and its leading dimension.
		rawRhsVec, 1);    // RHS and its leading dimension.
	if (info != 0) {
		std::cerr << "There was some error when solving a least squares ";
		std::cerr << "problem:" << info << std::endl;
	}

	auto res = std::make_unique<Vector>();
	res->resize(dim1);
	for (size_t i1 = 0; i1 < dim1; i1++)
		res->at(i1) = rawRhsVec[i1];

	std::free(rawCoeMat);
	std::free(rawRhsVec);

	return std::move(res);
}
