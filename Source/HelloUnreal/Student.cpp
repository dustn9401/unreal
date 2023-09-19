// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"

#include "Card.h"

UStudent::UStudent()
{
	Name = TEXT("이학생");
	Card->SetCardType(ECardType::Student);
}

void UStudent::DoLesson()
{
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("%d학년 %s학생 출석"), Year, *Name);
}
