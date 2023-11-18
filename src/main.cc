#include <functional>
#include <iostream>
#include <numeric>
#include <memory>
#include <random>
#include <vector>

int    numTrials  = 10000000;
double returnRate = 0.06;

class ExactConstantLinearEuropeanPutPricer {
	public:
		struct Params {
			double alpha = 0.06;
			double beta = 0.3;
			double initialValue = 5;
			double strikePrice = 10.0;
			double totalTime = 1.0;
		};
		
	private:
		std::unique_ptr<std::default_random_engine>       generator;
		std::unique_ptr<std::normal_distribution<double>> distribution;
		Params params;

	public:
		ExactConstantLinearEuropeanPutPricer(
			std::unique_ptr<std::default_random_engine>       generator,
			std::unique_ptr<std::normal_distribution<double>> distribution)
			: generator   (std::move(generator))
			, distribution(std::move(distribution))
			, trialVals   (std::make_unique<std::vector<double>>())
			{}
			
		std::unique_ptr<std::vector<double>>
		calculateTrialVals(unsigned numTrials);

	private:
		std::vector<double>                  rndNums;
		std::unique_ptr<std::vector<double>> trialVals;

		void   calcRandomNumbers   (unsigned numTrials);
		void   calcOptionValuations(unsigned numTrials);
		double calcOptionValuation (double   rnd);
		double calcExactOptionValue(double   w);

};

void
ExactConstantLinearEuropeanPutPricer::calcRandomNumbers(unsigned numTrials) {
	rndNums.clear();
	rndNums.resize(numTrials, 0.0);

	for (int trial = 0; trial < numTrials; trial++)
		rndNums[trial] = (*distribution)(*generator);
}

void
ExactConstantLinearEuropeanPutPricer::calcOptionValuations(unsigned numTrials) {
	trialVals->clear();
	trialVals->resize(numTrials, 0.0);
	for (int trial = 0; trial < numTrials; trial++)
		trialVals->at(trial) = calcOptionValuation(rndNums[trial]);
}

double
ExactConstantLinearEuropeanPutPricer::calcExactOptionValue(double w) {
	return
		params.initialValue
		* std::exp(
			(params.alpha - 0.5*params.beta*params.beta)*params.totalTime
			+ params.beta*w
 		);
}

double
ExactConstantLinearEuropeanPutPricer::calcOptionValuation(double rnd) {
	auto w = rnd * std::sqrt(params.totalTime);
	return std::max(
		params.strikePrice - calcExactOptionValue(w),
		0.0
	);
}

std::unique_ptr<std::vector<double>>
ExactConstantLinearEuropeanPutPricer::calculateTrialVals(unsigned numTrials) {
	calcRandomNumbers   (numTrials);
	calcOptionValuations(numTrials);

	return std::move(trialVals);
}

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
