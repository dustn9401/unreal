// Fill out your copyright notice in the Description page of Project Settings.


#include "Teacher.h"

UTeacher::UTeacher()
{
	Name = TEXT("이선생");
	Year = 3;
	Id = 1;
}

void UTeacher::DoLesson()
{
	UE_LOG(LogTemp, Log, TEXT("%d년차 %s 선생님이 강의합니다."), Year, *Name);
}
