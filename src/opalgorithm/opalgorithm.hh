#pragma once

#include "./aggregator.hh"
#include "./partialcalculator.hh"
#include "../sdesimulator/sdesimulator.hh"

#include <memory>


class OpAlgorithm {
	protected:
		std::unique_ptr<SdeSimulator> sdeSimulator;
	public:
		OpAlgorithm(
			std::unique_ptr<SdeSimulator> sdeSimulator)
			: sdeSimulator(std::move(sdeSimulator))
			{}
		
		virtual std::shared_ptr<Aggregator>        getAggregator()        = 0;
		virtual std::shared_ptr<PartialCalculator> getPartialCalculator() = 0;
};
