# Unreal Portfolio Todo List

## Now Processing
Inventory6. PlayerCharacter->AddItem() 해서 InventorWidget->Grid->AddChild() 했는데 FItemData는 잘 넘어오는데, WidgetImag가 안보임
1. ItemWidget 이 잘 생성되는지 확인
2. Grid 가 Refresh 안돼서 그런걸 수도 있으니 영상 계속 시청 (현재 8:18)
3. Grid이름이 Gird (i위치 다름) 으로 되어있으니 InventoryWidget (c++, blueprint) 둘다 수정 필요


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