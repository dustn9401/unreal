// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUNREAL_API UPerson : public UObject
{
	GENERATED_BODY()

public:
	UPerson();
	
	// ReSharper disable once CppHidingFunction
	FORCEINLINE const FString& GetName() const
    {
    	return Name;
    }
    
    FORCEINLINE void SetName(const FString& InName)
    {
    	Name = InName;
    }


	// FORCEINLINE TObjectPtr<class UCard> GetCard() const	// 구현부에서는 아래 라인처럼 사용함. 물론 이 라인도 사용 가능ㅇㅇ
	FORCEINLINE class UCard* GetCard() const
	{
		return Card;
	}

	// FORCEINLINE void SetCard(const TObjectPtr<UCard>& InCard)	// setter도 마찬가지로, 이 라인도 사용 가능하지만 일반적으로 아래처럼 사용함
	FORCEINLINE void SetCard(class UCard* InCard)
	{
		this->Card = InCard;
	}

	virtual void Serialize(FArchive& Ar) override;
	
protected:
	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Year;

public:
	[[nodiscard]] int32 GetYear() const
	{
		return Year;
	}

	void SetYear(int32 InYear)
	{
		this->Year = InYear;
	}

protected:
	UPROPERTY()
	// class UCard* Card;	// 옛날방식
	TObjectPtr<class UCard> Card;	// 언리얼5 최신방식 ㅋ


private:
};
