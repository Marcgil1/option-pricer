#include "eulerConstantLinearEuropeanPutPricer.hh"

#include <cmath>

void
EulerConstantLinearEuropeanPutPricer::calcRandomNumbers(unsigned numTrials) {
	rndNums.clear();
	rndNums.resize(numTrials, std::vector<double>());
	for (auto& rnd: rndNums) {
		rnd.resize(params.numSteps, 0.0);
		for (auto& num: rnd)
			numTrials = (*distribution)(*generator);
	}
}

// TODO: Abstract to parent class.
void
EulerConstantLinearEuropeanPutPricer::calcOptionValuations(unsigned numTrials) {
	trialVals->clear();
	trialVals->resize(numTrials, 0.0);
	for (int trial = 0; trial < numTrials; trial++)
		trialVals->at(trial) = calcOptionValuation(rndNums[trial]);
}

double
EulerConstantLinearEuropeanPutPricer::calcStockValuation(
		std::vector<double> const& rnd) {
	double stockVal = params.initialValue;
	for (int step = 1; step < params.numSteps; step++) {
		auto dt   =                       params.stepSize;
		auto dw   = rnd[step] * std::sqrt(params.stepSize);
		stockVal *= 1 + params.alpha*dt + params.beta*dw;
	}
	return stockVal;
}

// TODO: Abstract to parent class.
double
EulerConstantLinearEuropeanPutPricer::calcOptionValuation(
		std::vector<double> const& rnd) {
	return std::max(
		params.strikePrice - calcStockValuation(rnd),
		0.0
	);
}

// TODO: Abstract to parent class.
std::unique_ptr<std::vector<double>>
EulerConstantLinearEuropeanPutPricer::calculateTrialVals(unsigned numTrials) {
	calcRandomNumbers   (numTrials);
	calcOptionValuations(numTrials);

	return std::move(trialVals);
}
