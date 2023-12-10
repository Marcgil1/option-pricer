#include "./mpimanager.hh"

void
MpiManager::init() {
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
}

void
MpiManager::finish() {
	MPI_Finalize();
}

int
MpiManager::getPid() {
	return pid;
}

bool
MpiManager::isMaster() {
	return pid == 0;
}

void
MpiManager::send(double partialResult) {
	// TODO: Implemnt.
}

void
MpiManager::receiveResults(
	std::back_insert_iterator<Container> it)
{
	// TODO: Implement.
}
