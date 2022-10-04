# 포트폴리오 동영상 링크
https://www.youtube.com/watch?v=3RmR-PMR3co

# 완료한 것들
* AI Enemy를 만들었다.
    * BlackBoard에 정보를 저장하고, Behavior Tree에서 알고리즘을 수행한다.
    * AI Controller에서 필요한 연결작업들을 수행 (Behavior Tree나 AI Perception 등)
    * 이미 만들었던 플레이어 Anim_BP를 리타게터를 이용하여 리타깃 후 그대로 사용하였다.
    * 공격 모션의 경우 플레이어는 Anim Notify로 Sphere Trace 하였는데, 에너미의 경우 몽타주 노티파이를 활용하였다.

* Movement Input / Camera Input 을 c++로 Bind
* DeadMenu Widget을 ActorStatusComponent 안에 만들었다. (해당 Property와 상호작용하기 때문에)
    * 죽으면 DeadMenuWidget이 표시되게 만들었다.
* CharacterStatusComponent 라는 ActorComponent를 만들어서 관리한다.    
    1. Actor Component와 그냥 Component의 차이 확인하기 -> ActorComponent 을 사용하기로 정함 (추상적개념이기 때문에)
    2. CharacterStatusComponent 라는 AC를 만들었다. (추후 플레이어와 NPC 모두 적용하기 위함)
    3. Health 과 RecieveDamage 기능을 구현했다.
        * FClamp 로 Heal 이나 Damage 가 0~MaxHealth 의 범위를 넘지 않도록 조절했다.
        * UGameplayStatics::SpawnSoundAttached 를 통해 소리가 플레이어에 부착되도록 했다.
            * 리턴값은 UAuidoComponent* 이다. (Play와 Stop로 소리를 컨트롤 가능하다.)
        * Health가 0이 되면 죽도록 처리했다. (GameMode는 왜 c++ 상속해도 UFUNCTION이 안생기는지 의문)
            * GetWorld()->SpawnActor() 를 사용했는데 매개변수로 FActorSpawnParameters 가 들어간다.
            * FActorSpawnParameters 에서 Owner 만 사용해봤다.
            * 흑백화면을 만들기 위해 Camera->PostProcessingSettings를 수정했다.
    4. Component 안에서 Widget 을 만들고 Player 에 붙였다.
    5. 죽었을 때 나타나는 DeadMenu 를 만들었다.
        * Respawn , Quit 버튼을 만들었다.
    6. Respawn 기능을 만들었다.
        * Component BeginPlay 시 Widget을 새로 만들어서 붙여줬다.
        * GameMode 와 연동하여 SpawnActor 해줬다.
    7. Quit Game 기능을 만들었다.

* Zoom In / Out 을 만들었다.
    * 단순히 Spring Arm Target Length 만 조절하면 되는 쉬운 작없이었다.   
    (아마 부드럽게 작동하려면 추가적인 수정이 필요할듯)

* Target Lock On / Off 를 만들었다.
    * Blueprint로 먼저 작업하고 C++로 변환하는 과정을 거쳤다.
        * 확실히 워크 플로우를 한번에 보기 편하고, 새로운 기능을 추가할 땐 블루프린트로 선작업하는게 훨씬 좋은 것 같다.
        * c++ 로 옮길땐 항상 생각지도 못한 변수가 생길 수 있다. 변수부터 차근차근 바꾸고 함수도 구현이 확실히 되는지, 외부참조는 없는지 확인 후 변환할 것

# 새로 배운 점
1. Git 을 통해 버전 관리를 할 때는, 항상 visual studio project file 을 다시 generate 시켜줘야한다.
    * 다른 PC에서 작업한 c++ 파일이 여기서 pull 했더니 vs project에 안들어있음

2. Class 의 Constructor 에서는 되도록 멤버 변수를 사용하는 일을 하지 말자 (생성, 초기화 관련된 일만 하자)
    * BeginPlay()를 이용하거나 Init() 함수를 따로 만들어서 사용하자.

3. Post Construct (like BeginPlay)가 필요할 때는 Native Construct 를 override 해서 사용하자!
    * 함수 내부에서 먼저 Super::NaiveConstruct()를 실행 해 준 뒤 Post Construct 처럼 활용

4. Interface 자체에서 구현된 경우 아래와 같이 cast 없이 바로 method 사용 가능   
(멍청한 거였음 이건 해당 Object를 import 했다는건데 그럴꺼면 interface 쓸 필요가 없음)   
(interface 는 두 객체가 서로 정보를 알지 못해도 interface 라는 공통분모를 가지고 소통하는거)
    * 이 때 interface 를 상속받은 class 에서 interface method를 override 한 경우 override 된 함수가 실행된다.
    * 만약 override 하지 않았다면 interface 자체에서 구현된 함수가 실행된다.
    * ex)

        ```c++
            // 아래처럼 굳이 cast 해서 사용할 필요 없음
            if (IMyInterface* Interface = Cast<IMyInterface>(MyObject);)
            {
                Interface->MyInterfaceMethod();
            }
            // 아래와 같이 사용
            MyObject->MyInterfaceMethod();
        ```
5. Component
    1. ActorComponent
        * 모든 컴포넌트들의 부모이다.
        * 움직임, 인벤토리, 어트리뷰트 관리 및 기타 <B>비물리적 개념</B>과 같은 <B>추상적인 동작</B> 대부분에 유용
        * Transform 이 없다. (즉, 이동 회전 등을 하지 않는다)
    2. SceneComponent
        * ActorComponent의 자손이다.
        * Transform 을 포함하다. (위치, 이동, 회전 등의 역할이 추가)
        * Geometry 가 없다. (visual, physics, collision 등을 하지 않는다.)
    3. PrimitiveComponent
        * SceneComponent의 자손이다.
        * Geometry 를 포함한다. (시각 표현, 물리 법칙, 충돌 등의 역할이 추가된다.)
    * 즉 Actor -> Scene -> Primitive 순의 상속관계이고, 상속될때마다 하나씩 기능이 추가된다.
    * Actor (Component말고) 는 기본적으로 SceneComponent를 가지고 있고, 거기에 여러 컴포넌트들을 추가하여 만들어지는 컴포넌트의 집합체이다.

6.  Timer 설정
    1. 생성
        * ex) GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &MyUObject::MyMemberMethod, 10.0f, true);
        * 이 타이머를 가질 FTimerHandler, 실행하는 UObject, 실행하려고 하는 MemberMethod, 타이머 시간 (얼마 뒤에 실행할지), 반복여부, 첫 시작 시간 (안적으면 앞에 시간과 동일)
    2. 제거
        ```c++
            GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);
	        MyTimerHandle.Invalidate();
        ```

7. LogUObjectBase: Error: 'this' pointer is invalid. 에러
    * 정말 바보같은 에러다. 만들어져있지 않은 Object에 아마 MyObject.IsValidLowLevelFast()를 실행하면 뜰 것이다.
    * 내 경우 BeginPlay에서 (아직 CreateWidget 하지 않은 )UUserWidget* 에 있는 함수를 사용하려다 자꾸 Access 에러가 떠서 위의 IsValid 함수를 사용했더니 발견되었다.
    * 이 경우에는 해당 함수까지의 경로에 UE_LOG 를 찍어서 어디까지 정상적으로 들어가는지 판별하면 대충 에러의 원인이 보인다.
    * (220926) 똑같은 실수를 또 했다.
        * Replicate 적용 중 Item 으로 Status가 변경 될 시 UpdateHUD를 통해 HUD에 있는 status 수치를 변경했다.
        * 근데 이 HUD 는 IsLocallyControlled 일 때만 생성되도록 했음 (하지만 멍청하게도 UpdateHUD는 모든 client에서 실행된다는걸 까먹음)
        * 계속 'this'pointer is invalid 에러가 떴었다.
        * UpdateHUD 를 IsLocallyControlled 일때만 실행하도록 수정하니 에러 사라짐
        * Replicate 할 때는 이게 어디서 실행될 지 꼭 생각하면서 함수를 짜야겠다.

8. 배열에서 IsNotEmtpy() 를 표현하는 방법
    ```c++
        if (MyArray.Num()) { }
        // 이렇게 하면 Num 이 0이면 false로 취급돼서 IsNotEmpty()와 같은 기능을 한다.
    ```
9. Replicate
    1. UPROPERTY
        ```c++
        // MyActor.h
            UPROPERTY(Replicated) 
            UMyProperty MyProperty;
            // 또는 아래와 같이 선언 후
            UPROPERTY(ReplicatedUsing = OnRep_MyProperty)
            UMyProperty MyProperty;

            // 해당 변수가 Replicate 되었을 때 처리할 기능을 아래의 함수에 구현해주면 된다.
            void OnRep_MyProperty();
        // MyActor.cpp
            void AInventoryTut_PlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
            {
                DOREPLIFETIME(AMyActor, MyProperty);
                // 또는 특정 조건으로 Replicate 시키고 싶다면
                DOREPLIFETIME_COND(AMyActor, MyProperty, /* 특정 컨디션*/);
            }
        ```
    2. UComponent
        ``` c++
            // 해당 컴포넌트를 소유하는 actor class의 contructor 에서
            MyComponent->SetIsReplicated(true);
        ```
10. Replicate 관련 오류
    1. IsLocallyControlled 
        * InterfaceWidget 은 IsLocallyControlled 인 캐릭터만 생성
        * AddItem (InterfaceWidget 건드리는 함수) 를 실행할 때 IsLocallyControlled 체크를 안해서 계속 튕김 (InterfaceWidget이 생성되지 않은 다른 Actor들에서도 계속 접근하려고 했었던 것)
        * 항상 IsLocallyControlled 와 HasAuthority 를 잘 생각해서 코드를 짜야겠다.
    2. RPC 는 항상 Reliable 혹은 UnReliable 과 함께 쓰여야한다.

11. ECollisionChannel (ECC)
    1. ETraceTypeQuery 와 EObjectTypeQuery 는 다 ECC 안에 있는걸 따로 매칭한 것이다.
    2. UEngineTypes::ConvertToTraceType() 또는 UEngineTypes::ConvertToObjectType() 으로 형변환 해서 사용 가능하다. (반대로도 가능)

12. Unreal Interface
    1. 사용법
        1. c++ 로 작성해서 c++ class 에서 inherit 한 뒤 c++로 사용할 때는
            ```c++
                if (IMyInterface* Interface = Cast<IMyInterface>(MyObject))
                {
                    Interface->MyInterfaceFunction();
                }
            ```
        2. c++로 작성해서 BP 로 inherit, implement 한 뒤 c++에서 사용할 때는
            ```c++
                if (MyObject->GetClass()->ImplementsInterface(UMyInteface::StaticClass()))
                {
                    IMyInteface::Execute_MyInterfaceFunction(MyObject);
                }
            ```
    2. 상속 방법
        1. c++로 작성해서 BP에서 Implement 하고 싶으면 (당연한거지만 적어봄)
            ```c++
                // BP 에서 구현해줘야하기 때문에 BlueprintImplementableEvent 혹은 BlueprintNativeEvent
                // virtual X, 당연히 pure virtual 도 X
                UFUNCTION(BlueprintImplementableEvent)
                void MyFunction();
            ```
13. SphereOverlapActors
    1. 사용법
        ```c++
            FVector MySpawnLocation = GetActorLocation();
            float MySphereRadius = 100.0f;
            TArray<TEnumAsByte<EObjectTypeQuery>> QueryArray;
	        QueryArray.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
            TArray<AActor*> IgnoreActorArray;
	        IgnoreActorArray.Add(this);

            TArray<AActor*> OverlapedActors;
            UKismetSystemLibrary::SphereOverlapActors(GetWorld(), MySpawnLocation, MySphereRadius, QueryArray, AMyTargetActor::StaticClass(), IgnoreActorArray, OverlapedActors);
        ```
14. 컴포넌트화
    1. 해당 액터에 그 컴포넌트가 있는지 확인하는 법
        ``` c++
            // 생각보다 복잡
            UMyComponent* MyComponent = Cast<UMyComponent>(MyActor->GetComponentByClass(UMyComponent::StaticClass()));
            if (MyComponent != nullptr && MyComponent->IsValidLowLevelFast())
            {
                MyComponent->MyComponentFunction();
            }
        ```
        1. 컴포넌트를 찾고자 하는 액터->GetComponentByClass() 를 해준다.
            * 이 때 파라미터로는 <B>UMyActorComponent::StaticClass()</B> 를 넣어준다.
        2. 위 함수의 리턴값은 UActorComponent* 이다. 따라서 바로 넣을 수 없으니 Casting 해서 넣어준다.
        3. 초기화된 변수가 nullptr 인지, nullptr이 아니라면 valid한지 체크한다.
        4. 여기까지 통과하면 해당 액터에 컴포넌트가 존재하고 제대로 찾은것이니 <B>-></B>로 사용한다.
    2. 위젯을 소유하는 액터가 해당 컴포넌트를 가지고 있는지 확인하는 법
        ```c++
            UMyComponent* MyComponent = Cast<UMyComponent>(UUserWidget::GetOwningPlayerPawn()->GetComponentByClass(UMyComponent::StaticClass()));
        ```
        1. 처음엔 GetOwningPlayer() 를 썼었는데 Cast가 실패했었다. (GetOwningPlayer 는 PlayerController를 반환한다, Component 는 그 Controller가 조종하는 Pawn에서 찾아야함)
        2. GetOwningPlayerPawn()을 사용하니 정상적으로 작동

15. Camera
    1. PostProcessing 
        1. 흑백화면 만들기
            ```c++
                UCameraComponent* Camera = Cast<UCameraComponent>(this->GetComponentByClass(UCameraComponent::StaticClass()));
                if (Camera && Camera->IsValidLowLevelFast())
                {
                    Camera->PostProcessSettings.bOverride_ColorSaturation = 1;
                    Camera->PostProcessSettings.ColorSaturation = FVector4(0, 0, 0, 1);
                }
            ```
            1. 플레이어의 <B>CameraComponent</B> 에 접근
            2. <B>CameraComponent</B> 의 <B>PostProcessSetting</B>을 수정해준다.
                1. 하나는 해당 값을 Override할지를 정하는 bool형 변수 bOverride_ 이고
                2. 하나는 채도값에 해당하는 FVector4형 변수 ColorSaturation 이다.
            3. 참고로 이 때 플레이어의 카메라를 포스트 프로세싱 하는 것이기 때문에 World는 정상적으로 적용되나, Widget은 Viewport에 따로 붙기때문에 적용이 안된다.   
            (근데 와우도 UI는 흑백화면 적용이 안돼서 굳이 찾을 필요는 없을듯)
    2. Camera Shake
        1. 먼저 CameraShakeBase 를 만든다.
            1. 단일 인스턴스 (하나로 쿨타임마다 쓸껀지 / 매번 카메라셰이크때마다 생성할껀지)
                * 셰이크를 중첩할게 아니고 한 액터에서만 사용할꺼기 때문에 이번엔 단일로 사용함
            2. 카메라 셰이크 패턴 -> 루트 셰이크 패턴 (카메라 흔들 방법 / 종류)
                * 웨이브 오실레이터가 무난하다고 해서 선택
                * Location
                    * 위치 면적 배수 : 흔들릴 면적
                    * 위치 주파수 배수 : 흔들림 강도
                * Timing
                    * 경과 시간 : 흔들릴 시간
        2. 다 만들었으면 저장하고 아래와 같이 사용
            ```c++
                if (CameraShakeBase && CameraShakeBase->IsValidLowLevelFast())
                    Cast<APlayerController>(GetOwner()->GetOwner())->PlayerCameraManager.Get()->StartCameraShake(CameraShakeBase);
            ```
            1. 요점은 사용하고자 하는 Player Controller 에 접근 후
            2. 카메라 매니저를 부르고
            3. 거기서 StartShakeCamera 를 하면 된다. (매개변수는 TSubclassOf<UCameraShakeBase>) 이다.

        
16. Animation
    1. RootMotion
        1. RootMotion 인지 확인하는 방법 (Mixamo)
            * mixamo 에서 애니메이션을 선택하면 <B>In Place</B> 체크 박스가 있다.
            * 언리얼의 애니메이션 창에서 Character->Bones->All Hierachy 선택하면 빨간색 줄 (Root)가 늘어나는게 보인다.
        2. RootMotion 활성화
            * 애니메이션 Asset Detail 의 Root Motion 탭에서 루트모션 활성화를 눌러준다.
                * 루트모션 잠금을 Ref Pose 와 Anim First Frame 중에 적절한 것으로 선택해준다.
            * 제대로 적용됐는지 확인하려면 캐릭터->애니메이션-> 루프 / 루프 및 초기화 를 선택해준다.
            * 아까처럼 루프선(빨간줄)이 늘어난다면 제대로 적용된 것
        3. Blender 의 Addon 활용할 것
            * Edit -> Preferences -> Add-ons 에서 Animation:Mixamo Converter 찾기
            * 설치되어있지 않다면 위의 Install 눌러서 Zip 다운받은거 찾아서 설치
            * 설치 후 Blender 화면의 우측 Mixamo 탭 누르고
                * Transfer Rotation 체크해제
                * Advances Options 에서 Apply Rotations 체크해제
            * Advanced Options 닫고 Batch 구역의 Input 과 Output 폴더 경로 설정
            * Input 폴더에 mixamo 에서 받은 fbx 넣고 Batch Convert 버튼 누르기
            * Output 폴더에 변환된 fbx를 unreal 에서 활용 (모델, 애니메이션 둘 다 가능)
    2. Animation Slot
        *  사용하고자 하는 Montage 화면에서 우하단 애님 슬롯 매니저 창 누르기 (없다면 상단 '창' 에서 활성화)
        * (사용하고자 하는 슬롯을 새로 만들어야 한다면) 슬롯 추가 후 이름 작성 (여기선 UpperBody)
        * 중앙하단의 DefaultGroup.DefaultSlot 으로 되어있는거 누르고 슬롯이름->UpperBody 선택
        * 저장 후 AnimBP 가서
            * 우선 기존 사용하던 (섞을 원본) 을 <B>캐시 포즈 새로 저장</B> 으로 저장
            * 해당 캐시 포즈를 두개 불러서 Layer Blend By Bone 에 연결
            * 아래 연결된 캐시와 Layer Blend 사이에 Default Slot 을 끼워넣어주고 클릭해서 슬롯 을 UpperBody 로 변경
            * Layer Blend 클릭
                * 레이어 설정 -> 인덱스 -> 분기 필터 에 + 버튼 눌러서 인덱스 추가
                * 인덱스에서 어디서부터 블렌드 할껀지 사용할 본 이름 적기 (Skeleton 에서 본 돌려보면서 결정하기)
                * 뎁스 블랜드 1로 설정 -> 메시 스페이스 회전 블렌드 활성화
            * 저장
    3. Retarget
        * 이미 존재하는 애니메이션이나 애님 블루프린트를 다른 스켈레톤 메시에 그대로 적용시키는 방법
        * 원본 스켈레톤 메시와 적용할 스켈레톤 메시 둘다 IK Rig가 필요하다.
            * Chain에서 각각 뻗어나가는 부분들을 등록해준다.
                1. 목부터 머리까지 (Head)
                2. 왼 어깨부터 손까지 (Arm_L)
                3. 오른 어깨부터 손까지 (Arm_R)
                4. 왼 허벅지부터 발까지 (Leg_L)
                5. 오른 허벅지부터 발까지 (Leg_R)
                6. 척추 (Spine)
            * 그리고 골반에 해당하는 부분 (Hip 혹은 Pelvis) 을 루트로 지정해준다.
        * 그 후 IK Retargetor를 만들어서 원본과 적용할 IK Rig를 등록해준다.
        * 그러면 이제 그 리타게터를 가지고 애니메이션이나 애님 블루프린트를 리타깃하여 사용할 수 있다.

17. UUserWidget
    1. SpawnActor
        * BeginPlay에서 CreateWidget을 실행했더니, 죽고 나서 SpawnActor로 리스폰 할 때는 BeginPlay 당시 PlayerController가 없었다. (라고 생각했다)
        * 그래서 PlayerController 가 Pawn 을 OnPossess할 때 Component를 찾아서 Widget을 만들어줬다.
        * 그런데 Component의 GetOwner는 해당 Component를 소유하는 Actor (컴포넌트 말고 진짜 배치되는 액터) 이고, 그 Actor를 다시 GetOwner 해야 Controller 가 나온다.
        * Component 의 BeginPlay 에서 CreateWidget 할 때, OwningObject 매개변수에 GetOwner()->GetOwner() 를 넣었더니 정상적으로 작동했다.

18. QuitGame
    ```c++
        UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Type::Quit, false);
    ```