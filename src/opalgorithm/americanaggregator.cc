#include "./americanaggregator.hh"

#include "../params.hh"
#include "../leastsquaressolver/leastsquaressolver.hh"

#include <cmath>
#include <functional>


double payoff(double x) {
	return std::max(STRIKE_PRICE - x, 0.0);
}

std::vector<std::function<double(double)>>
basisFuncs = {
	[] (double x) { return 1.0;   },
	[] (double x) { return x;     },
	[] (double x) { return x*x;   },
	[] (double x) { return x*x*x; },
};

double 
AmericanAggregator::aggregate(Iterator beg, Iterator end) {
	std::vector<std::vector<double>> paths(beg, end);

	std::vector<double> payoffs      (NUM_TRIALS, 0.0);
	std::vector<int>    stoppingTimes(NUM_TRIALS, -1);
	for (size_t t = 0; t < NUM_TRIALS; t++) {
		payoffs      [t] = payoff(paths[t].back());
		stoppingTimes[t] = NUM_EXERCISE_DATES - 1;
	}

	std::vector<size_t> pi;
	std::vector<double> b;
	std::vector<std::vector<double>> a;
	for (int ed = NUM_EXERCISE_DATES - 2; ed >= 0; ed--) {
		size_t j = 0;
		for (size_t t = 0; t < NUM_TRIALS; t++) {
			if (payoff(paths[t][ed]) > 0) {
				j++;
				pi.push_back(t);

				std::vector<double> newRow;
				for (size_t bs = 0; bs < std::size(basisFuncs); bs++) {
					newRow.push_back(basisFuncs[bs](paths[t][ed]));
				}
				a.emplace_back(std::move(newRow));

				b.push_back(std::exp(-RETURN_RATE * (stoppingTimes[t] - ed) * STEP_SIZE) * payoffs[t]);
			}
		}
		
		auto vec = LeastSquaresSolver::solve(a, b);

		for (size_t i = 0; i < j; i++) {
			double c = 0.0;
			for (size_t m = 0; m < std::size(basisFuncs); m++)
				c += vec->at(m) * a[i][m];

			if (payoff(paths[pi[i]][ed]) >= c) {
				payoffs      [pi[i]] = payoff(paths[pi[i]][ed]);
				stoppingTimes[pi[i]] = ed;
			}
		}
	}

	double c0 = 0.0;
	for (size_t t = 0; t < NUM_TRIALS; t++)
		c0 += std::exp(-RETURN_RATE * stoppingTimes[t] * STEP_SIZE) * payoffs[t];
	c0 /= NUM_TRIALS;

	return c0;
	//return std::max(Z0, C0) ?
}
