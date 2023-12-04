#pragma once

#include "../logging/logger.hh"
#include "../opalgorithm/opalgorithm.hh"
#include "../opexecutor/opexecutor.hh"

#include <memory>


class SingleNodeOpExecutor : OpExecutor {
	public:
		SingleNodeOpExecutor(
			std::unique_ptr<OpAlgorithm> opAlgorithm,
			std::shared_ptr<Logger>      logger)
			: OpExecutor(
				std::move(opAlgorithm),
				logger
			  )
			{}

		double run() override;
};
