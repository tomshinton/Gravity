#pragma once

#include <Runtime/SlateCore/Public/Styling/SlateStyle.h>
#include <Runtime/SlateCore/Public/Styling/SlateStyleRegistry.h>

namespace GravFieldEditorStylePrivate
{
	const FName StyleName = TEXT("GravFieldGen");
}

#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)

class FGravFieldGenEditorStyle : public FSlateStyleSet
{
	public:

	FGravFieldGenEditorStyle()
			: FSlateStyleSet(GravFieldEditorStylePrivate::StyleName)
	{
		const FVector2D Icon40x40(40.0f, 40.0f);

		const FString ContentRoot = (FPaths::GameSourceDir() / "Editor/GravFieldGen/Resources");
		SetContentRoot(ContentRoot);
		SetCoreContentRoot(ContentRoot);

		Set("Icon", new IMAGE_BRUSH("Icon_GenField_64px", Icon40x40));

		FSlateStyleRegistry::RegisterSlateStyle(*this);
	};

	~FGravFieldGenEditorStyle()
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(GravFieldEditorStylePrivate::StyleName);
	}

	static void Get()
	{
		MakeShareable(new FGravFieldGenEditorStyle);
	}
};