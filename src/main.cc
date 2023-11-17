#include <functional>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

int numTrials = 10000000;
double alpha = 0.06;
double beta = 0.3;
double initialValue = 5;
double optionStrikePrice = 10;
double startTime = 0;
double endTime = 1;
double totalTime = endTime - startTime;
double returnRate = 0.06;

double exactOptionValue(double w) {
	return initialValue * exp((alpha - 0.5*beta*beta)*totalTime + beta*w);
}

int main() {
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0.0, 1.0);
	auto rnd = std::bind(distribution, generator);

	std::vector<double> rndNums(numTrials, 0.0);
	for (int trial = 0; trial < numTrials; trial++) {
		rndNums[trial] = rnd();
	}

	std::vector<double> trialVals(numTrials, 0.0);
	for (int trial = 0; trial < numTrials; trial++) {
		auto w = rndNums[trial] * std::sqrt(totalTime);
		auto stockPrice = exactOptionValue(w);
		trialVals[trial] = std::max(optionStrikePrice - stockPrice, 0.0);
	}

	auto meanOptionVal =
		std::accumulate(std::begin(trialVals), std::end(trialVals), 0.0) / numTrials;
	auto discountedOptionVal = exp(-returnRate * totalTime) * meanOptionVal;

	std::cout << discountedOptionVal << std::endl;
}
