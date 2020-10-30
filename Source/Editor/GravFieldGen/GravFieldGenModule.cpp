#include "Editor/GravFieldGen/GravFieldGenModule.h"
#include "Editor/GravFieldGen/Public/Commands/GravFieldGenCommands.h"
#include "Editor/GravFieldGen/Public/Styles/GravFieldGenEditorStyle.h"

#include <Editor/LevelEditor/Public/LevelEditor.h>

DEFINE_LOG_CATEGORY_STATIC(GravFieldGenLog, Log, All)

void FGravFieldGenModule::StartupModule()
{
	UE_LOG(GravFieldGenLog, Log, TEXT("Spinning up GravFieldGen module"));

	InitialiseGenerator();
	InitialiseUI();
}

void FGravFieldGenModule::ShutdownModule()
{
	UE_LOG(GravFieldGenLog, Log, TEXT("Shutting down GravFieldGen module"));
}

void FGravFieldGenModule::InitialiseGenerator()
{
	GenTool = MakeShareable(new FGravFieldGeneratorTool);
}

void FGravFieldGenModule::InitialiseUI()
{
	if (!GenTool.IsValid())
	{
		UE_LOG(GravFieldGenLog, Error, TEXT("Cannot initialise UI - generator tool in unitialised"));
		return;
	}

	FGravFieldGenEditorStyle::Get();
	FGravFieldGenCommands::Register();

	ModuleCommands = MakeShareable(new FUICommandList);
	ModuleCommands->MapAction(
		FGravFieldGenCommands::Get().GenerateFieldCommand,
		FExecuteAction::CreateRaw(GenTool.Get(), &FGravFieldGeneratorTool::StartTool)
	);

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	TSharedPtr<FExtender> Extender = MakeShareable(new FExtender);
	
	Extender->AddToolBarExtension
	(
		"Compile",
		EExtensionHook::After,
		ModuleCommands,
		FToolBarExtensionDelegate::CreateRaw(this, &FGravFieldGenModule::AddToolbarButton)
	);
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(Extender);
}

void FGravFieldGenModule::AddToolbarButton(FToolBarBuilder& Builder)
{
	const FText NewNodeLabel = FText::FromString("Build Field");
	const FText NewNodeTooltip = FText::FromString("Generate a gravity field for this level and save results to content");
	const FSlateIcon NewNodeIcon = FSlateIcon("GravFieldGen", "Icon");


	Builder.AddToolBarButton(FGravFieldGenCommands::Get().GenerateFieldCommand, NAME_None, NewNodeLabel, NewNodeTooltip, NewNodeIcon);
}
