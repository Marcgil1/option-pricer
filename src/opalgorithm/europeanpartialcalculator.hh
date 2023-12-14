#pragma once

#include "./partialcalculator.hh"
#include "../sdesimulator/sdesimulator.hh"

#include <memory>
#include <vector>


class EuropeanPartialCalculator: public PartialCalculator {
	public:
		EuropeanPartialCalculator(
			std::unique_ptr<SdeSimulator> sdeSimulator)
			: PartialCalculator(std::move(sdeSimulator))
			{}

		std::vector<double> run() override;
};
