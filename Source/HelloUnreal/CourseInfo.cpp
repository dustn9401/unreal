// Fill out your copyright notice in the Description page of Project Settings.


#include "CourseInfo.h"

UCourseInfo::UCourseInfo()
{
	Contents = TEXT("기존 학사 정보");
}

void UCourseInfo::ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents)
{
	Contents = InNewContents;

	UE_LOG(LogTemp, Log, TEXT("CourseInfo Changed!!!"));

	OnChanged.Broadcast(InSchoolName, Contents);
}
