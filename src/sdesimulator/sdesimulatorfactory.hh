#pragma once

#include "./sdesimulator.hh"

#include <memory>


class SdeSimulatorFactory {
	public:
		static
		std::unique_ptr<SdeSimulator>
		getDefaultSdeSimulator();
};
