// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHotKeyFunctionLibrary.h"

void UMyHotKeyFunctionLibrary::PrintMessage()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
	                                 TEXT("StaticFunctionLibraryPrint is triggered. (Shift + Alt + W)"));

	UE_LOG(LogTemp, Warning, TEXT("StaticFunctionLibraryPrint is triggered.(Shift + Alt + W)"))
}
