#include "exactConstantLinearEuropeanPutPricer.hh"

#include <cmath>

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
