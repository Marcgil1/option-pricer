#include "logging/logger.hh"
#include "mpimanager/mpimanager.hh"
#include "opalgorithm/europeanopalgorithm.hh"
#include "opexecutor/singlenodeopexecutor.hh"
#include "sdesimulator/eulersdesimulator.hh"

#include <iostream>
#include <memory>
#include <random>


int main() {
	auto mpiManager =
		std::make_shared<MpiManager>();
	auto logger =
		std::make_shared<Logger>(
			std::cout, std::cout, std::cerr);
	auto generator =
		std::make_unique<std::mt19937>(mpiManager->getPid());
	auto distribution =
		std::make_unique<std::normal_distribution<double>>();
	auto sdeSimulator =
		std::make_unique<EulerSdeSimulator>(
			std::move(generator),
			std::move(distribution));
	auto opAlgorithm =
		std::make_unique<EuropeanOpAlgorithm>(
			std::move(sdeSimulator));
	auto opExecutor =
		std::make_unique<SingleNodeOpExecutor>(
			std::move(opAlgorithm),
			mpiManager,
			logger
		);

	mpiManager->init();

	if (mpiManager->isMaster()) {
		logger->log << "Program starting." << std::endl;
		logger->log << "Correctly instantiated all upper-level objects." << std::endl;
	}

	opExecutor->run();

	if (mpiManager->isMaster()) {
		auto result = opExecutor->getResult();

		logger->log << "Finished execution." << std::endl;
		logger->out << "Result: " << result << std::endl;
	}

	mpiManager->finish();

	return 0;
}
