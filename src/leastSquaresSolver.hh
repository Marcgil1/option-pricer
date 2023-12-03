#pragma once

#include <memory>
#include <vector>

typedef std::vector<double> Vector;
typedef std::vector<Vector> Matrix;


class LeastSquaresSolver {
	public:
		static
		std::unique_ptr<Vector>
		solve(Matrix const& mat, Vector const& vec);
	private:
		static
		std::unique_ptr<Matrix>
		getAdjMat(Matrix const& mat);

		static
		std::unique_ptr<Matrix>
		getCoeMat(Matrix const& mat, Matrix const& adjMat);

		static
		std::unique_ptr<Vector>
		getRhsVec(Vector const& vec, Matrix const& adjMat);

		static
		std::unique_ptr<Vector>
		linSolve(Matrix const& coeMat, Vector const& rhsVec);
};
