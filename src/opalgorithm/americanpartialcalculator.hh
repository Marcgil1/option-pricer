#pragma once

#include "./partialcalculator.hh"
#include "../sdesimulator/sdesimulator.hh"

#include <memory>
#include <vector>


class AmericanPartialCalculator: public PartialCalculator {
	public:
		AmericanPartialCalculator(
			std::unique_ptr<SdeSimulator> sdeSimulator)
			: PartialCalculator(std::move(sdeSimulator))
			{}

		std::vector<double> run() override;
};
