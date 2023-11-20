#include "constantLinearEuropeanPutPricer.hh"

void
ConstantLinearEuropeanPutPricer::calcRandomNumbers(unsigned numTrials) {
	rndNums.clear();
	rndNums.resize(numTrials, std::vector<double>());

	#pragma omp parallel for
	for (unsigned trial = 0; trial < numTrials; trial++) {
		rndNums[trial].resize(params.numSteps, 0.0);
		for (auto& num: rndNums[trial])
			num = (*distribution)(*generator);
	}
}

void
ConstantLinearEuropeanPutPricer::calcOptionValuations(unsigned numTrials) {
	trialVals->clear();
	trialVals->resize(numTrials, 0.0);

	#pragma omp parallel for
	for (unsigned trial = 0; trial < numTrials; trial++)
		trialVals->at(trial) = calcOptionValuation(trial);
}

std::unique_ptr<std::vector<double>>
ConstantLinearEuropeanPutPricer::calculateTrialVals(unsigned numTrials) {
	calcRandomNumbers   (numTrials);
	calcOptionValuations(numTrials);

	return std::move(trialVals);
}

double
ConstantLinearEuropeanPutPricer::calcOptionValuation(unsigned trial) {
	return std::max(
		params.strikePrice - calcStockValuation(trial),
		0.0
	);
}
