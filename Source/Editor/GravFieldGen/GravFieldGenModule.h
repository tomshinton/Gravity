#include <Runtime/Core/Public/Modules/ModuleManager.h>
 
#include "Editor/GravFieldGen/Public/Tool/GravFieldGeneratorTool.h"

class FGravFieldGenModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

	void InitialiseGenerator();
	void InitialiseUI();

	void AddToolbarButton(FToolBarBuilder& Builder);
	TSharedPtr<FUICommandList> ModuleCommands;

	TSharedPtr<FGravFieldGeneratorTool> GenTool;
};

IMPLEMENT_MODULE(FGravFieldGenModule, GravFieldGen)