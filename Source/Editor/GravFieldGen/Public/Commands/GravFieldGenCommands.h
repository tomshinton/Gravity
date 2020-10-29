#pragma once

#include <Runtime/Slate/Public/Framework/Commands/Commands.h>
#include <Editor/EditorStyle/Public/EditorStyleSet.h>

class FGravFieldGenCommands : public TCommands<FGravFieldGenCommands>
{
public:

	FGravFieldGenCommands()
		:TCommands<FGravFieldGenCommands>
		(
			TEXT("GravFieldGen"),
			NSLOCTEXT("Contexts", "GravFieldGenCommands", "GravField Generation Commands"),
			NAME_None, 
			FEditorStyle::GetStyleSetName()
		)
	{};

	void RegisterCommands() override;

	TSharedPtr<FUICommandInfo> GenerateFieldCommand;
};
