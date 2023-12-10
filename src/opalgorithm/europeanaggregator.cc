#include "./europeanaggregator.hh"

#include <cmath>
#include <numeric>

double
EuropeanAggregator::aggregate(Iterator beg, Iterator end) {
	auto sumOptionVals       = std::accumulate(beg, end, 0.0);
	auto meanOptionVal       = sumOptionVals / double(totalSimulations);
	auto discountedOptionVal = std::exp(-returnRate * 1.0) * meanOptionVal; // TODO: Update 1.0 with total time.
	return discountedOptionVal;
}
