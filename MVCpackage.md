# MVC 패키지(폴더) 분리 계획

현재 `ConsoleMVC/` 폴더에는 `Model.h/.cpp`, `View.h/.cpp`, `Controller.h/.cpp`, `main.cpp`가 평평하게(flat) 나열되어 있다.
클래스 수가 늘어날 것을 대비해, 계층(Model/View/Controller)별로 폴더를 나누고 프로젝트 파일까지 갱신하는 계획이다.

## 목표 구조

```
ConsoleMVC/
├── Models/
│   └── Model.h / Model.cpp
├── Views/
│   └── View.h / View.cpp
├── Controllers/
│   └── Controller.h / Controller.cpp
├── Common/            (계층 간 공유 타입/유틸이 생기면 추가)
└── main.cpp
```

## 단계별 계획

### 1. 디스크 상의 실제 폴더/파일 이동
- `ConsoleMVC/Models/`, `ConsoleMVC/Views/`, `ConsoleMVC/Controllers/` 폴더 생성
- `Model.h`, `Model.cpp` → `Models/`
- `View.h`, `View.cpp` → `Views/`
- `Controller.h`, `Controller.cpp` → `Controllers/`
- `main.cpp`는 최상위(`ConsoleMVC/`)에 유지

### 2. `#include` 경로 수정
- 각 `.cpp`/`.h` 파일 내 상호 include 경로를 폴더 상대경로로 변경
  - 예: `Controller.h`에서 `#include "Models/Model.h"`, `#include "Views/View.h"`
  - `main.cpp`에서 `#include "Controllers/Controller.h"` 등
- 프로젝트 속성의 "추가 포함 디렉터리"에 `$(ProjectDir)`가 포함되어 있는지 확인 (상대경로 include가 정상 동작하도록)

### 3. `.vcxproj` / `.vcxproj.filters` 갱신
- `ConsoleMVC.vcxproj`의 `<ClInclude>`/`<ClCompile>` 항목 경로를 새 폴더 경로로 수정
  (예: `<ClInclude Include="Model.h" />` → `<ClInclude Include="Models\Model.h" />`)
- `ConsoleMVC.vcxproj.filters`에 `Models`, `Views`, `Controllers` 필터(Solution Explorer 가상 폴더)를 추가하고, 각 파일을 해당 필터에 매핑
  - 주의: Solution Explorer에서 필터만 만들고 파일을 안 옮기면 실제 디스크 구조와 어긋나므로, 반드시 물리적 이동과 병행

### 4. 네임스페이스 도입 검토
- 계층별 이름 충돌 방지를 위해 `namespace mvc::model`, `namespace mvc::view`, `namespace mvc::controller` 도입 여부 결정
- 현재는 클래스가 계층당 1개뿐이므로 당장은 생략 가능. 계층당 클래스가 2개 이상으로 늘어나는 시점에 도입 권장

### 5. 빌드 검증
- Visual Studio에서 솔루션을 다시 로드하고 빌드하여 include 경로 오류/누락 파일 여부 확인
- 기존 동작(메뉴 표시, 아이템 추가/삭제/조회)이 동일하게 동작하는지 실행 확인

### 6. 문서 갱신
- `MVC.md`의 "이 저장소의 스켈레톤 코드는 위 구조를 그대로 따른다" 부분을 새 폴더 구조에 맞게 수정

## 향후 확장 시 고려사항 (지금 단계에서는 미적용)

- View/Controller 구현체가 여러 종류로 늘어나면 `IView`, `IModel` 같은 추상 인터페이스 도입
- 계층별 클래스가 많아지면 각 폴더 내부에 다시 하위 폴더로 세분화 (예: `Models/Item/`, `Models/User/`)
