#ifdef XMOD_ENUM
#define XFUNC0(fname) fname,
#define XFUNC1(fname, arg1) fname,
#endif

#ifdef XMOD_STRUCT
#define XFUNC0(fname) void(*fname)( void );
#define XFUNC1(fname, arg1) void(*fname)( arg1 );
#endif

#ifdef XMOD_SYM
#define XFUNC0(fname) \
	imod.fname = reinterpret_cast<void (*)(void)>(dlsym(imod.handle, "mod_"#fname)); \
	if (!imod.fname) { \
		gmerrf(errlev::warning, "module \"%s\" missing function: \"%s\".", path, "mod_"#fname); \
	}
#define XFUNC1(fname, arg1) \
	imod.fname = reinterpret_cast<void (*)(arg1)>(dlsym(imod.handle, "mod_"#fname)); \
	if (!imod.fname) { \
		gmerrf(errlev::warning, "module \"%s\" missing function: \"%s\".", path, "mod_"#fname); \
	}
#endif

#ifdef XMOD_CALL_DEF
#define XFUNC0(fname) void signal_##fname();
#define XFUNC1(fname, arg1) void signal_##fname(arg1);
#endif

#ifdef XMOD_CALL
#define XFUNC0(fname) void module::signal_##fname() { for (module_t & mod : modules) if (mod.fname) mod.fname(); }
#define XFUNC1(fname, arg1) void module::signal_##fname(arg1 a) { for (module_t & mod : modules) if (mod.fname) mod.fname(a); }
#endif

XFUNC0(game_start)
XFUNC0(game_end)


#undef XFUNC0
#undef XFUNC1
