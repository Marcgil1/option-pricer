#pragma once

#include <iterator>
#include <memory>
#include <random>
#include <vector>


class SdeSimulator {
	protected:
		std::unique_ptr<std::mt19937>                     generator;
		std::unique_ptr<std::normal_distribution<double>> distribution;
		std::vector<std::vector<double>>                  rndNums;

		virtual void calcSimulations(
			std::vector<std::vector<double>>& res,
			size_t                            numTrials,
			size_t                            samplesPerTrial) = 0;
	private:
		void calcRandomNumbers(size_t numTrials);
	public:
		SdeSimulator(
			std::unique_ptr<std::mt19937>                     generator,
			std::unique_ptr<std::normal_distribution<double>> distribution)
			: generator   (std::move(generator   ))
			, distribution(std::move(distribution))
			{}

		void simulate(
			std::vector<std::vector<double>>& res,
			size_t                            numTrials,
			size_t                            samplesPerTrial);
};
