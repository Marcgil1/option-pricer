#pragma once

#include "constantLinearEuropeanPutPricer.hh"

class OptionPricerFactory {
	public:
		static
		std::unique_ptr<
			ConstantLinearEuropeanPutPricer
		>
		getDefaultOptionPricer();
};
