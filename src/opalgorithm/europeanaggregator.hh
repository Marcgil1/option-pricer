#pragma once

#include "./aggregator.hh"


class EuropeanAggregator: public Aggregator {
	private:
		int    totalSimulations;
		double returnRate;
	public:
		EuropeanAggregator(
			int    totalSimulations,
			double returnRate)
			: totalSimulations(totalSimulations)
			, returnRate      (returnRate      )
			{}

		double aggregate(Iterator beg, Iterator end) override;
};
