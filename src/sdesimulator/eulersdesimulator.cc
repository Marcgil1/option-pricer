#include "./eulersdesimulator.hh"

#include "../params.hh"


void
EulerSdeSimulator::calcSimulations(
	std::vector<std::vector<double>>& res,
	size_t				              numTrials,
	size_t                            samplesPerTrial)
{
	res.resize(numTrials);

	#pragma omp parallel for
	for (size_t trial = 0; trial < numTrials; trial++)
		calcSingleSimulation(
			res[trial], trial, samplesPerTrial);
}


void
EulerSdeSimulator::calcSingleSimulation(
	std::vector<double>& singlePath,
	size_t               trial,
	size_t               samplesPerTrial)
{
	singlePath.resize(samplesPerTrial, 0.0);

	// NOTE: It must hold that NUM_STEPS % samplesPerTrial == 0
	auto stepsPerSample = NUM_STEPS / samplesPerTrial;
	auto rnd            = rndNums[trial];
	auto stockVal       = INITIAL_VALUE;
	for (unsigned step = 1; step < NUM_STEPS; step++) {
		auto dt   =                       STEP_SIZE;
		auto dw   = rnd[step] * std::sqrt(STEP_SIZE);
		stockVal *= 1 + ALPHA*dt + BETA*dw;

		if ((step+1) % stepsPerSample == 0)
			singlePath[(step+1) / stepsPerSample - 1] = stockVal;
	}
}
