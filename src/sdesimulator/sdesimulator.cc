#include "./sdesimulator.hh"

#include "../params.hh"


void
SdeSimulator::simulate(std::vector<double>& res, size_t numTrials) {
	calcRandomNumbers(     numTrials);
	calcSimulations  (res, numTrials);
}

void
SdeSimulator::calcRandomNumbers(size_t numTrials) {
	rndNums.clear ();
	rndNums.resize(numTrials, std::vector<double>());

	#pragma omp parallel for
	for (unsigned trial = 0; trial < numTrials; trial++) {
		rndNums[trial].resize(NUM_STEPS, 0.0);
		for (auto& num: rndNums[trial])
			num = (*distribution)(*generator);
	}
}
