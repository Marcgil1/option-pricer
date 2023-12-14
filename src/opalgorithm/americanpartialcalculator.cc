#include "./americanpartialcalculator.hh"

std::vector<double>
AmericanPartialCalculator::run() {
	std::vector<std::vector<double>> valuations;

	sdeSimulator->simulate(
		valuations,
		1,
		NUM_EXERCISE_DATES
	);

	return valuations.front();
}
