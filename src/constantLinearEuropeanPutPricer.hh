#pragma once

#include <memory>
#include <random>
#include <vector>

#include <omp.h>

class ConstantLinearEuropeanPutPricer {
	public:
		struct Params {
			double alpha = 0.06;
			double beta = 0.3;
			double initialValue = 5;
			double strikePrice = 10.0;
			double totalTime = 1.0;
			unsigned numSteps = 1000;
			double   stepSize = totalTime / double(numSteps);
		};

		std::unique_ptr<std::vector<double>>
		calculateTrialVals(unsigned numTrials);

		ConstantLinearEuropeanPutPricer()
			: generator   (std::make_unique<std::default_random_engine>())
			, distribution(std::make_unique<std::normal_distribution<double>>())
			, trialVals   (std::make_unique<std::vector<double>>())
			{}

	protected:
		std::unique_ptr<std::default_random_engine>       generator;
		std::unique_ptr<std::normal_distribution<double>> distribution;

		std::unique_ptr<std::vector<double>> trialVals;
		std::vector<std::vector<double>>     rndNums;
		Params params;

		virtual double calcStockValuation(unsigned trial) = 0;

	private:
		void   calcRandomNumbers   (unsigned numTrials);
		void   calcOptionValuations(unsigned numTrials);
		double calcOptionValuation (unsigned trial);

};
