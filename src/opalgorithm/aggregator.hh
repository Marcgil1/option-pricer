#pragma once

#include <vector>


typedef std::vector<std::vector<double>>::iterator Iterator;


class Aggregator {
	public:
		virtual double aggregate(Iterator beg, Iterator end) = 0;
};
