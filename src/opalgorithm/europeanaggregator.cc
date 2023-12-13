#include "../params.hh"
#include "./europeanaggregator.hh"

#include <cmath>
#include <numeric>


double
EuropeanAggregator::aggregate(Iterator beg, Iterator end) {
	auto sumOptionVals       = std::accumulate(beg, end, 0.0);
	auto meanOptionVal       = sumOptionVals / double(totalSimulations);
	auto discountedOptionVal = std::exp(-returnRate * TOTAL_TIME) * meanOptionVal;
	return discountedOptionVal;
}
