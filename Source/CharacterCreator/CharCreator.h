// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CreatorInstance.h"
#include "CharCreator.generated.h"

UCLASS()
class CHARACTERCREATOR_API ACharCreator : public AActor
{
	GENERATED_BODY()
	
protected:

	// Main directories.

	FString dataDir{};					// Data
	FString raceDir{};					// Data / Races
	FString rStatsDir{};				// Data / Races / Stats
	FString rPortraitsDir{};			// Data / Races / Portraits
	FString classDir{};					// Data / Classes
	FString classStatsDir{};			// Data / Classes / Stats

	// Race Directories.

	FString rAktiin{};					// Data / Races / Aktiin
	FString rAradiin{};					// Data / Races / Aradiin
	FString rLunath{};					// Data / Races / Lunath
	FString rSiron{};					// Data / Races / Siron
	FString rZerath{};					// Data / Races / Zerath

	TMap<TCHAR, int> modInt
	{
		{'+', 2},
		{'0', 0},
		{'-', -2}
	};

	virtual void BeginPlay() override;

	// Defaults.

	void PopulateRaceDefaults();
	void PopulateClassDefaults();
	void PopulateStatDefaults();
	void PopulatePortraitDefaults();

	// Data

	void ReadRaces();
	void ReadClasses();
	void ReadPortraits();

	// Utility.

	void CreateDirectory(FString dirName);
	void MakeTextFile(FString content, FString filePath);
	void MakePNG(UTexture2D* texture, FString filePath);
	UTexture2D* MakeTexture(FString filePath);
	FStatBlock MakeStatBlock(FString content);
	void MakeRace(FString raceFile, FString statsFile);
	void MakeClass(FString classFile, FString statsFile);

	void StartCharacterCreation();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Creation")
	TArray<UTexture2D*> portraitList{};					// Possibly delete.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Creation")
	TArray<FName> defaultRaceNames{};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Creation")
	TArray<FName> raceNames{};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Creation")
	TArray<FName> classNames{};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Creation")
	TMap<FName, FRace> raceRegistry{};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Creation")
	TMap<FName, FBackground> classRegistry{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Creation")
	TMap<FName, FPortraits> portraitRegistry{};

	// Stats

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Creation")
	TMap<FName, FStatBlock> raceBonuses{};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Creation")
	TMap<FName, FStatBlock> classBonuses{};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Creation")
	FStatBlock bonus{};

	ACharCreator();
	virtual void Tick(float DeltaTime) override;
	void InitializeDataFiles();
};
