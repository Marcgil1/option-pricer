#include <functional>
#include <iostream>
#include <numeric>
#include <memory>
#include <random>
#include <vector>

#include <mpi.h>
#include <omp.h>

#include "optionPricerFactory.hh"

int    numTrials  = 10000;
double returnRate = 0.06;

void aggregatePartialResults(double ownSumOptionVals, int numProc) {
	double sumOptionVals = ownSumOptionVals;

	for (int pid = 1; pid < numProc; pid++) {
		double     partialOptionVal;
		MPI_Status status; // TODO: Do a more granular study of this variable.

		MPI_Recv(&partialOptionVal, 1, MPI_DOUBLE, pid, 0, MPI_COMM_WORLD, &status);
		if (status.MPI_ERROR != MPI_SUCCESS) {
			std::cerr << "Error when retrieving partial results from " << pid << std::endl;
		}
		sumOptionVals += partialOptionVal;
	}
	
	auto meanOptionVal       = sumOptionVals / double(numProc * numTrials);
	auto discountedOptionVal = std::exp(-returnRate * 1.0) * meanOptionVal;

	std::cout << discountedOptionVal << std::endl;
}

void sendPartialResults(double sumOptionVals, int pid) {
	auto fd = MPI_Send(&sumOptionVals, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	if (fd != MPI_SUCCESS) {
		std::cerr << "Error when sending partial results from " << pid << std::endl;
	}
}

int main() {
	MPI_Init(NULL, NULL); // TODO: Encapsulate all MPI functionality into a messenger class.
	int pid;     MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	int numProc; MPI_Comm_size(MPI_COMM_WORLD, &numProc);

	// TODO: Implement dependency injection with these variables.
	// TODO: Investigate why the random engine is ignoring its seed.
	auto generator    = std::make_unique<std::default_random_engine>(pid);
	auto distribution = std::make_unique<std::normal_distribution<double>>(0.0, 1.0);
	auto optionPricer = OptionPricerFactory::getDefaultOptionPricer();

	auto optionVals =
		optionPricer->calculateTrialVals(numTrials);
	auto sumOptionVals =
		std::accumulate(
			optionVals->begin(),
			optionVals->end(), 0.0);

	if (pid == 0) {
		aggregatePartialResults(sumOptionVals, numProc);
	} else {
		sendPartialResults(sumOptionVals, pid);
	}

	MPI_Finalize();
}
