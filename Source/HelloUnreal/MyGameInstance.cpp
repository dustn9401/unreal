// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "Card.h"
#include "CourseInfo.h"
#include "JsonObjectConverter.h"
#include "Teacher.h"
#include "Student.h"
#include "Staff.h"
#include "StudentManager.h"

void PrintPersonInfo(const UPerson* InPerson, const FString& InTag)
{
	UE_LOG(LogTemp, Log, TEXT("[%s] Name: %s, Year: %d, CardType: %d"), *InTag, *InPerson->GetName(), InPerson->GetYear(), InPerson->GetCard()->GetCardType())
}

FString GenerateRandomName()
{
	constexpr TCHAR FirstChar[] = TEXT("김이박최");
	constexpr TCHAR MiddleChar[] = TEXT("상혜지성");
	constexpr TCHAR LastChar[] = TEXT("수은원연");

	TArray<TCHAR> Picked;
	Picked.SetNum(3);
	Picked[0] = FirstChar[FMath::RandRange(0, 3)];
	Picked[1] = MiddleChar[FMath::RandRange(0, 3)];
	Picked[2] = LastChar[FMath::RandRange(0, 3)];

	return Picked.GetData();
}

void CheckUObjectIsValid(const UObject* InObj, const FString& InTag)
{
	if (InObj->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] is Valid"), *InTag);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] is NOT Valid"), *InTag);
	}
}

void CheckUObjectIsNull(const UObject* InObj, const FString& InTag)
{
	if (InObj == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] == nullptr"), *InTag);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] != nullptr"), *InTag);
	}
}

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


	if (UFunction* DoLessonFunc = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson")); DoLessonFunc != nullptr)
	{
		Teacher->ProcessEvent(DoLessonFunc, nullptr);
	}

	UE_LOG(LogTemp, Log, TEXT("===================================================="));

	// 객체 생성해서 포인터로 들고 있지만, UObject 타입이기 떄문에 따로 메모리 해제를 하지 않아도 되는듯
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

	constexpr int32 StudentNum = 300;
	for(int32 i =0;i<StudentNum;i++)
	{
		// StudentsData.Emplace(FStudentData(GenerateRandomName(), i + 1));
		StudentsData.Emplace(GenerateRandomName(), i);	// 이렇게도 됨
	}

	// TArray<FString> StudentNamesArray = Select<FString>(StudentsData, [](const FStudentData& Data)
	// {
	// 	return Data.Name;
	// });

	TArray<FString> StudentNamesArray;
	Algo::Transform(StudentsData, StudentNamesArray, [](const FStudentData& Data)
	{
		return Data.Name;
	});

	UE_LOG(LogTemp, Log, TEXT("NameArray Num: %d"), StudentNamesArray.Num());

	TSet<FString> StudentNamesSet;
	Algo::Transform(StudentsData, StudentNamesSet, [](const FStudentData& Data)
	{
		return Data.Name;
	});

	UE_LOG(LogTemp, Log, TEXT("NameSet Num: %d"), StudentNamesSet.Num());


	TSet<FStudentData> StudentDataSet;
	for(int32 i =0;i<StudentNum;i++)
	{
		StudentDataSet.Emplace(FStudentData(GenerateRandomName(), i + 1));
	}

	// Map, Multimap 사용법은 stl이랑 비슷함
	// TMap<FString, int32> StudentMap;
	// StudentMap.Find()
	// TMultiMap<FString, int32> StudentMultiMap;
	// StudentMultiMap.MultiFind()

	UE_LOG(LogTemp, Log, TEXT("================================================="));
	
	// UPROPERTY 언리얼 메모리관리
	StudentNonProp = NewObject<UStudent>();
	StudentProp = NewObject<UStudent>();

	StudentManager = new FStudentManager(NewObject<UStudent>());

	// 직렬화/역직렬화, 파일 입출력, 스트림
	const FString SaveDir = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));
	UE_LOG(LogTemp, Log, TEXT("Save Dir: %s"), *SaveDir);

	// 일반 클래스 및 구조체: 쉬프트연산자 직접 구현해서 사용
	{
		const FString RawDataFileName(TEXT("RawData.bin"));
		FString RawDataAbsPath = FPaths::Combine(*SaveDir, *RawDataFileName);
		UE_LOG(LogTemp, Log, TEXT("Save Path: %s"), *RawDataAbsPath);
		FPaths::MakeStandardFilename(RawDataAbsPath);
		UE_LOG(LogTemp, Log, TEXT("Save Path MakeStandardFilename: %s"), *RawDataAbsPath);
		
		FStudentData RawDataSrc(TEXT("김연수"), 16);	// 저장할 데이터
		if (FArchive* RawFileWriterAr = IFileManager::Get().CreateFileWriter(*RawDataAbsPath); RawFileWriterAr != nullptr)
		{
			*RawFileWriterAr << RawDataSrc;
			RawFileWriterAr->Close();
			delete RawFileWriterAr;
			RawFileWriterAr = nullptr;
		}

		FStudentData RawDataDest;
		if (FArchive* RawFileReaderAr = IFileManager::Get().CreateFileReader(*RawDataAbsPath); RawFileReaderAr != nullptr)
		{
			*RawFileReaderAr << RawDataDest;
			RawFileReaderAr->Close();
			delete RawFileReaderAr;
			RawFileReaderAr = nullptr;

			UE_LOG(LogTemp, Log, TEXT("Loaded Data: Name=%s, Order=%d"), *RawDataDest.Name, RawDataDest.Order);
		}
	}

	// 언리얼 오브젝트는 Serialize 함수를 사용
	StudentSrc = NewObject<UStudent>();
	StudentSrc->SetName(TEXT("김연수"));

	auto TeacherSrc = NewObject<UTeacher>();
	TeacherSrc->SetName(TEXT("이득우"));
	TeacherSrc->SetYear(32);
	
	{
		const FString ObjectDataFileName = TEXT("ObjectData.bin");
		FString ObjectDataAbsPath = FPaths::Combine(*SaveDir, *ObjectDataFileName);
		FPaths::MakeStandardFilename(ObjectDataAbsPath);

		TArray<uint8> BufferArray;
		FMemoryWriter MemoryWriter(BufferArray);
		TeacherSrc->Serialize(MemoryWriter);

		// 스마트 포인터, 중괄호가 끝날 때 메모리 해제해줌 (c# using구문)
		if (TUniquePtr<FArchive> FileWriterAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileWriter(*ObjectDataAbsPath)))
		{
			*FileWriterAr << BufferArray;
			FileWriterAr->Close();
		}

		TArray<uint8> BufferArrayFromFile;
		if (TUniquePtr<FArchive> FileReaderAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileReader(*ObjectDataAbsPath)))
		{
			*FileReaderAr << BufferArrayFromFile;
			FileReaderAr->Close();
		}

		FMemoryReader MemoryReader(BufferArrayFromFile);
		UStudent* StudentDest = NewObject<UStudent>();
		StudentDest->Serialize(MemoryReader);
		PrintPersonInfo(StudentDest, TEXT("ObjectData"));
	}

	UE_LOG(LogTemp, Log, TEXT("================================================="));

	// Json 및 스마트 포인터

	{
		const FString ObjectDataFileName = TEXT("ObjectDataJson.json");
		FString ObjectDataAbsPath = FPaths::Combine(*SaveDir, *ObjectDataFileName);
		FPaths::MakeStandardFilename(ObjectDataAbsPath);

		TSharedRef<FJsonObject> JsonObjectSrc = MakeShared<FJsonObject>();
		FJsonObjectConverter::UStructToJsonObject(TeacherSrc->GetClass(), TeacherSrc, JsonObjectSrc);

		//write
		FString JsonOutString;
		if (TSharedRef<TJsonWriter<TCHAR>> JsonWriterAr = TJsonWriterFactory<TCHAR>::Create(&JsonOutString);
			FJsonSerializer::Serialize(JsonObjectSrc, JsonWriterAr))
		{
			FFileHelper::SaveStringToFile(JsonOutString, *ObjectDataAbsPath);	
		}

		// read
		FString JsonInString;
		FFileHelper::LoadFileToString(JsonInString, *ObjectDataAbsPath);

		TSharedRef<TJsonReader<TCHAR>> JsonReaderAr = TJsonReaderFactory<TCHAR>::Create(JsonInString);

		if (TSharedPtr<FJsonObject> JsonObjectDest;
			FJsonSerializer::Deserialize(JsonReaderAr, JsonObjectDest))
		{
			if (UTeacher* JsonStudentDest = NewObject<UTeacher>();
				FJsonObjectConverter::JsonObjectToUStruct(JsonObjectDest.ToSharedRef(), JsonStudentDest->GetClass(), JsonStudentDest))
			{
				PrintPersonInfo(JsonStudentDest, TEXT("JsonData"));
			}
		}
	}
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();

	// 언리얼 오브젝트가 null은 아니지만 유효한 오브젝트가 아닌경우를 체크
	// 유니티 오브젝트는 null비교를 override 하여 비싼 비용으로 체크를 해주긴 하는데, 느려서 잘 사용 안함. 그런데 언리얼은 아예 null비교를 사용하면 안된다.
	CheckUObjectIsNull(StudentNonProp, TEXT("StudentNonProp"));
	CheckUObjectIsValid(StudentNonProp, TEXT("StudentNonProp"));
	CheckUObjectIsNull(StudentProp, TEXT("StudentProp"));
	CheckUObjectIsValid(StudentProp, TEXT("StudentProp"));

	// 언리얼오브젝트가 아닌 일반 c++클래스로 UObject를 관리하는 방법
	const UStudent* Student = StudentManager->GetStudent();
	
	delete StudentManager;
	StudentManager = nullptr;

	CheckUObjectIsNull(Student, TEXT("StudentInManager"));
	CheckUObjectIsValid(Student, TEXT("StudentInManager"));
}

