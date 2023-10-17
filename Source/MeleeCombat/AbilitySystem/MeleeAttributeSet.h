// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MeleeAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)			\
	 GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	 GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)				\
	 GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)				\
	 GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class MELEECOMBAT_API UMeleeAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	

public:
	UMeleeAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	//void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);

	UPROPERTY(BlueprintReadOnly,Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMeleeAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMeleeAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UMeleeAttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UMeleeAttributeSet, MaxStamina);


	template<class T>
	using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;
};
