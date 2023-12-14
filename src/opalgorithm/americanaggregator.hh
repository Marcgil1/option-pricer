#pragma once

#include "./aggregator.hh"


class AmericanAggregator: public Aggregator {
	public:
		AmericanAggregator() {}

		double aggregate(Iterator beg, Iterator end) override;
};
