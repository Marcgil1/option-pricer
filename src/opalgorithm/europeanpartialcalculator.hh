#pragma once

#include "./partialcalculator.hh"
#include "../sdesimulator/sdesimulator.hh"

#include <memory>


class EuropeanPartialCalculator: public PartialCalculator {
	public:
		EuropeanPartialCalculator(
			std::unique_ptr<SdeSimulator> sdeSimulator)
			: PartialCalculator(std::move(sdeSimulator))
			{}

		double run() override;
};
