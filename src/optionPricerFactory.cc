#include "optionPricerFactory.hh"

#include "eulerConstantLinearEuropeanPutPricer.hh"

std::unique_ptr<
	ConstantLinearEuropeanPutPricer
>
OptionPricerFactory::getDefaultOptionPricer() {
	return std::make_unique<EulerConstantLinearEuropeanPutPricer>();
}

