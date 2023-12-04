#pragma once

#include <memory>
#include <random>

class SdeSimulator {
	protected:
		std::unique_ptr<std::mt19937>                     generator;
		std::unique_ptr<std::normal_distribution<double>> distribution;
	public:
		SdeSimulator(
			std::unique_ptr<std::mt19937>                     generator,
			std::unique_ptr<std::normal_distribution<double>> distribution)
			: generator   (std::move(generator   ))
			, distribution(std::move(distribution))
			{}
};
