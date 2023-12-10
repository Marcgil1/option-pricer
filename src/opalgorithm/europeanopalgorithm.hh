#pragma once

#include "./aggregator.hh"
#include "./partialcalculator.hh"
#include "./opalgorithm.hh"
#include "../sdesimulator/sdesimulator.hh"

#include <memory>

class EuropeanOpAlgorithm : public OpAlgorithm {
	public:
		EuropeanOpAlgorithm(
			std::unique_ptr<SdeSimulator> sdeSimulator)
			: OpAlgorithm(std::move(sdeSimulator))
			{}
		
		std::shared_ptr<Aggregator>        getAggregator()        override;
		std::shared_ptr<PartialCalculator> getPartialCalculator() override;
};
