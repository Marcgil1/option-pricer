#pragma once

#include "../logging/logger.hh"
#include "../opalgorithm/opalgorithm.hh"

#include <memory>


class OpExecutor {
	protected:
		std::unique_ptr<OpAlgorithm> opAlgorithm;
		std::shared_ptr<Logger>      logger;
	public:
		OpExecutor(
			std::unique_ptr<OpAlgorithm> opAlgorithm,
			std::shared_ptr<Logger>      logger)
			: opAlgorithm(std::move(opAlgorithm))
			, logger     (          logger      )
			{}

		virtual double run() = 0;
};
