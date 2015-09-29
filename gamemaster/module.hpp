#ifndef GM_MODULE_HPP
#define GM_MODULE_HPP

namespace module {

	enum class signal_e : unsigned char {
	#define XMOD_ENUM
	#include "xmodule.hpp"
	#undef XMOD_ENUM
	};

	bool load(char const *);
	bool unload(char const *);

	void shutdown();

	#define XMOD_CALL_DEF
	#include "xmodule.hpp"
	#undef XMOD_CALL_DEF

}

#endif //GM_MODULE_HPP
