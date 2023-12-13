#include "../params.hh"
#include "./europeanpartialcalculator.hh"

#include <vector>


double
EuropeanPartialCalculator::run() {
	std::vector<double> underlyingValuations;
	std::vector<double>        putValuations;

	sdeSimulator->simulate(
		underlyingValuations,
		NUM_TRIALS
	);

	putValuations.resize(std::size(underlyingValuations));
	#pragma omp parallel for
	for (size_t i = 0; i < std::size(underlyingValuations); i++)
		putValuations[i] = std::max(STRIKE_PRICE - underlyingValuations[i], 0.0);

	return std::accumulate(
		std::begin(putValuations),
		std::end  (putValuations),
		0.0
	);
}
