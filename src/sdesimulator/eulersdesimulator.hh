#pragma once

#include "./sdesimulator.hh"

#include <memory>
#include <random>


class EulerSdeSimulator: public SdeSimulator {
	protected:
		void calcSimulations(
			std::vector<double>& res,
			size_t               numTrials) override;
	private:
		double calcSingleSimulation(size_t trial);
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
