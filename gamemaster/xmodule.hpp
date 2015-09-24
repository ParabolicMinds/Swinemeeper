#ifdef XMOD_STRUCT
#define XFUNC(required, rtype, fname, ...) rtype(*fname)( __VA_ARGS__ );
#endif

#ifdef XMOD_SYM
#define XFUNC(required, rtype, fname, ...) \
	mod.fname = reinterpret_cast<rtype (*)(__VA_ARGS__)>(dlsym(mod.handle, #fname)); \
	if (!mod.fname) { \
		if (required) { \
			gmerror(errlev::error, "%s: module \"%s\" missing required function: \"%s\".", __PRETTY_FUNCTION__, path, #fname); \
			dlclose(mod.handle); \
			return false; \
		} else { \
			gmerror(errlev::warning, "%s: module \"%s\" missing optional function: \"%s\".", __PRETTY_FUNCTION__, path, #fname); \
		} \
	}
#endif

XFUNC(1, void, mod_initialize, void)

#undef XFUNC
