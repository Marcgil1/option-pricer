#pragma once

#include "../sdesimulator/sdesimulator.hh"

#include <memory>
#include <vector>


class PartialCalculator {
	protected:
		std::unique_ptr<SdeSimulator> sdeSimulator;
	public:
		PartialCalculator(
			std::unique_ptr<SdeSimulator> sdeSimulator)
			: sdeSimulator(std::move(sdeSimulator))
			{}

		virtual std::vector<double> run() = 0;
};
