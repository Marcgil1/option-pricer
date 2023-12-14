#include "params.hh"
#include "logging/logger.hh"
#include "mpimanager/mpimanager.hh"
#ifdef MK_EUROPEAN
#include "opalgorithm/europeanopalgorithm.hh"
#else
#include "opalgorithm/americanopalgorithm.hh"
#endif
#include "opexecutor/opexecutor.hh"
#include "sdesimulator/eulersdesimulator.hh"

#include <iostream>
#include <memory>
#include <random>


int main() {
	auto logger =
		std::make_shared<Logger>(
			std::cout, std::cout, std::cerr);
	auto mpiManager =
		std::make_shared<MpiManager>(logger);

	mpiManager->init();

	auto generator =
		std::make_unique<std::mt19937>(mpiManager->getPid());
	auto distribution =
		std::make_unique<std::normal_distribution<double>>();
	auto sdeSimulator =
		std::make_unique<EulerSdeSimulator>(
			std::move(generator),
			std::move(distribution));
	#ifdef MK_EUROPEAN
	auto opAlgorithm =
		std::make_unique<EuropeanOpAlgorithm>(
			std::move(sdeSimulator),
			NUM_TRIALS * mpiManager->getNumProc(),
			RETURN_RATE);
	#else
	auto opAlgorithm =
		std::make_unique<AmericanOpAlgorithm>(
			std::move(sdeSimulator));
	#endif
	auto opExecutor =
		std::make_unique<OpExecutor>(
			std::move(opAlgorithm),
			mpiManager,
			logger
		);


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
