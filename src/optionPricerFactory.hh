#pragma once

#include "constantLinearEuropeanPutPricer.hh"

class OptionPricerFactory {
	public:
		static
		std::unique_ptr<
			ConstantLinearEuropeanPutPricer
		>
		getDefaultOptionPricer(
			std::unique_ptr<std::mt19937> generator,
			std::unique_ptr<std::normal_distribution<double>> distribution
		);
};
