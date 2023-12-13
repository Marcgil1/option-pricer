#pragma once

#include "./sdesimulator.hh"

#include <memory>
#include <random>


class EulerSdeSimulator: public SdeSimulator {
	protected:
		void calcSimulations(
			std::vector<std::vector<double>>& res,
			size_t                            numTrials,
			size_t                            samplesPerTrial) override;
	private:
		void calcSingleSimulation(
			std::vector<double>& singlePath,
			size_t               trial,
			size_t               samplesPerTrial);
	public:
		EulerSdeSimulator(
			std::unique_ptr<std::mt19937>                     generator,
			std::unique_ptr<std::normal_distribution<double>> distribution)
			: SdeSimulator(
				  std::move(generator   ),
				  std::move(distribution)
			  )
			{}
};
