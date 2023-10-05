// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class HELLOUNREAL_API FStudentManager final : FGCObject
{
public:
	explicit FStudentManager(class UStudent* InStudent) : SafeStudent(InStudent) {}

	TObjectPtr<UStudent> GetStudent() const
	{
		return SafeStudent;
	}

private:
	TObjectPtr<UStudent> SafeStudent = nullptr;

	// FGCObject의 아래 두 함수를 구현해야 함
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	virtual FString GetReferencerName() const override
	{
		return TEXT("FStudentManager");
	}
};
