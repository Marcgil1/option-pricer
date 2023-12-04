#pragma once

#include "constantLinearEuropeanPutPricer.hh"

#include <memory>
#include <random>

class EulerConstantLinearEuropeanPutPricer
		: public ConstantLinearEuropeanPutPricer {
	public:
		EulerConstantLinearEuropeanPutPricer(
			std::unique_ptr<std::mt19937> generator,
			std::unique_ptr<std::normal_distribution<double>> distribution)
			: ConstantLinearEuropeanPutPricer(
				std::move(generator), std::move(distribution))
			{}
	protected:
		double calcStockValuation(unsigned trial);
};
