#include "validator.h"
#include <string>

namespace bub {

	void tutorial_validator::validate(const tutorial& t) {

		if (t.get_duration().m < 0 || t.get_duration().s < 0)
			throw bub::validator_exception("Duration min/sec cannot be negative");
		if (t.get_likes() < 0)
			throw bub::validator_exception("Like count cannot be negative");

	}

}