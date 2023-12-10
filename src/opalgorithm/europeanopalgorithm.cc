#include "./europeanopalgorithm.hh"

#include "./europeanaggregator.hh"
#include "./europeanpartialcalculator.hh"


std::shared_ptr<Aggregator>
EuropeanOpAlgorithm::getAggregator() {
	return aggregator;
}

std::shared_ptr<PartialCalculator>
EuropeanOpAlgorithm::getPartialCalculator() {
	return partialCalculator;
}
