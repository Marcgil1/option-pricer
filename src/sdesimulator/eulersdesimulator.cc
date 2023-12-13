#include "./eulersdesimulator.hh"

#include "../params.hh"


void
EulerSdeSimulator::calcSimulations(
	std::vector<double>& res,
	size_t				 numTrials)
{
	res.resize(numTrials);

	#pragma omp parallel for
	for (size_t trial = 0; trial < numTrials; trial++)
		res[trial] = calcSingleSimulation(trial);
}


double
EulerSdeSimulator::calcSingleSimulation(size_t trial) {
	auto rnd      = rndNums[trial];
	auto stockVal = INITIAL_VALUE;
	for (unsigned step = 1; step < NUM_STEPS; step++) {
		auto dt   =                       STEP_SIZE;
		auto dw   = rnd[step] * std::sqrt(STEP_SIZE);
		stockVal *= 1 + ALPHA*dt + BETA*dw;
	}
	return stockVal;
}
