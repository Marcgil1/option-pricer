#include "./sdesimulatorfactory.hh"

#include "./eulersdesimulator.hh"


std::unique_ptr<SdeSimulator>
SdeSimulatorFactory::getDefaultSdeSimulator() {
	return std::make_unique<EulerSdeSimulator>();
}
