#pragma once

#include "../sdesimulator/sdesimulator.hh"

#include <memory>


class OpAlgorithm {
	protected:
		std::unique_ptr<SdeSimulator> sdeSimulator;
	public:
		OpAlgorithm(
			std::unique_ptr<SdeSimulator> sdeSimulator)
			: sdeSimulator(std::move(sdeSimulator))
			{}
};
