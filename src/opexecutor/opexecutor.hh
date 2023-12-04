#pragma once

#include "../logging/logger.hh"
#include "../opalgorithm/opalgorithm.hh"
#include "../mpimanager/mpimanager.hh"

#include <memory>


class OpExecutor {
	protected:
		std::unique_ptr<OpAlgorithm> opAlgorithm;
		std::shared_ptr<MpiManager>  mpiManager;
		std::shared_ptr<Logger>      logger;
	public:
		OpExecutor(
			std::unique_ptr<OpAlgorithm> opAlgorithm,
			std::shared_ptr<MpiManager>  mpiManager,
			std::shared_ptr<Logger>      logger)
			: opAlgorithm(std::move(opAlgorithm))
			, mpiManager (          mpiManager  )
			, logger     (          logger      )
			{}

		virtual void   run()       = 0;
		virtual double getResult() = 0;
};
