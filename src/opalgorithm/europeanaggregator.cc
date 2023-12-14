#include "../params.hh"
#include "./europeanaggregator.hh"

#include <cmath>
#include <numeric>


double
EuropeanAggregator::aggregate(Iterator beg, Iterator end) {
	double sumOptionVals = 0.0;
	for (auto it = beg; it != end; it++)
		sumOptionVals += it->front();

	auto meanOptionVal       = sumOptionVals / double(totalSimulations);
	auto discountedOptionVal = std::exp(-returnRate * TOTAL_TIME) * meanOptionVal;
	return discountedOptionVal;
}
