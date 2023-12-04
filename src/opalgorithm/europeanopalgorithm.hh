#pragma once

#include "./opalgorithm.hh"
#include "../sdesimulator/sdesimulator.hh"

#include <memory>

class EuropeanOpAlgorithm : public OpAlgorithm {
	public:
		EuropeanOpAlgorithm(
			std::unique_ptr<SdeSimulator> sdeSimulator)
			: OpAlgorithm(std::move(sdeSimulator))
			{}
};
