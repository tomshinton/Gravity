#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/Slate/Public/Widgets/Notifications/SNotificationList.h>

class UTexture2D;
class UPackage;

class FGravFieldGeneratorTool
{
public:

	FGravFieldGeneratorTool();

	void StartTool();

private:

	bool GenerateField(UTexture2D& InSourceTexture);
		
	UTexture2D* FindOrCreateTargetTexture();
	bool SaveField(UTexture2D& InSourceTexture);
	void SetFieldSize();

	void Cleanup();

	void PostNotification(const FString& InString);

	uint32 FieldWidth;
	uint32 FieldHeight;

	FString CurrentFieldName;
	UPackage* CurrentPackage;
	uint8* Pixels;

	FNotificationInfo NotificationInfo;
	TWeakPtr<SNotificationItem> Notification;
};