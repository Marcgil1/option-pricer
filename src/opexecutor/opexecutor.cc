#include "../opexecutor/opexecutor.hh"

#include <iterator>
#include <vector>


void
OpExecutor::run() {
	auto partialCalculator =
		opAlgorithm->getPartialCalculator();

	mpiManager->send(
		partialCalculator->run()
	);
}

double
OpExecutor::getResult() {
	if (not mpiManager->isMaster())
		return -1;

	auto aggregator = opAlgorithm->getAggregator();
	auto results    = std::vector<double>();
	mpiManager->receiveResults(
		std::back_inserter(results)
	);

	return opAlgorithm
		->getAggregator()
		->aggregate(
			std::begin(results),
			std::end  (results)
		);
}
