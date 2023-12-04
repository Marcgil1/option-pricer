#include "optionPricerFactory.hh"

#include "eulerConstantLinearEuropeanPutPricer.hh"

std::unique_ptr<
	ConstantLinearEuropeanPutPricer
>
OptionPricerFactory::getDefaultOptionPricer(
		std::unique_ptr<std::mt19937> generator,
		std::unique_ptr<std::normal_distribution<double>> distribution) {
	return std::make_unique<EulerConstantLinearEuropeanPutPricer>(
		std::move(generator), std::move(distribution)
	);
}
