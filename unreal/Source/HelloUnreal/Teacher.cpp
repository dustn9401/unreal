// Fill out your copyright notice in the Description page of Project Settings.


#include "Teacher.h"

#include "Card.h"

UTeacher::UTeacher()
{
	Name = TEXT("이선생");
	Year = 3;
	Card->SetCardType(ECardType::Teacher);
}

void UTeacher::DoLesson()
{
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("%d년차 %s 선생님이 강의합니다."), Year, *Name);
}
