#include <dlfcn.h>
#include <vector>

#include "player_api.h"

#include "lexicon/common.h"
#include "module.hpp"
#include "error.hpp"

using namespace module;

typedef struct module_s {
	void * handle;
	bool(*initialize)(handle_t);
	void(*shutdown)(void);
	// Imported Functions Declaration
	#define XMOD_STRUCT
	#include "xmodule.hpp"
	#undef XMOD_STRUCT

} module_t;

static std::vector<module_t> modules;

bool module::load(char const * path) {
	module_t mod;
	mod.handle = dlopen(vas("./modules/%s", path), RTLD_NOW);
	if (!mod.handle) {
		gmerrf(errlev::error, "module \"%s\" does not exist.", path);
		return false;
	}

	mod.initialize = reinterpret_cast<bool (*)(handle_t)>(dlsym(mod.handle, "mod_initialize"));
	if (!mod.initialize) {
		gmerrf(errlev::warning, "module \"%s\" missing function: \"%s\".", path, "mod_initialize");
	}

	mod.shutdown = reinterpret_cast<void (*)(void)>(dlsym(mod.handle, "mod_shutdown"));
	if (!mod.shutdown) {
		gmerrf(errlev::warning, "module \"%s\" missing function: \"%s\".", path, "mod_shutdown");
	}

	// Imported Functions Linking
	#define XMOD_SYM
	#include "xmodule.hpp"
	#undef XMOD_SYM

	if (!mod.initialize || mod.initialize(mod.handle)) {
		modules.push_back(mod);
		return true;
	}

	gmerrf(errlev::error, "module \"%s\" successfully linked, but returned error on initialization.", path);
	dlclose(mod.handle);
	return false;
}

bool module::unload(char const *) {
	return false;
}

void module::shutdown() {
	for (module_t & mod : modules) {
		if (mod.shutdown) mod.shutdown();
		dlclose(mod.handle);
	}
}

#define XMOD_CALL
#include "xmodule.hpp"
#undef XMOD_CALL
