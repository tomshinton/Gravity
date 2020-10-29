#include "Editor/GravFieldGen/Public/Commands/GravFieldGenCommands.h"

#define LOCTEXT_NAMESPACE "FGravFieldGenCommands"

void FGravFieldGenCommands::RegisterCommands()
{
	UI_COMMAND(GenerateFieldCommand, "GenerateField", "Generate a gravity field for this level", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
