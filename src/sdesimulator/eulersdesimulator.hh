#pragma once

#include "./sdesimulator.hh"

#include <memory>
#include <random>


class EulerSdeSimulator: public SdeSimulator {
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
