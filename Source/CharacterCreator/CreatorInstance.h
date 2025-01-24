// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CreatorInstance.generated.h"

USTRUCT(BlueprintType)
struct FStatBlock
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Creation")
	int strength{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Creation")
	int constitution{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Creation")
	int dexterity{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Creation")
	int intelligence{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Creation")
	int willpower{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Creation")
	int charisma{};

	// Default constructor.

	FStatBlock()
		: strength(0), constitution(0), dexterity(0), intelligence(0), willpower(0), charisma(0)
	{}

	// Custom constructor.

	FStatBlock(int str, int con, int dex, int intll, int wil, int cha)
	{
		strength = str;
		constitution = con;
		dexterity = dex;
		intelligence = intll;
		willpower = wil;
		charisma = cha;
	}
};

USTRUCT(BlueprintType)
struct FPortraits
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Creation")
	TArray<UTexture2D*> portraits{};
};

USTRUCT(BlueprintType)
struct FRace
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Creation")
	FName name{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Creation")
	FText description{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Creation")
	FStatBlock modifiers{};

	FPortraits portraits;
	// Default constructor.

	FRace()
		: name(FName("Race")), description(FText::FromString("Description")), modifiers(FStatBlock())
	{}

	FRace(FName nm, FText desc, FStatBlock mod)
	{
		name = nm;
		description = desc;
		modifiers = mod;
	}
};

USTRUCT(BlueprintType)
struct FBackground
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Creation")
	FName name{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Creation")
	FText description{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Creation")
	FStatBlock modifiers{};

	// Default Constructor.

	FBackground()
		: name(FName("Class")), description(FText::FromString("Description")), modifiers(FStatBlock())
	{}

	FBackground(FName nm, FText desc, FStatBlock mod)
	{
		name = nm;
		description = desc;
		modifiers = mod;
	}
};

/**
 * 
 */
UCLASS()
class CHARACTERCREATOR_API UCreatorInstance : public UGameInstance
{
	GENERATED_BODY()
	
};
