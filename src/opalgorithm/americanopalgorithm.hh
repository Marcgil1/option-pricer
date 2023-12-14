#pragma once

#include "./aggregator.hh"
#include "./americanaggregator.hh"
#include "./americanpartialcalculator.hh"
#include "./partialcalculator.hh"
#include "./opalgorithm.hh"
#include "../sdesimulator/sdesimulator.hh"

#include <memory>


class AmericanOpAlgorithm : public OpAlgorithm {
	private:
		std::shared_ptr<Aggregator>        aggregator;
		std::shared_ptr<PartialCalculator> partialCalculator;

	public:
		AmericanOpAlgorithm(
			std::unique_ptr<SdeSimulator> sdeSimulator)
			: aggregator(
				  std::make_shared<AmericanAggregator>())
			, partialCalculator(
				  std::make_shared<AmericanPartialCalculator>(
					  std::move(sdeSimulator)
				  )
			  )
			{}
		
		std::shared_ptr<Aggregator>        getAggregator()        override;
		std::shared_ptr<PartialCalculator> getPartialCalculator() override;
};
