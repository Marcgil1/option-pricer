#pragma once

#include "../sdesimulator/sdesimulator.hh"

#include <memory>


class PartialCalculator {
	protected:
		std::unique_ptr<SdeSimulator> sdeSimulator;
	public:
		PartialCalculator(
			std::unique_ptr<SdeSimulator> sdeSimulator)
			: sdeSimulator(std::move(sdeSimulator))
			{}

		virtual double run() = 0;
};
