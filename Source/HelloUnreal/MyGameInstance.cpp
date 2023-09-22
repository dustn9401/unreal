// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "Card.h"
#include "CourseInfo.h"
#include "Teacher.h"
#include "Student.h"
#include "Staff.h"

UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("기본학교");
	// CourseInfo = NewObject<UCourseInfo>();
}

template <typename T, typename K, typename LambdaType>
TArray<T> Select(const TArray<K>& InArr, LambdaType Func)
{
	TArray<T> Ret;
	for(auto Element : InArr)
	{
		Ret.Emplace(Func(Element));
	}

	return Ret;
}

// 문자열을 결합하는 함수
// Elements 타입을 템플릿으로 하고 싶었는데, 공용 문자열 변환 함수가 없어서 실패
FString Join(const TArray<FString>& Elements, const FString& Delimiter) {
	FString Result;
	bool IsFirst = true;
    
	for (const FString& Element : Elements) {
		if (!IsFirst) Result += Delimiter;
		Result += Element;
		IsFirst = false;
	}
    
	return Result;
}

void UMyGameInstance::Init()
{
	Super::Init();

	const TArray<int32> Arr = {1,2,3,4,5};
	
	// C#의 Where
	auto EvenNums = Arr.FilterByPredicate([](int32 Element) {return Element % 2 == 0;});

	// C#의 Select에 해당하는 함수는 없다. 이런식으로 사용하는듯
	TArray<int32> TwoPoweredNums;
	for (const int32& Element : Arr)
	{
		TwoPoweredNums.Add(Element * Element);
	}

	// 직접만든 Select함수
	auto TwoPoweredNumsStr = Select<FString>(TwoPoweredNums, [](int32 X)
	{
		return FString::Printf(TEXT("%d"), X);
	});
	
	UE_LOG(LogTemp, Log, TEXT("TwoPoweredNums: %s"), *Join(TwoPoweredNumsStr, TEXT(", ")))

	// CourseInfo = NewObject<UCourseInfo>(this);
	CourseInfo = NewObject<UCourseInfo>();	// CourseInfo를 멤버변수로 들고 있어도 Outer 지정이 필수는 아닌듯.

	UE_LOG(LogTemp, Log, TEXT("===================================================="));

	UStudent* Student1 = NewObject<UStudent>();
	Student1->SetName(TEXT("학생1"));
	UStudent* Student2 = NewObject<UStudent>();
	Student2->SetName(TEXT("학생2"));
	UStudent* Student3 = NewObject<UStudent>();
	Student3->SetName(TEXT("학생3"));

	CourseInfo->OnChanged.AddUObject(Student1, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student2, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student3, &UStudent::GetNotification);

	CourseInfo->ChangeCourseInfo(SchoolName, TEXT("변경된 학사 정보"));

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
	

	UFunction* DoLessonFunc = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson"));
	if (DoLessonFunc)
	{
		Teacher->ProcessEvent(DoLessonFunc, nullptr);
	}

	UE_LOG(LogTemp, Log, TEXT("===================================================="));
	
	TArray<UPerson*> Persons = { NewObject<UStudent>(), NewObject<UTeacher>(), NewObject<UStaff>()};
	int32 Idx = 0;
	for(const auto Person : Persons)
	{
		UE_LOG(LogTemp, Log, TEXT("#%d, Name=%s"), Idx, *Person->GetName());
		if (ILessonInterface* LessonInterface = Cast<ILessonInterface>(Person))
		{
			UE_LOG(LogTemp, Log, TEXT("%s is ILesson"), *Person->GetName());
			LessonInterface->DoLesson();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("%s is NOT ILesson"), *Person->GetName());
		}

		const UCard* OwnCard = Person->GetCard();
		check(OwnCard);

		// Name 파라미터는 언리얼엔진 규약임. /Script는 언리얼 객체 위치(언리얼이 정한 값), 모듈이름(프로젝트명).타입
		if (const UEnum* CardEnumType = FindObject<UEnum>(nullptr, TEXT("/Script/HelloUnreal.ECardType")))
		{
			FString CardEnumDisplayName = CardEnumType->GetDisplayNameTextByValue(static_cast<int64>(OwnCard->GetCardType())).ToString();
			UE_LOG(LogTemp, Log, TEXT("CardType=%d, DisplayName=%s"), OwnCard->GetCardType(), *CardEnumDisplayName);
		}

		Idx++;
	}
	
	UE_LOG(LogTemp, Log, TEXT("================================================="));
}
