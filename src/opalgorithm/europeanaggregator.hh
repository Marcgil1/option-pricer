#include "./aggregator.hh"

class EuropeanAggregator: public Aggregator {
	public:
		double aggregate(Iterator beg, Iterator end) override;
};
