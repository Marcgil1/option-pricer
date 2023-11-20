#pragma once

#include "constantLinearEuropeanPutPricer.hh"

#include <memory>
#include <random>
#include <vector>

class EulerConstantLinearEuropeanPutPricer
		: public ConstantLinearEuropeanPutPricer {
	protected:
		double calcStockValuation(unsigned trial);
};
