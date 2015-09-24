#include <dlfcn.h>
#include <vector>

#include "lexicon/common.hpp"
#include "module.hpp"
#include "error.hpp"

using namespace module;

typedef struct module_s {
	void * handle;
	void (*init_func)(void);
} module_t;

static std::vector<module_t> modules;

bool module::load(char const * path) {
	module_t mod;
	mod.handle = dlopen(vas("./modules/%s", path), RTLD_NOW);
	if (!mod.handle) {
		gmerror(errlev::error, "%s: module \"%s\" does not exist.", __PRETTY_FUNCTION__, path);
		return false;
	}
	mod.init_func = reinterpret_cast<void (*)(void)>(dlsym(mod.handle, "mod_initialize"));
	if (!mod.init_func) {
		gmerror(errlev::error, "%s: module \"%s\" missing mod_initialize function.", __PRETTY_FUNCTION__, path);
	}
	return true;
}

bool module::unload(char const *) {

}
