#include <Runtime/Core/Public/Modules/ModuleManager.h>
 
class FArenaFrameworkModule : public IModuleInterface
{
	virtual void StartupModule() override { }
	virtual void ShutdownModule() override { }
};

IMPLEMENT_MODULE(FArenaFrameworkModule, ArenaFramework)