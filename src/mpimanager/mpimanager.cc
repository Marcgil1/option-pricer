#include "./mpimanager.hh"

#include <iostream>

void
MpiManager::init() {
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Comm_size(MPI_COMM_WORLD, &numProc);
}

void
MpiManager::finish() {
	MPI_Finalize();
}

int
MpiManager::getPid() {
	return pid;
}

int
MpiManager::getNumProc() {
	return numProc;
}

bool
MpiManager::isMaster() {
	return pid == 0;
}

void
MpiManager::send(double partialResult) {
	auto fd = MPI_Send(&partialResult, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	if (fd != MPI_SUCCESS) {
		logger->err
			<< "Error when sending partial results from "
			<< getPid() << std::endl;
	}
}

void
MpiManager::receiveResults(
	std::back_insert_iterator<Container> it)
{
	for (int pid = 0; pid < numProc; pid++) {
		double     partialResult;
		MPI_Status status; // TODO: Do a more granular study of this variable.

		MPI_Recv(
			&partialResult, 1, MPI_DOUBLE, pid, 0, MPI_COMM_WORLD, &status);
		if (status.MPI_ERROR != MPI_SUCCESS) {
			logger->err
				<< "Error when retrieving partial results from " << pid
				<< std::endl;
		}
		
		it = partialResult;
	}
}
