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
};
