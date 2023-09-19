// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LessonInterface.h"
#include "UObject/NoExportTypes.h"
#include "Person.h"
#include "Student.generated.h"

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
private:
	UPROPERTY()
	int32 Id;
};
