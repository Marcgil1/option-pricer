#pragma once

#include "./partialcalculator.hh"


class EuropeanPartialCalculator: public PartialCalculator {
	double run() override;
};
