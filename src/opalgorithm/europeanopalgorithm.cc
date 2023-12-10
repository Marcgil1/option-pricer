#include "./europeanopalgorithm.hh"

#include "./europeanaggregator.hh"
#include "./europeanpartialcalculator.hh"


std::shared_ptr<Aggregator>
EuropeanOpAlgorithm::getAggregator() {
	return std::make_shared<EuropeanAggregator>();
}

std::shared_ptr<PartialCalculator>
EuropeanOpAlgorithm::getPartialCalculator() {
	return std::make_shared<EuropeanPartialCalculator>();
}
