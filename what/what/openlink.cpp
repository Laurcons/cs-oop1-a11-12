#include "openlink.h"

#ifdef _WIN32
#	include <Windows.h>
#else
#	include <cstdlib>
#endif

namespace bub {

#ifdef _WIN32

	void open_link(std::string link) {
		system(("explorer \"" + link + "\"").c_str());
	}

#else

	void open_link(std::string link) {
		system(("firefox \"" + link + "\"").c_str());
	}

#endif

}