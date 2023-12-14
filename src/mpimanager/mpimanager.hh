#pragma once

#include "../logging/logger.hh"

#include <iterator>
#include <memory>
#include <vector>

#include <mpi.h>


typedef std::vector<std::vector<double>> Container;


class MpiManager {
	public:
		MpiManager(
			std::shared_ptr<Logger> logger)
			: logger (logger)
			, pid    (-1)
			, numProc(0)
			{}

		void init();
		void finish();
		int  getPid();
		int  getNumProc();
		bool isMaster();
		void send(std::vector<double> const& partialResult);
		void receiveResults(std::back_insert_iterator<Container> it);
	private:
		int pid;
		int numProc;
		std::shared_ptr<Logger> logger;
};
