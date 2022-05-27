#pragma once
#include "base.h"
#include "domain.h"
#include <string>
#include <vector>

namespace bub {

	class validator_exception : public std::exception {
	private:
		std::string _msg;
	public:
		validator_exception(std::string str) : _msg(str) {}
		const char* what() const noexcept override {
			return _msg.c_str();
		}
	};

	class tutorial_validator {
	public:

		void validate(const tutorial& t);

	};

}