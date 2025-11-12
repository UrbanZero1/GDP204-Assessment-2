// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DialogueTools.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ScenarioEnum : uint8
{
	Null                	UMETA(DisplayName = "Null"),
	Jordan_FirstContact 	UMETA(DisplayName = "Jordan - First Contact"),
	Jordan_FollowUp     	UMETA(DisplayName = "Jordan - Follow Up"),
	Jordan_CoffeeInvite 	UMETA(DisplayName = "Jordan - Coffee Invite"),
	Jordan_FamilyCall   	UMETA(DisplayName = "Jordan - Family Call"),
	Jordan_Disclosure   	UMETA(DisplayName = "Jordan - Disclosure"),
	Jordan_LastWalk     	UMETA(DisplayName = "Jordan - Last Walk"),
	Jade_BumpIn				UMETA(DisplayName = "Jade - Bump-In"),
	Jade_Apology			UMETA(DisplayName = "Jade - Apology"),
	Jade_SampleShuffle		UMETA(DisplayName = "Jade - Sample Shuffle"),
	Jade_PersonalQuestion	UMETA(DisplayName = "Jade - Personal Question"),
	Jade_HastyConfession	UMETA(DisplayName = "Jade - Hasty Confession"),
	Jade_Overwhelm			UMETA(DisplayName = "Jade - Overwhelm"),
	Jade_CheckIn			UMETA(DisplayName = "Jade - Check-In"),
	Liam_AfterPractice		UMETA(DisplayName = "Liam - After Practice"),
	Liam_Hallway			UMETA(DisplayName = "Liam - Hallway"),
	Liam_StudyGroup			UMETA(DisplayName = "Liam - Study Group Drop-In"),
	Liam_FriendPressure		UMETA(DisplayName = "Liam - Friend Pressure"),
	Liam_BoilOver			UMETA(DisplayName = "Liam - Boil Over"),
	Liam_WheresLiam			UMETA(DisplayName = "Liam - Wheres Liam"),
	Liam_Accountability		UMETA(DisplayName = "Liam - Accountability"),
	Liam_ChoosingCrew		UMETA(DisplayName = "Liam - Choosing Your Crew"),
};

UENUM(BlueprintType)
enum class CharacterEmotions : uint8
{
	Normal UMETA(DisplayName = "Normal"),
	Speaking UMETA(DisplayName = "Speaking"),
	Happy UMETA(DisplayName = "Happy"),
	Mad UMETA(DisplayName = "Mad"),
	Flirty UMETA(DisplayName = "Flirty"),
	Disagree UMETA(DisplayName = "Disagree"),
	Blush UMETA(DisplayName = "Blush"),
};

USTRUCT(BlueprintType)
struct DIALOGUETEST_API FChoiceNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Affection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Text;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AnswerId;
};

USTRUCT(BlueprintType)
struct DIALOGUETEST_API FScenarioBackground : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ScenarioEnum Scenario;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture;
};

USTRUCT(BlueprintType)
struct DIALOGUETEST_API FDialogueNode : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ScenarioEnum Scenario;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FChoiceNode> Choices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NextId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Condition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ConditionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	CharacterEmotions CharacterEmotion;

};

USTRUCT(BlueprintType)
struct DIALOGUETEST_API FDialogueInnerStruct
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> dialogues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCondition;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ConditionId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SpeakerName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasResponse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FChoiceNode> Responses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	CharacterEmotions CharacterEmotion;
};

USTRUCT(BlueprintType)
struct DIALOGUETEST_API FScenarioStruct
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ScenarioEnum Scenario;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDialogueInnerStruct> DialogueArray;

};

USTRUCT(BlueprintType)
struct DIALOGUETEST_API FCharacterDisplayStruct : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	CharacterEmotions CharacterEmotion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CharacterTexture;
};

USTRUCT(BlueprintType)
struct DIALOGUETEST_API FSaveStruct
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CharacterId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Affection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ScenarioId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DialogueId;
	
};

UCLASS()
class DIALOGUETEST_API UDialogueTools : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static TArray<FScenarioStruct> BuildDialogueTree(TArray<FDialogueNode> DialogueArray, FText Name);
};

