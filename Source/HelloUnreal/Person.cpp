// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"

#include "Card.h"

UPerson::UPerson()
{
	Name = TEXT("홍길동");
	Year = 1;
	Card = CreateDefaultSubobject<UCard>(TEXT("NAME_Card"));
}

void UPerson::Serialize(FArchive& Ar)
{
	// Super::Serialize(Ar);	// 언리얼 5.2부터 바뀐걸로 의심되는데, 이거 쓰면 크래시남
	
	Ar << Year;
	Ar << Name;
	Card->Serialize(Ar);
	// Ar << Card;	// 이렇게는 안됨
}
