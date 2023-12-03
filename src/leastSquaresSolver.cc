#include "leastSquaresSolver.hh"

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
	return std::make_unique<Matrix>();
}

std::unique_ptr<Matrix>
LeastSquaresSolver::getCoeMat(Matrix const& mat, Matrix const& adjMat) {
	return std::make_unique<Matrix>();
}

std::unique_ptr<Vector>
LeastSquaresSolver::getRhsVec(Vector const& vec, Matrix const& adjMat) {
	return std::make_unique<Vector>();
}

std::unique_ptr<Vector>
LeastSquaresSolver::linSolve(Matrix const& coeMat, Vector const& rhsVec) {
	return std::make_unique<Vector>();
}
