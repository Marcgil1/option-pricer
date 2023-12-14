#include "./americanopalgorithm.hh"

std::shared_ptr<Aggregator>
AmericanOpAlgorithm::getAggregator() {
	return aggregator;
}

std::shared_ptr<PartialCalculator>
AmericanOpAlgorithm::getPartialCalculator() {
	return partialCalculator;
}
