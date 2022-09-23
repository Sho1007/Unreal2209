# 진행 중
Inventory Tut. 12

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
1. PlayerCharacterState 라는 Actor (혹은 Component)를 만들어서 State를 관리한다.
    1. Actor Component와 그냥 Component의 차이 확인하기 (어떤걸 사용해서 구현할지 정해야하기 때문에)
    2. Component에 PlayerState 라는 FStruct 만들기
        * Health, Hunger, Temperature, 등등 필요한 변수와 그 변수의 Get, Set 구현
    3. .. Health <= 0 이면 죽는다던가 하는 부가적 기능들 구현 (-> 이 참에 Respawn 혹은 죽은 이후에는 어떻게 처리할지 생각)

# 완료한 것들

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
5. 
