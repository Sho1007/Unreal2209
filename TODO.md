# 진행 중
(언리얼 강의) https://youtu.be/qJn5vnNWWLw?list=PLnHeglBaPYu-LRVJOgj0egeKwVGXFUSqE&t=106   
(운영체제 강의) https://youtu.be/EdTtGv9w2sA?list=PLBrGAFAIyf5rby7QylRc6JxU5lzQ9c4tN&t=1251

# 해야할 것들
## Inventory
### Add Function
1. LineTrace 했을 때 true면 Outline 나오면서 [F] (Interact) 느낌의 버튼 활성화 (해당 물체의 표면에 있는듯한 Rotation 반영)
    1. LineTrace 했을 때 true면 (이하 InteractInterface 상속받았을 때) CrossHair 활성화
    2. Outline Material 구현
    3. LineTrace 했을 때 true면 Outline Material 활성화
    4. (HP Bar 구현 하면서) 해당 Actor 에 Interact Button Component 도 같이 달아보기
    5. LineTrace 했을 때 true면 Interact Button Component 활성화
    6. Interact Button Component 에 해당 Actor의 Rotation을 적용
### BugFix
1. Item->Interact->Destroy (Destroy 할 때 시간이 걸려서 Intertact키를 연타하면 Invalid한 Item이 LineTrace 될 수 있음)
    * 그렇다면 LineTraceChannel 을 ECC_Visibility 로 하니까 Item이 Interact될 때 Channel을 다른걸로 바꿔버리면 되지 않을까?

## PlayerCharacter
### Add Function
* PlayerCharacterState 라는 Actor (혹은 Component)를 만들어서 State를 관리한다.
    * [ ] 캐릭터 사망시 어떻게 처리할 것인가? (현재 Status Component에 bIsDead까지만 있음) (-> 이 참에 Respawn 혹은 죽은 이후에는 어떻게 처리할지 생각)

# 완료한 것들
* PlayerCharacterState 라는 ActorComponent를 만들어서 관리한다.    
    * Actor Component와 그냥 Component의 차이 확인하기 -> ActorComponent 을 사용하기로 정함 (추상적개념이기 때문에)
    * Component에 PlayerState 라는 FStruct 만들기 -> FStruct 따로 만들 필요없이 그냥 PlayerCharacterStatus 라는 Component를 만들었다.
    * CrossHairWidget을 HUDWidget으로 변경하여 거기에 Status를 표시하는 TextBlock을 생성
    * HUDWidget과 CharacterStatusComponent를 PlayerCharacter를 매개체로 연결

* Replicate
    * Character 의 Interact() 를 Client에서도 사용 가능하게 수정함 (그런데 현재 서버에서 안됨)
    

# 깨달은 점
1. Git 을 통해 버전 관리를 할 때는, 항상 visual studio project file 을 다시 generate 시켜줘야한다.
    * 다른 PC에서 작업한 c++ 파일이 여기서 pull 했더니 vs project에 안들어있음
2. Class 의 Constructor 에서는 되도록 멤버 변수를 사용하는 일을 하지 말자 (생성, 초기화 관련된 일만 하자)
    * BeginPlay()를 이용하거나 Init() 함수를 따로 만들어서 사용하자.

3. Post Construct (like BeginPlay)가 필요할 때는 Native Construct 를 override 해서 사용하자!
    * 함수 내부에서 먼저 Super::NaiveConstruct()를 실행 해 준 뒤 Post Construct 처럼 활용

4. Interface 자체에서 구현된 경우 아래와 같이 cast 없이 바로 method 사용 가능
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
    * ex) GetWorld()->GetTimerManager().SetTimer(MyTimerHandler, this, &MyUObject::MyMemberMethod, 10.0f, true);
    * 이 타이머를 가질 FTimerHandler, 실행하는 UObject, 실행하려고 하는 MemberMethod, 타이머 시간 (얼마 뒤에 실행할지), 반복여부, 첫 시작 시간 (안적으면 앞에 시간과 동일)

7. LogUObjectBase: Error: 'this' pointer is invalid. 에러
    * 정말 바보같은 에러다. 만들어져있지 않은 Object에 아마 MyObject.IsValidLowLevelFast()를 실행하면 뜰 것이다.
    * 내 경우 BeginPlay에서 (아직 CreateWidget 하지 않은 )UUserWidget* 에 있는 함수를 사용하려다 자꾸 Access 에러가 떠서 위의 IsValid 함수를 사용했더니 발견되었다.
    * 이 경우에는 해당 함수까지의 경로에 UE_LOG 를 찍어서 어디까지 정상적으로 들어가는지 판별하면 대충 에러의 원인이 보인다.

8. 배열에서 IsNotEmtpy() 를 표현하는 방법
```c++
if (MyArray.Num()) { }
// 이렇게 하면 Num 이 0이면 false로 취급돼서 IsNotEmpty()와 같은 기능을 한다.
```
9. UPROPERTY 를 Replicate 하려면
    1.  ```c++
            // 일단 UPROPERTY에 ReplicatedUsing 지정자를 써야하고 
            // = OnRep_Function 으로 함수를 지정해줘야한다.
            UPROPERTY(ReplicatedUsing = OnRep_MyObject)
            UMyObject MyObject;
        ```
    2.  ```c++
            // 그에 맞는 UFUNCTION() OnRep 함수도 필요
            UFUNCTION()
            void OnRep_MyObejct();
        ```
