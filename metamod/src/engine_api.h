#pragma once

#include <archtypes.h>

// Plugin's GetEngineFunctions, called by metamod.
typedef int (*GET_ENGINE_FUNCTIONS_FN)(enginefuncs_t *pengfuncsFromEngine, int *interfaceVersion);

// According to SDK engine/eiface.h:
// ONLY ADD NEW FUNCTIONS TO THE END OF THIS STRUCT. INTERFACE VERSION IS FROZEN AT 138
#define ENGINE_INTERFACE_VERSION 138

// Protect against other projects which use this include file but use the
// normal enginefuncs_t type for their meta_engfuncs.
#ifdef METAMOD_CORE
	#include "meta_eiface.h"	// meta_enginefuncs_t
	extern meta_enginefuncs_t meta_engfuncs;
#else
	extern enginefuncs_t meta_engfuncs;
#endif

void compile_engine_callbacks();
