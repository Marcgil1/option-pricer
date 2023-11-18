#include <functional>
#include <iostream>
#include <numeric>
#include <memory>
#include <random>
#include <vector>

#include "eulerConstantLinearEuropeanPutPricer.hh"
#include "exactConstantLinearEuropeanPutPricer.hh"

int    numTrials  = 10000000;
double returnRate = 0.06;

int main() {
	auto generator    = std::make_unique<std::default_random_engine>();
	auto distribution = std::make_unique<std::normal_distribution<double>>(0.0, 1.0);
	ExactConstantLinearEuropeanPutPricer optionPricer(std::move(generator), std::move(distribution));

	auto optionVals =
		optionPricer.calculateTrialVals(numTrials);
	auto meanOptionVal =
		std::accumulate(
			optionVals->begin(),
			optionVals->end(), 0.0)
		/ numTrials;
	auto discountedOptionVal =
		std::exp(-returnRate * 1.0) * meanOptionVal;

	std::cout << discountedOptionVal << std::endl;
}
