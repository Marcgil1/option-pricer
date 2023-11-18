#pragma once

#include <memory>
#include <random>
#include <vector>

class ExactConstantLinearEuropeanPutPricer {
	public:
		struct Params {
			double alpha = 0.06;
			double beta = 0.3;
			double initialValue = 5;
			double strikePrice = 10.0;
			double totalTime = 1.0;
		};
		
	private:
		std::unique_ptr<std::default_random_engine>       generator;
		std::unique_ptr<std::normal_distribution<double>> distribution;
		Params params;

	public:
		ExactConstantLinearEuropeanPutPricer(
			std::unique_ptr<std::default_random_engine>       generator,
			std::unique_ptr<std::normal_distribution<double>> distribution)
			: generator   (std::move(generator))
			, distribution(std::move(distribution))
			, trialVals   (std::make_unique<std::vector<double>>())
			{}
			
		std::unique_ptr<std::vector<double>>
		calculateTrialVals(unsigned numTrials);

	private:
		std::vector<double>                  rndNums;
		std::unique_ptr<std::vector<double>> trialVals;

		void   calcRandomNumbers   (unsigned numTrials);
		void   calcOptionValuations(unsigned numTrials);
		double calcOptionValuation (double   rnd);
		double calcExactOptionValue(double   w);
};
