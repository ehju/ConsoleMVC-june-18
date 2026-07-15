# MVC (Model-View-Controller) 패턴

## 개요

MVC는 애플리케이션을 세 가지 역할로 분리하여 관심사를 나누는(Separation of Concerns) 소프트웨어 디자인 패턴이다.
데이터/비즈니스 로직(Model), 사용자에게 보여지는 표현(View), 사용자 입력을 처리하고 Model과 View를 중개하는 로직(Controller)을 분리함으로써
각 요소를 독립적으로 개발·테스트·수정할 수 있게 한다.

## 구성 요소

### Model (모델)
- 애플리케이션의 데이터와 비즈니스 로직을 담당한다.
- 데이터의 상태를 관리하고, 상태 변경에 대한 규칙(비즈니스 로직)을 처리한다.
- View나 Controller의 존재를 알지 못한다. 즉, 자신의 데이터가 어떻게 표시되는지 신경 쓰지 않는다.
- 상태가 바뀌면 필요 시 옵저버(콜백/이벤트)를 통해 상위 계층에 변경을 알릴 수 있다.

### View (뷰)
- Model이 가진 데이터를 사용자에게 표시하는 역할만 담당한다 (콘솔 앱에서는 출력/입력 프롬프트).
- 스스로 데이터를 가져오거나 가공하지 않고, Controller로부터 전달받은 데이터만 그린다.
- 사용자의 입력(키보드 등)을 받아 Controller에게 전달하는 창구 역할도 한다.
- Model에 대해 알지 못하며, Model을 직접 참조하지 않는다.

### Controller (컨트롤러)
- Model과 View 사이의 중재자.
- 사용자 입력을 받아 적절한 Model의 동작(메서드 호출)으로 변환한다.
- Model의 상태가 변경되면 View를 갱신하도록 지시한다.
- 애플리케이션의 흐름(메뉴 처리, 입력 검증 등)을 제어한다.

## 데이터 흐름

```
사용자 입력 → View → Controller → Model (상태 변경)
                                     │
                                     ▼
                              변경 알림(콜백)
                                     │
                                     ▼
                        Controller → View (화면 갱신)
```

1. 사용자가 View를 통해 입력한다.
2. View는 입력을 그대로 Controller에 전달한다 (해석하지 않는다).
3. Controller는 입력을 해석하여 Model의 메서드를 호출한다.
4. Model은 데이터를 변경하고, 등록된 리스너(콜백)를 통해 변경 사실을 알린다.
5. Controller(또는 콜백)가 View에게 최신 데이터를 전달하여 화면을 갱신한다.

## 장점

- **관심사 분리**: 데이터, 로직, 표현이 분리되어 코드 이해와 유지보수가 쉬워진다.
- **독립적인 개발/테스트**: Model은 View 없이도 단위 테스트가 가능하다.
- **재사용성**: 같은 Model에 대해 다른 View(예: GUI, 콘솔, 웹)를 붙일 수 있다.
- **확장성**: 새로운 기능 추가 시 영향 범위가 각 계층으로 한정된다.

## 콘솔 애플리케이션에서의 적용

콘솔 프로그램에서는 GUI 프레임워크가 없으므로 다음과 같이 단순화하여 적용한다.

- **Model**: 순수 C++ 클래스. 데이터(예: 목록, 값)와 이를 조작하는 메서드, 변경 통지용 콜백(`std::function`)을 가진다.
- **View**: `std::cin`/`std::cout`을 이용해 메뉴 출력, 데이터 출력, 사용자 입력 수신을 담당하는 클래스. 상태를 갖지 않는다(stateless).
- **Controller**: `Model&`과 `View&`를 참조로 보유하며, 메인 루프에서 View로부터 입력을 받아 Model을 조작하고 View에 결과를 표시하도록 지시한다.
- **main()**: Model, View, Controller 인스턴스를 생성하고 Controller를 실행(`Run()`)하는 진입점 역할만 한다.

이 저장소의 스켈레톤 코드는 위 구조를 그대로 따른다. 다만 클래스 수 증가에 대비해 계층별로 폴더를 분리했다:
`Models/Model.h/.cpp`, `Views/View.h/.cpp`, `Controllers/Controller.h/.cpp`, `main.cpp`.
폴더 분리 배경과 절차는 [MVCpackage.md](./MVCpackage.md) 참고.

## 참고 자료

- [MVC in C++ - Jacob Galam (Medium)](https://jacobgalam.medium.com/mvc-in-c-66497e5d7011)
- [Model-View-Controller – modernescpp](https://www.modernescpp.com/index.php/model-view-controller/)
- [MVC Design Pattern - GeeksforGeeks](https://www.geeksforgeeks.org/system-design/mvc-design-pattern/)
- [MVC architectural pattern for C++ console application (Gist)](https://gist.github.com/sunmeat/40286ad51bd9d478f44f14f4b6073992)
- [Model-View-Controller Explained in C++ - helloacm](https://helloacm.com/model-view-controller-explained-in-c/)
- [Design Patterns - MVC Pattern - TutorialsPoint](https://www.tutorialspoint.com/design_pattern/mvc_pattern.htm)
