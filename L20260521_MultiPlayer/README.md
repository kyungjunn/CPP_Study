# L20260521_MultiPlayer

C++로 밑바닥부터 구현한 TCP 기반 멀티플레이어 게임 서버/클라이언트 프로젝트입니다.
소켓 프로그래밍, 커스텀 바이너리 프로토콜 설계(FlatBuffers), 세션 동기화, DB 연동까지
게임 서버의 핵심 구성요소를 직접 구현하는 것을 목표로 진행했습니다.

## 프로젝트 개요

| 구분 | 내용 |
|---|---|
| 서버 | Winsock2 + `select()` 기반 멀티플렉싱 TCP 서버 (C++) |
| 클라이언트 | SDL2 기반 GUI 클라이언트 (C++) |
| 직렬화 | Google FlatBuffers |
| DB | MySQL (Connector/C++) |
| 빌드 | Visual Studio (.sln / .vcxproj), Windows |

## 아키텍처

```
┌────────────┐   TCP (길이 헤더 + FlatBuffers)   ┌────────────────────┐
│  Client    │ ───────────────────────────────▶ │  Server             │
│  (SDL2)    │ ◀─────────────────────────────── │  (Winsock + select) │
│            │                                    │                      │
│ RecvThread │                                    │  단일 스레드 루프    │
│ SendThread │                                    │  - accept           │
│ Main(SDL)  │                                    │  - recv/dispatch    │
└────────────┘                                    │  - SessionManager   │
                                                    └──────────┬──────────┘
                                                               │
                                                        MySQL (id/pw 인증)
```

- **서버**: `select()`로 다중 소켓을 폴링하는 동기식(blocking, synchronous, polling) 멀티플렉싱 서버. 별도 워커 스레드 없이 단일 루프에서 accept/recv/dispatch를 처리합니다.
- **클라이언트**: 렌더링을 담당하는 메인(SDL 이벤트 루프) 스레드와, 별도의 `RecvThread`/`SendThread`로 구성된 3-스레드 구조입니다.
- **세션 관리**: `SessionManager`가 접속 중인 유저의 소켓, 좌표(X, Y), 색상, 도형(Shape) 상태를 `std::vector<Session>`으로 관리하고, 로그인/이동/색상 변경 시 다른 클라이언트에게 브로드캐스트합니다.

## 네트워크 프로토콜

`NetCommon/UserPacket.fbs` 스키마를 `flatc`로 컴파일하여 `PacketType` union 기반 단일 루트 테이블로 송수신합니다. TCP 스트림은 2바이트 길이 헤더 + FlatBuffers 바이너리로 프레이밍합니다.

| 패킷 | 방향 | 용도 |
|---|---|---|
| `Login` / `Signup` / `Logout` | C2S / S2C | 계정 인증, 회원가입, 로그아웃 |
| `Spawn` | S2C | 신규/기존 오브젝트 생성 브로드캐스트 (위치·색상·모양 포함) |
| `Destroy` | S2C | 오브젝트(플레이어) 제거 |
| `Move` | C2S / S2C | 방향키 입력 → 좌표 갱신 및 브로드캐스트 |
| `ChangeColor` | C2S / S2C | 플레이어 색상 변경 |
| `Chat` | C2S / S2C | 채팅 (스키마 정의, 서버 로직은 일부 미구현) |

## 주요 기능

- 계정 로그인 (MySQL `user` 테이블 조회, PreparedStatement 사용)
- 접속 시 다른 플레이어 스폰 정보 동기화, 종료 시 Destroy 브로드캐스트
- WASD 이동 입력 처리 및 실시간 위치 브로드캐스트
- 플레이어 색상 변경 및 동기화
- SDL2 화면에 접속 중인 플레이어를 사각형으로 렌더링

## 프로젝트 구조

```
Server/       서버 진입점(server.cpp), DB 연동(DBManager)
Client/       SDL2 클라이언트(client.cpp)
NetCommon/    Server/Client가 공유하는 패킷 스키마·직렬화·세션 관리 코드
  ├─ UserPacket.fbs       FlatBuffers 패킷 스키마
  ├─ SessionManager.*     접속 유저 상태 관리
  ├─ NetUtil.*            소켓 send/recv 프레이밍 유틸
  └─ flatbuffers/         FlatBuffers 헤더 라이브러리
```

## 사용 기술 스택

- **언어**: C++
- **네트워킹**: Winsock2 (TCP Socket, `select()`)
- **직렬화**: Google FlatBuffers
- **DB**: MySQL, MySQL Connector/C++ (JDBC 스타일 API)
- **클라이언트 렌더링**: SDL2
- **빌드**: MSBuild (Visual Studio)

## 향후 개선 계획

프로젝트를 학습용으로 진행하며 파악한, 다음 단계로 개선하고자 하는 부분입니다.

- **비밀번호 해싱 도입**: 현재 평문 비교 방식을 bcrypt 등으로 교체
- **DB 접속 정보 외부화**: 소스에 하드코딩된 계정 정보를 설정 파일/환경변수로 분리
- **서버 동시성 개선**: 단일 스레드 `select()` 구조를 IOCP 또는 워커 스레드 풀 기반으로 확장하여 다중 접속 처리량 개선
- **세션 조회 최적화**: `O(n)` 선형 탐색 중인 `SessionManager`를 `unordered_map` 기반으로 전환
- **레거시 코드 정리**: FlatBuffers 도입 이전 JSON 직렬화 프로토타입(`IPacket` 계열), 사용되지 않는 `DBManager`/`C2S_Login` 중복 구현 정리
- **회원가입 플로우 완성**: 클라이언트 측 비활성화된 회원가입 흐름 재연결
- **빌드 구성 정리**: `NetCommon`을 정적 라이브러리로 온전히 링크하도록 프로젝트 참조 정비
