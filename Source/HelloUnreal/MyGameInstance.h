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
	
	// TArray 내의 오브젝트도 마찬가지로, UPROPERTY() 매크로가 없다면 해제당한다. (컴파일러 경고가 없기 떄문에 주의가 필요할듯)
	TArray<TObjectPtr<class FStudent>> StudentNonPropArray;

	UPROPERTY()
	TArray<TObjectPtr<class FStudent>> StudentPropArray;


	class FStudentManager* StudentManager = nullptr;
};
