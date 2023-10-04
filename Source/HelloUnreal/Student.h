// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LessonInterface.h"
#include "UObject/NoExportTypes.h"
#include "Person.h"
#include "Student.generated.h"

USTRUCT()
struct FStudentData
{
	friend bool operator==(const FStudentData& Lhs, const FStudentData& RHS)
	{
		return Lhs.Name == RHS.Name
			&& Lhs.Order == RHS.Order;
	}

	friend bool operator!=(const FStudentData& Lhs, const FStudentData& RHS)
	{
		return !(Lhs == RHS);
	}

	friend FORCEINLINE uint32 GetTypeHash(const FStudentData& InData)
	{
		return GetTypeHash(InData.Order);
	}

	GENERATED_BODY()

	FStudentData(): Name(TEXT("Default")), Order(-1)
	{
	}

	FStudentData(const FString& Name, const int32 Order)
		: Name(Name),
		  Order(Order)
	{
	}

	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Order;
};

/**
 * 
 */
UCLASS()
class HELLOUNREAL_API UStudent : public UPerson, public ILessonInterface
{
	GENERATED_BODY()
public:
	UStudent();

	virtual void DoLesson() override;

	void GetNotification(const FString& School, const FString& NewCourseInfo) const;
};
