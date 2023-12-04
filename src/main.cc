#include "logging/logger.hh"
#include "sdesimulator/sdesimulatorfactory.hh"
#include "opalgorithm/europeanopalgorithm.hh"
#include "opexecutor/singlenodeopexecutor.hh"

#include <iostream>
#include <memory>


int main() {
	auto logger =
		std::make_shared<Logger>(
			std::cout, std::cout, std::cerr);

	logger->log << "Program starting." << std::endl;
	logger->log << "Correctly instantiated all upper-level objects." << std::endl;


	logger->log << "Finished execution." << std::endl;

	return 0;
}
