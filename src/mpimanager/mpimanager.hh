#pragma once

#include <mpi.h>


class MpiManager {
	public:
		MpiManager(): pid(-1) {}
		void init();
		void finish();
		int  getPid();
		bool isMaster();
	private:
		int pid;
};
