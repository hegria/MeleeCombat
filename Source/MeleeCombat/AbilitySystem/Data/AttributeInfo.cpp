// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/AttributeInfo.h"

FMeleeAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound)
{
	for (const FMeleeAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
			return Info;
	}

	if (bLogNotFound)
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for Attribute Tag [%s]"), *AttributeTag.ToString());

	return FMeleeAttributeInfo();
}
