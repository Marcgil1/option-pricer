#pragma once

#include "./aggregator.hh"
#include "./partialcalculator.hh"
#include "../sdesimulator/sdesimulator.hh"

#include <memory>


class OpAlgorithm {
	protected:
		std::unique_ptr<SdeSimulator> sdeSimulator;
		int                           totalSimulations;
		double                        returnRate;
	public:
		OpAlgorithm(
			std::unique_ptr<SdeSimulator> sdeSimulator,
			int                           totalSimulations,
			double                        returnRate)
			: sdeSimulator    (std::move(sdeSimulator    ))
			, totalSimulations(          totalSimulations )
			, returnRate      (          returnRate       )
			{}
		
		virtual std::shared_ptr<Aggregator>        getAggregator()        = 0;
		virtual std::shared_ptr<PartialCalculator> getPartialCalculator() = 0;
};
