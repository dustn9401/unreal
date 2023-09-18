// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Teacher.h"
#include "Student.h"

UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("기본학교");
}

void UMyGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Log, TEXT("===================================================="));

	const UClass* ClassRuntime = GetClass();
	const UClass* ClassCompile = UMyGameInstance::StaticClass();
	check(ClassRuntime == ClassCompile);
	ensureMsgf(ClassRuntime == ClassCompile, TEXT("ClassRuntime != ClassCompile!!"));

	UE_LOG(LogTemp, Log, TEXT("Shool class name: %s"), *ClassRuntime->GetName());
	SchoolName = TEXT("학교학교");
	UE_LOG(LogTemp, Log, TEXT("%s, %s"), *SchoolName, *ClassRuntime->GetDefaultObject<UMyGameInstance>()->SchoolName);
	
	UE_LOG(LogTemp, Log, TEXT("===================================================="));

	UStudent* Student = NewObject<UStudent>();
	UTeacher* Teacher = NewObject<UTeacher>();
	
	Student->SetName(TEXT("학생1"));
	UE_LOG(LogTemp, Log, TEXT("새로운 학생 이름: %s"), *Student->GetName());

	FProperty* NameProp = UTeacher::StaticClass()->FindPropertyByName(TEXT("Name"));
	if (NameProp)
	{
		FString CurTeacherName;
		
		NameProp->GetValue_InContainer(Teacher, &CurTeacherName);
		UE_LOG(LogTemp, Log, TEXT("현재 선생님이름: %s"), *CurTeacherName);

		CurTeacherName = TEXT("이득우");
		NameProp->SetValue_InContainer(Teacher, &CurTeacherName);
		UE_LOG(LogTemp, Log, TEXT("Teacher->GetName(): %s, NewTeacherName: %s"), *Teacher->GetName(), *CurTeacherName);
	}

	UE_LOG(LogTemp, Log, TEXT("===================================================="));
	
	Student->DoLesson();

	UFunction* DoLessonFunc = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson"));
	if (DoLessonFunc)
	{
		Teacher->ProcessEvent(DoLessonFunc, nullptr);
	}

	UE_LOG(LogTemp, Log, TEXT("===================================================="));
}
