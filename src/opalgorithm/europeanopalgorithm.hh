#pragma once

#include "./opalgorithm.hh"
#include "../sdesimulator/sdesimulatorfactory.hh"

#include <memory>

class EuropeanOpAlgorithm : public OpAlgorithm {
	public:
		EuropeanOpAlgorithm(
			std::unique_ptr<SdeSimulatorFactory> sdeSimulatorFactory)
			: OpAlgorithm(std::move(sdeSimulatorFactory))
			{}
};
