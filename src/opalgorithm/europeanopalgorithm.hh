#pragma once

#include "./aggregator.hh"
#include "./europeanaggregator.hh"
#include "./europeanpartialcalculator.hh"
#include "./partialcalculator.hh"
#include "./opalgorithm.hh"
#include "../sdesimulator/sdesimulator.hh"

#include <memory>


class EuropeanOpAlgorithm : public OpAlgorithm {
	private:
		std::shared_ptr<Aggregator>        aggregator;
		std::shared_ptr<PartialCalculator> partialCalculator;

	public:
		EuropeanOpAlgorithm(
			std::unique_ptr<SdeSimulator> sdeSimulator,
			int                           totalSimulations,
			double                        returnRate)
			: OpAlgorithm      (std::move(sdeSimulator), totalSimulations, returnRate)
			, aggregator       (std::make_shared<EuropeanAggregator>(totalSimulations, returnRate))
			, partialCalculator(std::make_shared<EuropeanPartialCalculator>())
			{}
		
		std::shared_ptr<Aggregator>        getAggregator()        override;
		std::shared_ptr<PartialCalculator> getPartialCalculator() override;
};
