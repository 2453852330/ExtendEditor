// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHotKeyActor.h"

// Sets default values
AMyHotKeyActor::AMyHotKeyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMyHotKeyActor::HelloStaticFunction()
{
	UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:This is a Static Test Function"),__FUNCTIONW__,__LINE__);
}

void AMyHotKeyActor::HelloNativeEvent_Implementation()
{
	UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:This is Called from C++"),__FUNCTIONW__,__LINE__);
}
