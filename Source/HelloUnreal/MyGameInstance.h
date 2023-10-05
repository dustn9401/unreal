// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Student.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HELLOUNREAL_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();
	virtual void Init() override;
	virtual void Shutdown() override;
	
private:
	UPROPERTY()
	FString SchoolName;

	UPROPERTY()
	TObjectPtr<class UCourseInfo> CourseInfo;

	TArray<FStudentData> StudentsData;

	TObjectPtr<class UStudent> StudentNonProp;

	UPROPERTY()
	TObjectPtr<class UStudent> StudentProp;

	class FStudentManager* StudentManager = nullptr;
};
