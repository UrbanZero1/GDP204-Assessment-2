// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTools.h"
TArray<FScenarioStruct> UDialogueTools::BuildDialogueTree(TArray<FDialogueNode> DialogueNodes, FText Name)
{
	TArray<FScenarioStruct> OutScenarios;
	const UEnum* EnumPtr = StaticEnum<ScenarioEnum>();
	const int32 EnumCount = EnumPtr->NumEnums() - 1;

	for (int32 i = 0; i < EnumCount; i++)
	{
		FText EnumDisplayName = EnumPtr->GetDisplayNameTextByIndex(i);
		if (EnumDisplayName.ToString().StartsWith(Name.ToString()))
		{
			OutScenarios.Add({ static_cast<ScenarioEnum>(i) });
		}
	}

	for (int32 i = 0; i < OutScenarios.Num(); i++)
	{
		FScenarioStruct *Scenario = &OutScenarios[i];
		for (FDialogueNode Node : DialogueNodes)
		{
			if (Node.Scenario != Scenario->Scenario)
			{
				continue;
			}
			FDialogueInnerStruct InnerStruct;
			InnerStruct.dialogues.Add(Node.Text);
			InnerStruct.bCondition = Node.Condition;
			InnerStruct.ConditionId = Node.Condition ? 1 : 0;
			if (Node.Condition)
			{
				InnerStruct.dialogues.Add(Node.ConditionText);
			}
			InnerStruct.SpeakerName = Node.Character;
			InnerStruct.bHasResponse = Node.Choices.Num() > 0;
			if (InnerStruct.bHasResponse)
			{
				InnerStruct.Responses = Node.Choices;
			}
			InnerStruct.CharacterEmotion = Node.CharacterEmotion;

			OutScenarios[i].DialogueArray.Add(InnerStruct);
		}
	}

	return OutScenarios;
}
