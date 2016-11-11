##16.11.10 회의

###1.	맵 구상 <br>

  -	STAGE 1 전체 맵의 크기 : 3개의 맵으로 구성 <br> <br>
  -	MAP 1 : <br>
    몹 1 리소스(Choco), 몹 2 리소스(Atroce) <br>
    https://drive.google.com/file/d/0BxzeUSJe9TjVWVY5bjdPUEZCd0k/view <br>

  -	MAP 2 : <br>
    등장 몹 - 맵 1의 몹 타입 2-1과 원거리 공격 몹 3-1, 3-2를 추가. (리소스 Archer_Skeleton) 몹 3-2는 원거리 공격을 맞았을 시, 밀림이나 경직등의 상태이상. <br>
    중간보스(리소스 Acient Tree) – 등장 몹을 전부 죽였을 경우 생성. <br>
    구체적인 기획은 맵 1 구현이 끝난 후 <br> 

  -	MAP 3 : <br>
    보스 – 광역, 몹 소환, 직접공격등의 패턴. <br>

###2.	스킬 구상  <br>

  -	우선 공격/방어에 해당하는 스킬 1개씩 먼저 구현하기.
  -	MAP 1, MAP 2에서 스킬 한 개 씩을 배울 수 있도록.
  -	공격 스킬 : WARCRAFT 3의 스톰볼트 (투사체, 몬스터 경직)
  -	방어 스킬 : WARCRAFT 3의 아바타 (체력 뻥튀기, 안밀리기)
  -	추가적으로 전광석화(빠르게 움직여서 밀쳐내기) 이런 거는 만들기 쉬울 듯.

###3.	큰 일정 <br>

  전체 개발 기간 7주 <br>
  1~2 Week : MAP 1 타일 구현. 몹1, 몹 2-1, 2-2 AI, 첫 번째 스킬, 캐릭터 이동 구현. <br>
  2~3 Week : MAP 2, 중간보스, 몹 3 AI, 두 번째 스킬 구현. <br>
  5~6 Week : MAP 3, 보스 AI 구현 <br>
  7~ Week : 디테일, 디버깅 <br>

###4.	세부 일정 <br>

  이번 주말 : 리소스 스프라이트 작업. <br>
  Week 1 목표 : MAP 1 타일, 몹 1, 2 AI. MAP 1, MAP 2간 이동 구현. <br>

  -	분업 : <br>
  	김현우 : 수요일까지 공격 구현. 이후 다른 쪽 헬프 <br>
  	고금성 : MAP 1 타일, 맵 간 이동. <br>
  	이근원 : AI <br>
  + GAINPUT LIB 설치/실험 ( 조이스틱 인풋 라이브러리 ) <br>

	Week 2 목표 : 첫 번째 스킬(스톰볼트) 구현, 메인 페이지 만들기, 몹 피격 / 공격 확인.