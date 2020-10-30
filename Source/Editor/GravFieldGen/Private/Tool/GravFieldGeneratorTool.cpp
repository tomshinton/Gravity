#include "Editor/GravFieldGen/Public/Tool/GravFieldGeneratorTool.h"

#include <Runtime/AssetRegistry/Public/AssetRegistryModule.h>
#include <Runtime/ArenaFramework/Public/Arena.h>
#include <Runtime/Engine/Classes/Engine/Texture2D.h>
#include <Runtime/Engine/Public/EngineUtils.h>
#include <Runtime/Slate/Public/Framework/Notifications/NotificationManager.h>

DEFINE_LOG_CATEGORY_STATIC(GravFieldGeneratorToolLog, Log, Log)

namespace GenToolPrivate
{
	const FString PackageName = TEXT("/Game/GravityFields/");
}

FGravFieldGeneratorTool::FGravFieldGeneratorTool()
	: NotificationInfo(FText::FromString(TEXT("Test Notification")))
{
	NotificationInfo.bUseThrobber = false;
	NotificationInfo.bFireAndForget = true;
	NotificationInfo.FadeOutDuration = 3.f;
	NotificationInfo.ExpireDuration = 3.f;
}

void FGravFieldGeneratorTool::StartTool()
{
	UE_LOG(GravFieldGeneratorToolLog, Log, TEXT("Generating"));
	
	if (UTexture2D* SourceTexture = FindOrCreateTargetTexture())
	{
		if (GenerateField(*SourceTexture))
		{
			if (SaveField(*SourceTexture))
			{
				PostNotification(FString::Printf(TEXT("Field generated for %s"), *CurrentFieldName));
			}
			else
			{
				PostNotification(FString::Printf(TEXT("Generation succeeded, but could not save field for %s"), *CurrentFieldName));
			}

			Cleanup();
		}
		else
		{
			PostNotification(FString::Printf(TEXT("Failed to generate field for %s"), *CurrentFieldName));
		}
	}
	else
	{
		PostNotification(TEXT("Could not find or generate texture for current level"));
		UE_LOG(GravFieldGeneratorToolLog, Error, TEXT("Could not find or generate texture for Level"));
	}
}

void FGravFieldGeneratorTool::SetFieldSize()
{
	for (TActorIterator<AArena> Itr(GWorld); Itr; ++Itr)
	{
		if (AArena* Arena = *Itr)
		{
			FieldWidth = FMath::RoundToInt(Arena->ArenaWidth);
			FieldHeight = FMath::RoundToInt(Arena->ArenaHeight);
		}
	}
}

void FGravFieldGeneratorTool::Cleanup()
{
	FieldWidth = 0;
	FieldWidth = 0;

	CurrentFieldName = "";
	CurrentPackage = nullptr;

	delete[] Pixels;
}

void FGravFieldGeneratorTool::PostNotification(const FString& InString)
{
	NotificationInfo.Text = FText::FromString(InString);
	Notification = FSlateNotificationManager::Get().AddNotification(NotificationInfo);
}

bool FGravFieldGeneratorTool::GenerateField(UTexture2D& InSourceTexture)
{
	SetFieldSize();

	if (FieldWidth <= 0 || FieldHeight <= 0)
	{
		return false;
	}

	InSourceTexture.AddToRoot();
	InSourceTexture.PlatformData = new FTexturePlatformData();
	InSourceTexture.PlatformData->SizeX = FieldWidth;
	InSourceTexture.PlatformData->SizeY = FieldHeight;
	InSourceTexture.PlatformData->NumSlices = 1;
	InSourceTexture.PlatformData->PixelFormat = EPixelFormat::PF_B8G8R8A8;

	InSourceTexture.MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;

	//Generate source pixel data
	Pixels = new uint8[FieldWidth * FieldHeight * 4];
	for (uint32 y = 0; y < FieldHeight; ++y)
	{
		for (uint32 x = 0; x < FieldWidth; ++x)
		{
			int32 curPixelIndex = ((y * FieldWidth) + x);
			Pixels[4 * curPixelIndex] = FMath::RandRange(0.f, 255.f); //Blue
			Pixels[4 * curPixelIndex + 1] = FMath::RandRange(0.f, 255.f); //Green
			Pixels[4 * curPixelIndex + 2] = FMath::RandRange(0.f, 255.f); //Red
			Pixels[4 * curPixelIndex + 3] = 1.f; //Alpha
		}
	}

	//Generate first mip
	FTexture2DMipMap* Mip = new FTexture2DMipMap();
	//InSourceTexture.PlatformData->Mips.Add(Mip);
	Mip->SizeX = FieldWidth;
	Mip->SizeY = FieldHeight;

	Mip->BulkData.Lock(LOCK_READ_WRITE);
	uint8* TextureData = (uint8*)Mip->BulkData.Realloc(FieldWidth * FieldHeight * 4);
	FMemory::Memcpy(TextureData, Pixels, sizeof(uint8) * FieldHeight * FieldWidth * 4);
	Mip->BulkData.Unlock();

	return true;
}

UTexture2D* FGravFieldGeneratorTool::FindOrCreateTargetTexture()
{
	if (UWorld* World = GWorld)
	{
		CurrentFieldName = World->GetMapName() + "_GF";
		CurrentPackage = CreatePackage(NULL, *(GenToolPrivate::PackageName + CurrentFieldName));
		CurrentPackage->FullyLoad();

		return NewObject<UTexture2D>(CurrentPackage, *CurrentFieldName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
	}

	return nullptr;
}

bool FGravFieldGeneratorTool::SaveField(UTexture2D& InSourceTexture)
{
	//Init with 0 mips on purpose - supports non-binary sized arenas, as well as preserves resolution at all times
	InSourceTexture.Source.Init(FieldWidth, FieldHeight, 1, 1, ETextureSourceFormat::TSF_BGRA8, Pixels);

	InSourceTexture.UpdateResource();
	CurrentPackage->MarkPackageDirty();
	FAssetRegistryModule::AssetCreated(&InSourceTexture);

	const FString PackageFileName = FPackageName::LongPackageNameToFilename(GenToolPrivate::PackageName + CurrentFieldName, FPackageName::GetAssetPackageExtension());
	bool Success = UPackage::SavePackage(CurrentPackage, &InSourceTexture, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName, GError, nullptr, true, true, SAVE_NoError);

	return true;
}
