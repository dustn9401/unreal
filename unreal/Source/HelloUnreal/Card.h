// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Card.generated.h"

UENUM()
enum class ECardType : uint8
{
	Student=1 UMETA(DisplayName="For Student"),
	Teacher UMETA(DisplayName="For Teacher"),
	Staff UMETA(DisplayName="For Staff"),
	Invalid
};

/**
 * 
 */
UCLASS()
class HELLOUNREAL_API UCard : public UObject
{
	GENERATED_BODY()

public:
	UCard();

private:
	UPROPERTY()
	ECardType CardType;

public:
	ECardType GetCardType() const
	{
		return CardType;
	}

	void SetCardType(const ECardType InCardType)
	{
		this->CardType = InCardType;
	}

	virtual void Serialize(FArchive& Ar) override;

private:
	UPROPERTY()
	int32 Id;
};
