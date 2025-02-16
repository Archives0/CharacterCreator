// Fill out your copyright notice in the Description page of Project Settings.


#include "CharCreator.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/Paths.h"
#include "Modules/ModuleManager.h"
#include "ImageUtils.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"

ACharCreator::ACharCreator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACharCreator::BeginPlay()
{
	Super::BeginPlay();
	StartCharacterCreation();
}

// Called every frame
void ACharCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// TODO: Add race and stat bonuses. Refactor repitition into functions.

void ACharCreator::StartCharacterCreation()
{
	InitializeDataFiles();
	ReadRaces();
	ReadClasses();
	ReadPortraits();

	// UE_LOG(LogTemp, Display, TEXT("Data directory created at: %s"), *dataDir);
}

void ACharCreator::InitializeDataFiles()
{
	// Initialize Data directory.

	FString launchDir = FPaths::LaunchDir();
	dataDir = launchDir / "Data";
	raceDir = dataDir / "Races";
	rStatsDir = raceDir / "Stats";
	rPortraitsDir = raceDir / "Portraits";
	classDir = dataDir / "Classes";
	classStatsDir = classDir / "Stats";

	CreateDirectory(dataDir);
	CreateDirectory(raceDir);
	CreateDirectory(classDir);
	CreateDirectory(rStatsDir);
	CreateDirectory(rPortraitsDir);
	CreateDirectory(classStatsDir);

	// Initialize race portrait directories.

	rAktiin = rPortraitsDir / "Aktiin";
	rAradiin = rPortraitsDir / "Aradiin";
	rLunath = rPortraitsDir / "Lunath";
	rSiron = rPortraitsDir / "Siron";
	rZerath = rPortraitsDir / "Zerath";

	CreateDirectory(rAktiin);
	CreateDirectory(rAradiin);
	CreateDirectory(rLunath);
	CreateDirectory(rSiron);
	CreateDirectory(rZerath);

	// Populate default data.

	PopulateRaceDefaults();
	PopulateClassDefaults();
	PopulateStatDefaults();
	PopulatePortraitDefaults();
}

void ACharCreator::PopulateRaceDefaults()
{
	if (!FPaths::DirectoryExists(raceDir))
	{
		UE_LOG(LogTemp, Error, TEXT("Races directory does not exist. Aborting."));
		return;
	}

	TArray<FString> fileNames{};
	IFileManager::Get().FindFiles(fileNames, *raceDir, TEXT("*.txt"));

	// If default file is not present, add it to Data/Races.

	if (!fileNames.Contains("Aktiin.txt"))
	{
		FString name = raceDir / "Aktiin.txt";
		FString description = "The predominant race of the continent Hla'Aktina. Their ingenuity has led to the rapid industrialization of the continent. Receive bonuses to Intelligence and Dexterity.";
		MakeTextFile(description, name);
	}

	if (!fileNames.Contains("Aradiin.txt"))
	{
		FString name = raceDir / "Aradiin.txt";
		FString description = "Their durable nature has allowed them to survive many hardships and equips them with ample skill for nearly any situation. Receive bonuses to Dexterity and Constitution.";
		MakeTextFile(description, name);
	}

	if (!fileNames.Contains("Lunath.txt"))
	{
		FString name = raceDir / "Lunath.txt";
		FString description = "Lunathi tend to be unconcerned with life on the ground, with many living in ancient floating cities. Their skill in magic is beaten by none. Receive bonuses to Willpower and Intelligence.";
		MakeTextFile(description, name);
	}

	if (!fileNames.Contains("Siron.txt"))
	{
		FString name = raceDir / "Siron.txt";
		FString description = "The predominant race of the eastern continent Enteril. They tend to lead virtuos lives and quest to prove themselves. Receive bonuses to Strength and Constitution.";
		MakeTextFile(description, name);
	}

	if (!fileNames.Contains("Zerath.txt"))
	{
		FString name = raceDir / "Zerath.txt";
		FString description = "Their subterranean lifestyle has made them a widespread race. Most serve as drones, and receive number designations as names. Receive bonuses to Strength and Willpower.";
		MakeTextFile(description, name);
	}
}

void ACharCreator::PopulateClassDefaults()
{
	if (!FPaths::DirectoryExists(classDir))
	{
		UE_LOG(LogTemp, Error, TEXT("Stats directory does not exist. Aborting."));
		return;
	}

	TArray<FString> fileNames{};
	IFileManager::Get().FindFiles(fileNames, *classDir, TEXT("*.txt"));

	// If default files not present, add it to Data/Classes

	if (!fileNames.Contains("Bandit.txt"))
	{
		FString name = classDir / "Bandit.txt";
		FString description = "You make your living from taking from others. A life of thuggery has improved your ability to impose yourself over others. Receives bonsues to Strength and Charisma.";
		MakeTextFile(description, name);
	}

	if (!fileNames.Contains("Commoner.txt"))
	{
		FString name = classDir / "Commoner.txt";
		FString description = "You have thus led a simple and humble life. Only recently have you started on the path of the ashlander. Receives no bonuses or detriments.";
		MakeTextFile(description, name);
	}

	if (!fileNames.Contains("Merchant.txt"))
	{
		FString name = classDir / "Merchant.txt";
		FString description = "You have made your living by selling goods to others, making you skilled in trade. Receives bonuses to Willpower and Charisma.";
		MakeTextFile(description, name);
	}

	if (!fileNames.Contains("Noble.txt"))
	{
		FString name = classDir / "Noble.txt";
		FString description = "You have led your life through high society. Your upbringing has made you skilled in socializing and well studied. Receives bonuses to Charisma and Intelligence.";
		MakeTextFile(description, name);
	}

	if (!fileNames.Contains("Priest.txt"))
	{
		FString name = classDir / "Priest.txt";
		FString description = "You have lived a pious life in worship of your gods. Their blessings have have taught you to be resistant to the will of others. Receives bonuses to Willpower and Constitution.";
		MakeTextFile(description, name);
	}

	if (!fileNames.Contains("Scholar.txt"))
	{
		FString name = classDir / "Scholar.txt";
		FString description = "You have dedicated much of your life to intellectual pursuits. Your studies have familiarized you with magic and its workings. Receives bonuses to Intelligence and Willpower.";
		MakeTextFile(description, name);
	}
}

void ACharCreator::PopulateStatDefaults()
{
	// Populate race stat bonuses.

	if (!FPaths::DirectoryExists(rStatsDir))
	{
		UE_LOG(LogTemp, Error, TEXT("Race stats directory does not exist. Aborting."));
		return;
	}

	TArray<FString> rNames{};
	IFileManager::Get().FindFiles(rNames, *rStatsDir, TEXT("*.txt"));

	// If default file is not present, add it to Data/Races/Stats.

	if (!rNames.Contains("Aktiin.txt"))
	{
		FString name = rStatsDir / "Aktiin.txt";
		FString description = "0|0|+|+|0|0";
		MakeTextFile(description, name);
	}

	if (!rNames.Contains("Aradiin.txt"))
	{
		FString name = rStatsDir / "Aradiin.txt";
		FString description = "0|+|+|0|0|0";
		MakeTextFile(description, name);
	}

	if (!rNames.Contains("Lunath.txt"))
	{
		FString name = rStatsDir / "Lunath.txt";
		FString description = "0|0|0|+|+|0";
		MakeTextFile(description, name);
	}

	if (!rNames.Contains("Siron.txt"))
	{
		FString name = rStatsDir / "Siron.txt";
		FString description = "+|+|0|0|0|0";
		MakeTextFile(description, name);
	}

	if (!rNames.Contains("Zerath.txt"))
	{
		FString name = rStatsDir / "Zerath.txt";
		FString description = "+|0|0|0|+|0";
		MakeTextFile(description, name);
	}

	// Populate class stat bonuses.

	if (!FPaths::DirectoryExists(classStatsDir))
	{
		UE_LOG(LogTemp, Error, TEXT("Background stats directory does not exist. Aborting."));
		return;
	}

	TArray<FString> cNames{};
	IFileManager::Get().FindFiles(cNames, *classStatsDir, TEXT("*.txt"));

	// If defualt file is not present, add it to Data/Classes/Stats

	if (!cNames.Contains("Bandit.txt"))
	{
		FString name = classStatsDir / "Bandit.txt";
		FString description = "0|0|+|0|0|+";
		MakeTextFile(description, name);
	}

	if (!cNames.Contains("Commoner.txt"))
	{
		FString name = classStatsDir / "Commoner.txt";
		FString description = "0|0|0|0|0|0";
		MakeTextFile(description, name);
	}

	if (!cNames.Contains("Merchant.txt"))
	{
		FString name = classStatsDir / "Merchant.txt";
		FString description = "0|0|0|0|+|+";
		MakeTextFile(description, name);
	}

	if (!cNames.Contains("Noble.txt"))
	{
		FString name = classStatsDir / "Noble.txt";
		FString description = "0|0|0|+|0|+";
		MakeTextFile(description, name);
	}

	if (!cNames.Contains("Priest.txt"))
	{
		FString name = classStatsDir / "Priest.txt";
		FString description = "0|0|0|0|+|+";
		MakeTextFile(description, name);
	}

	if (!cNames.Contains("Scholar.txt"))
	{
		FString name = classStatsDir / "Scholar.txt";
		FString description = "0|0|0|+|+|0";
		MakeTextFile(description, name);
	}
}

void ACharCreator::PopulatePortraitDefaults()
{
	if (!FPaths::DirectoryExists(rPortraitsDir))
	{
		UE_LOG(LogTemp, Error, TEXT("Race portraits directory does not exist. Aborting."));
		return;
	}

	// Directory contains folders of race names. For each folder, add default png files.
	// Default portraits set in BP as FPortraits, then converted into png.

	TArray<FString> pDirs{};
	IFileManager::Get().FindFiles(pDirs, *rPortraitsDir);

	// If entire folder is missing, create directory.

	if (!pDirs.Contains("Aktiin"))
	{
		FString directory = rPortraitsDir / "Aktiin";
		CreateDirectory(directory);
	}

	if (!pDirs.Contains("Aradiin"))
	{
		FString directory = rPortraitsDir / "Aradiin";
		CreateDirectory(directory);
	}

	if (!pDirs.Contains("Lunath"))
	{
		FString directory = rPortraitsDir / "Lunath";
		CreateDirectory(directory);
	}

	if (!pDirs.Contains("Siron"))
	{
		FString directory = rPortraitsDir / "Siron";
		CreateDirectory(directory);
	}

	if (!pDirs.Contains("Zerath"))
	{
		FString directory = rPortraitsDir / "Zerath";
		CreateDirectory(directory);
	}

	// If contents of directories do not contain default portraits, add them.

	pDirs.Empty();
	IFileManager::Get().FindFiles(pDirs, *rPortraitsDir);

	UE_LOG(LogTemp, Display, TEXT("Start image load"));

	for (FName race : defaultRaceNames)
	{
		int counter = 0;
		TArray<UTexture2D*> portraitArray = portraitRegistry.Find(race)->portraits;

		UE_LOG(LogTemp, Display, TEXT("Current race name: %s"), *race.ToString());

		for (UTexture2D* image : portraitArray)
		{
			MakePNG(image, (rPortraitsDir / race.ToString() / FString::FromInt(counter) + ".png"));
			counter++;
		}
	}

	UE_LOG(LogTemp, Display, TEXT("Finished image load"));
}

void ACharCreator::ReadRaces()
{
	// Get all files, read to content, parse, add to array as names.

	// Get list of race file names and stat file names.

	TArray<FString> rNames{};
	IFileManager::Get().FindFiles(rNames, *raceDir, TEXT("*.txt"));
	TArray<FString> rStats{};
	IFileManager::Get().FindFiles(rStats, *rStatsDir, TEXT("*.txt"));

	// Remove extension, then add to race names array. Used for UI display purposes.

	raceNames.Reserve(rNames.Num());

	for (FString name : rNames)
	{
		FString newName = name;
		newName.RemoveFromEnd(TEXT(".txt"));
		FName raceName = FName(*newName);
		raceNames.Add(raceName);
	}

	// Create FRace for each race in Data/Races and add to races array.

	raceRegistry.Reserve(rNames.Num());

	for (FString raceFile : rNames)
	{
		bool foundMatch = false;

		for (FString statFile : rStats)
		{
			if (raceFile.Equals(statFile))
			{
				MakeRace(raceFile, statFile);
				UE_LOG(LogTemp, Display, TEXT("Created race %s"), *raceFile);
				foundMatch = true;
				break;
			}
		}

		// If no corresponding stat file is found, give race a default stat block.

		if (!foundMatch)
		{
			UE_LOG(LogTemp, Warning, TEXT("No race and stats match found. Creating default stats for race."));
			MakeRace(raceFile, "default");
		}
	}
}

void ACharCreator::ReadClasses()
{
	// Get all files, read to content, parse, add to array as names.

	TArray<FString> cNames{};
	IFileManager::Get().FindFiles(cNames, *classDir, TEXT("*.txt"));

	classNames.Reserve(cNames.Num());

	for (FString name : cNames)
	{
		FString className = name;
		className.RemoveFromEnd(TEXT(".txt"));
		FName bgName = FName(*className);
		classNames.Add(bgName);
	}

	// Create FBackground for each class in Data/Classes and add to classes array.

	classRegistry.Reserve(cNames.Num());

	TArray<FString> cStats{};
	IFileManager::Get().FindFiles(cStats, *classStatsDir, TEXT("*.txt"));

	for (FString classFile : cNames)
	{
		bool foundMatch = false;

		for (FString statFile : cStats)
		{
			if (classFile.Equals(statFile))
			{
				MakeClass(classFile, statFile);
				UE_LOG(LogTemp, Display, TEXT("Created Class: %s"), *classFile);
				foundMatch = true;
				break;
			}
		}

		// If no matching class stat bonus was found, make default class.

		if (!foundMatch)
		{
			MakeClass(classFile, "default");
		}
	}
}

void ACharCreator::ReadPortraits()
{
	// Get all directories in Portraits, Make FPortraits for each directory name, save all pngs as texture assets in struct, add struct to registry.
	// Entries will already exist in registry for default races. Overwrite these in case they are modified by the player.

	for (FName race : raceNames)
	{
		FString directory = rPortraitsDir / race.ToString();

		TArray<FString> imagePaths{};
		IFileManager::Get().FindFiles(imagePaths, *directory, TEXT(".png"));
		FPortraits newRacePortraits = FPortraits();

		for (FString imagePath : imagePaths)
		{
			UTexture2D* image = MakeTexture((directory / imagePath));

			if (image)
			{
				newRacePortraits.portraits.Add(image);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Returned image was null, skipping"));
				continue;
			}
		}

		portraitRegistry.Add(race, newRacePortraits);
	}
}

#pragma region Utility

void ACharCreator::CreateDirectory(FString dirName)
{
	if (!FPaths::DirectoryExists(dirName))								// Check if directory does not exist.
	{
		if (IFileManager::Get().MakeDirectory(*dirName, true))			// Make new directory.
		{
			UE_LOG(LogTemp, Display, TEXT("%s directory created successfully."), *dirName);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Could not create %s directory."), *dirName);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s directory already exists."), *dirName);
	}
}

void ACharCreator::MakeTextFile(FString content, FString filePath)
{
	if (!FFileHelper::SaveStringToFile(content, *filePath))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create file at %s"), *filePath);
	}
}

void ACharCreator::MakePNG(UTexture2D* texture, FString filePath)
{
	if (!texture)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Texture2D. Aborting."));
		return;
	}

	texture->UpdateResource();

	// Get texture data.

	if (!texture->GetPlatformData())
	{
		UE_LOG(LogTemp, Error, TEXT("Texture platform data is null. Aborting."));
		return;
	}

	if (texture->GetPlatformData()->Mips.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Texture platform data has no mip maps. Aborting."));
		return;
	}

	FTexture2DMipMap& mip = texture->GetPlatformData()->Mips[0];

	if (mip.BulkData.IsLocked())
		mip.BulkData.Unlock();

	void* data = mip.BulkData.Lock(LOCK_READ_ONLY);

	if (!data)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to lock texture data. Aborting"));
		return;
	}

	int32 width = mip.SizeX;
	int32 height = mip.SizeY;
	const int32 pixelCount = width * height;
	const int32 bytesPerPixel = 4;					// Assuming RGBA8 format.
	TArray<FColor> pixels;
	pixels.SetNumUninitialized(pixelCount);

	FMemory::Memcpy(pixels.GetData(), data, pixelCount * bytesPerPixel);
	mip.BulkData.Unlock();

	// Convert to png.

	IImageWrapperModule& imageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(TEXT("ImageWrapper"));
	TSharedPtr<IImageWrapper> imageWrapper = imageWrapperModule.CreateImageWrapper(EImageFormat::PNG);

	if (imageWrapper->SetRaw(pixels.GetData(), pixels.Num() * bytesPerPixel, width, height, ERGBFormat::BGRA, 8))
	{
		// Save to file path.
		const TArray64<uint8>& pngData = imageWrapper->GetCompressed(100);

		if (FFileHelper::SaveArrayToFile(pngData, *filePath))
		{
			UE_LOG(LogTemp, Display, TEXT("Texture saved as png to %s"), *filePath);
			return;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to save png to directory."));
			return;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to encode texture2D as PNG."));
		return;
	}
}

UTexture2D* ACharCreator::MakeTexture(FString filePath)
{
	if (!FPaths::FileExists(*filePath))
	{
		UE_LOG(LogTemp, Error, TEXT("Directory %s does not exist. Returning null texture."), *filePath);
		return nullptr;
	}

	UTexture2D* texture = FImageUtils::ImportFileAsTexture2D(*filePath);
	return texture;
}

FStatBlock ACharCreator::MakeStatBlock(FString content)
{
	TArray<TCHAR> mods{};
	TArray<FString> parsedFile{};

	// Split content on delimiter '|'. 

	content.ParseIntoArray(parsedFile, TEXT("|"));

	for (FString element : parsedFile)
	{
		// If element is recognized, add. If not, replace with 0.

		if (element.Equals("0") || element.Equals("+") || element.Equals("-"))
		{
			mods.Add(element[0]);
		}
		else
		{
			mods.Add('0');
		}
	}

	// Create stat struct and return.

	if (mods.Num() != 6)
	{
		UE_LOG(LogTemp, Warning, TEXT("mods array had a length less than 6. Replacing with empty stat block"));
		return FStatBlock();
	}

	FStatBlock statBlock = FStatBlock
	(
		modInt.FindRef(mods[0]),
		modInt.FindRef(mods[1]),
		modInt.FindRef(mods[2]),
		modInt.FindRef(mods[3]),
		modInt.FindRef(mods[4]),
		modInt.FindRef(mods[5])
	);

	return statBlock;
}

void ACharCreator::MakeRace(FString raceFile, FString statsFile)
{
	// Create race name and load description.

	FString raceName = raceFile;
	FString raceDesc{};
	raceName.RemoveFromEnd(TEXT(".txt"));
	FFileHelper::LoadFileToString(raceDesc, *(raceDir / raceFile));

	//Check if stat file exists. If true, load. If not, make default stat block.

	FStatBlock raceMod{};

	if (FPaths::FileExists(*(rStatsDir / statsFile)))
	{
		FString stats{};
		FFileHelper::LoadFileToString(stats, *(rStatsDir / statsFile));
		raceMod = MakeStatBlock(stats);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s stats file not found. Adding default stats."), *raceName);
		raceMod = FStatBlock();
	}

	// Make struct and add to registry.

	FRace race = FRace(FName(raceName), FText::FromString(raceDesc), raceMod);
	raceRegistry.Add(race.name, race);
}

void ACharCreator::MakeClass(FString classFile, FString statsFile)
{
	FString className = classFile;
	FString classDesc{};
	className.RemoveFromEnd(TEXT(".txt"));
	FFileHelper::LoadFileToString(classDesc, *(classDir / classFile));

	FStatBlock classMod{};

	if (FPaths::FileExists(*(classStatsDir / classFile)))
	{
		FString stats{};
		FFileHelper::LoadFileToString(stats, *(classStatsDir / statsFile));
		classMod = MakeStatBlock(stats);
	}
	else
	{
		classMod = FStatBlock();
	}

	FBackground background = FBackground(FName(className), FText::FromString(classDesc), classMod);
	classRegistry.Add(background.name, background);
}

#pragma endregion Utility