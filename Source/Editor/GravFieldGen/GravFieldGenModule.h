#include <Runtime/Core/Public/Modules/ModuleManager.h>
 
class FGravFieldGenModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

	void InitialiseGenerator();

	void GenerateField();

	void AddToolbarButton(FToolBarBuilder& Builder);
	TSharedPtr<FUICommandList> ModuleCommands;
};

IMPLEMENT_MODULE(FGravFieldGenModule, GravFieldGen)