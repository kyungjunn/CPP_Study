#include <iostream>
#include "flatbuffers/flatbuffers.h"

#include "monster_generated.h" // Byte Array <-> Object Utility Function			

using namespace std;

int main()
{
	// FlatBuffer 데이터를 생성하기 위한 Builder 객체
	flatbuffers::FlatBufferBuilder builder;

	// Monster 객체 생성
	// CreateMonsterDirect 함수는 monster.fbs 스키마 기반으로
	// flatc 컴파일러가 자동 생성한 함수
	auto monster = CreateMonsterDirect(builder, "Abominable Snowman", 100);

	// FlatBuffer 데이터 생성 완료 처리
	builder.Finish(monster);

	// 읽어오는 코드, 생성된 FlatBuffer의 실제 메모리 주소 반환
	const uint8_t* flatbuffer = builder.GetBufferPointer();

	// send

	// recv
	// FlatBuffer 데이터를 Monster 객체처럼 읽기
	const Monster* snowman = GetMonster(flatbuffer);

	// 출력해보기
	cout << snowman->name()->c_str() << endl;
	cout << snowman->health() << endl;


	return 0;
}
