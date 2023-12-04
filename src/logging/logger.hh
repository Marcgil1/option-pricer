#pragma once

#include <ostream>


struct Logger {
	std::ostream& out;
	std::ostream& log;
	std::ostream& err;

	Logger() = delete;

	Logger(
		std::ostream& out,
		std::ostream& log,
		std::ostream& err)
		: out(out)
		, log(log)
		, err(err)
		{}
};
