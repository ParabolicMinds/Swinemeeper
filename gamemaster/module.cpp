#include <dlfcn.h>
#include <vector>

#include "lexicon/common.hpp"
#include "module.hpp"
#include "error.hpp"

using namespace module;

typedef struct module_s {
	void * handle;

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

	// Imported Functions Linking
	#define XMOD_SYM
	#include "xmodule.hpp"
	#undef XMOD_SYM

	if (mod.mod_initialize()) return true;

	gmerrf(errlev::error, "module \"%s\" successfully linked, but returned error on initialization.", path);
	dlclose(mod.handle);
	return false;
}

bool module::unload(char const *) {

}
