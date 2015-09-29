#include <dlfcn.h>
#include <vector>

#include "player_api.h"

#include "lexicon/common.h"
#include "module.hpp"
#include "error.hpp"

using namespace module;

typedef struct module_s {
	void * handle;
	char * name;
	bool(*initialize)(handle_t);
	void(*shutdown)(void);
	// Imported Functions Declaration
	#define XMOD_STRUCT
	#include "xmodule.hpp"
	#undef XMOD_STRUCT
} module_t;

static std::vector<module_t> modules;

static module_t imod;

static inline module_t * find_module(handle_t h) {
	if (imod.handle == h) return &imod;
	for (module_t & mod : modules) if (mod.handle == h) return &mod;
	return nullptr;
}

static inline void close_module(module_t & mod) {
	if (mod.shutdown) mod.shutdown();
	free(mod.name);
	dlclose(mod.handle);
}

bool module::load(char const * path) {
	imod.handle = dlopen(vas("./modules/%s", path), RTLD_NOW);
	if (!imod.handle) {
		gmerrf(errlev::error, "module \"%s\" does not exist.", path);
		return false;
	}

	imod.initialize = reinterpret_cast<bool (*)(handle_t)>(dlsym(imod.handle, "mod_initialize"));
	if (!imod.initialize) {
		gmerrf(errlev::error, "module \"%s\" missing REQUIRED function: \"%s\".", path, "mod_initialize");
		dlclose(imod.handle);
		return false;
	}

	imod.shutdown = reinterpret_cast<void (*)(void)>(dlsym(imod.handle, "mod_shutdown"));
	if (!imod.shutdown) {
		gmerrf(errlev::warning, "module \"%s\" missing function: \"%s\".", path, "mod_shutdown");
	}

	// Imported Functions Linking
	#define XMOD_SYM
	#include "xmodule.hpp"
	#undef XMOD_SYM

	imod.name = reinterpret_cast<char *>(malloc(strlen(path) + 1));
	strcpy(imod.name, path);

	if (imod.initialize(imod.handle)) {
		modules.push_back(imod);
		memset(&imod, 1, sizeof(module_t));
		return true;
	}

	gmerrf(errlev::error, "module \"%s\" successfully linked, but returned error on initialization.", path);
	free(imod.name);
	dlclose(imod.handle);
	memset(&imod, 1, sizeof(module_t));
	return false;
}

bool module::unload(char const * path) {
	for (module_t & mod : modules) if (!strcmp(path, mod.name)) close_module(mod);
	return false;
}

void module::shutdown() {
	for (module_t & mod : modules) {
		close_module(mod);
	}
}

#define XMOD_CALL
#include "xmodule.hpp"
#undef XMOD_CALL

#define gmmodstart(erret...) module_t * mod = find_module(h); if (!mod){ gmerrf(errlev::error, vas("module called GM function with invalid handle (0x%lx).", h)); return erret;}

GMAPIPUBLIC void gm_printf(handle_t h, const char * fmt, ...) {
	gmmodstart();
	va_list va;
	va_start(va, fmt);
	gmerror(errlev::log, vas("%s (0x%lx): %s", mod->name, h, vasa(fmt, va)));
}
