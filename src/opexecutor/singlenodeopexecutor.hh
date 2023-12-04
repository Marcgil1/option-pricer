#pragma once

#include "../logging/logger.hh"
#include "../opalgorithm/opalgorithm.hh"
#include "../opexecutor/opexecutor.hh"
#include "../mpimanager/mpimanager.hh"

#include <memory>


class SingleNodeOpExecutor : OpExecutor {
	public:
		SingleNodeOpExecutor(
			std::unique_ptr<OpAlgorithm> opAlgorithm,
			std::shared_ptr<MpiManager>  mpiManager,
			std::shared_ptr<Logger>      logger)
			: OpExecutor(
				std::move(opAlgorithm),
				mpiManager,
				logger
			  )
			{}

		void   run()       override;
		double getResult() override;
};
