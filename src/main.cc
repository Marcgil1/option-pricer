#include "logging/logger.hh"
#include "sdesimulator/sdesimulatorfactory.hh"
#include "opalgorithm/europeanopalgorithm.hh"
#include "opexecutor/singlenodeopexecutor.hh"

#include <iostream>
#include <memory>


int main() {
	auto logger =
		std::make_shared<Logger>(
			std::cout, std::cout, std::cerr);
	auto sdeSimulatorFactory =
		std::make_unique<SdeSimulatorFactory>();
	auto opAlgorithm =
		std::make_unique<EuropeanOpAlgorithm>(
			std::move(sdeSimulatorFactory));
	auto opExecutor =
		std::make_unique<SingleNodeOpExecutor>(
			std::move(opAlgorithm),
			logger
		);

	logger->log << "Program starting." << std::endl;
	logger->log << "Correctly instantiated all upper-level objects." << std::endl;

	auto result = opExecutor->run();

	logger->log << "Finished execution." << std::endl;
	logger->out << "Result: " << result << std::endl;

	return 0;
}
