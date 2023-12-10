#pragma once

#include <iterator>
#include <vector>

#include <mpi.h>


typedef std::vector<double> Container;


class MpiManager {
	public:
		MpiManager(): pid(-1) {}

		void init();
		void finish();
		int  getPid();
		int  getNumProc();
		bool isMaster();
		void send(double partialResult);
		void receiveResults(std::back_insert_iterator<Container> it);
	private:
		int pid;
		int numProc;
};
