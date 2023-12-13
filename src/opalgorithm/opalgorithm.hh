#pragma once

#include "./aggregator.hh"
#include "./partialcalculator.hh"
#include "../sdesimulator/sdesimulator.hh"

#include <memory>


class OpAlgorithm {
	public:
		virtual std::shared_ptr<Aggregator>        getAggregator()        = 0;
		virtual std::shared_ptr<PartialCalculator> getPartialCalculator() = 0;
};
