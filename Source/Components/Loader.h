#pragma once

// modules
#include "Modules\Assets\Assets.h"
#include "Modules\Drawing.h"
#include "Modules\GameLog.h"
#include "Modules\Intro.h"
#include "Modules\Network.h"
#include "Modules\Patches.h"
#ifdef MP_DEMO
#include "Modules\PrintPatches.h"
#endif
#include "Modules\Stats.h"

namespace Loader
{
	struct Module
	{
		const char* name;
		void (*load)();
		void (*unload)();
	};

#define MAX_MODULES 128 // big number, nobody should EVER have 128 modules
	extern Module g_modules[MAX_MODULES];
	extern int g_moduleCount;

	void RegisterModule(const char* name, void (*load)(), void (*unload)());
	void LoadAllModules();
	void UnloadAllModules();
}

#ifdef SP_DEV
	#define MODULE_NS(name) name::SP_Dev
#elif MP_DEMO
	#define MODULE_NS(name) name::MP_Demo
#else // fallback
	#define MODULE_NS(name) name
#endif

struct ModuleRegistrator
{
	ModuleRegistrator(const char* name, void (*load)(), void (*unload)())
	{
		Loader::RegisterModule(name, load, unload);
	}
};

#define REGISTER_MODULE(name) \
	static ModuleRegistrator _module_##name(#name, MODULE_NS(name)::Load, MODULE_NS(name)::Unload)
