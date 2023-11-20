#include "eulerConstantLinearEuropeanPutPricer.hh"

#include <cmath>

double
EulerConstantLinearEuropeanPutPricer::calcStockValuation(unsigned trial) {
	auto rnd      = rndNums[trial];
	auto stockVal = params.initialValue;
	for (unsigned step = 1; step < params.numSteps; step++) {
		auto dt   =                       params.stepSize;
		auto dw   = rnd[step] * std::sqrt(params.stepSize);
		stockVal *= 1 + params.alpha*dt + params.beta*dw;
	}
	return stockVal;
}


