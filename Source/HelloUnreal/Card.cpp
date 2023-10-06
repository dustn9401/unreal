// Fill out your copyright notice in the Description page of Project Settings.


#include "Card.h"

UCard::UCard(): CardType(ECardType::Invalid), Id(0)
{
}

void UCard::Serialize(FArchive& Ar)
{
	UObject::Serialize(Ar);
	Ar << CardType;
}
