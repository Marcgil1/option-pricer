#pragma once

#include "../sdesimulator/sdesimulatorfactory.hh"

#include <memory>


class OpAlgorithm {
	protected:
		std::unique_ptr<SdeSimulatorFactory> sdeSimulatorFactory;
	public:
		OpAlgorithm(
			std::unique_ptr<SdeSimulatorFactory> sdeSimulatorFactory)
			: sdeSimulatorFactory(std::move(sdeSimulatorFactory))
			{}
};
