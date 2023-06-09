#include "hw3.h" //채용정보 시스템을 구동하기 위한 헤더파일을 가져온다


/* 함수이름: main
   기능: 채용정보 시스템 객체를 사용헤 채용 정보 시스템을 실행하는 기능을 수행한다.


   매개변수: 없음
   반환값: 0이면 정상 종료, 그 외의 값이 반환되면 비정상 종료된다.

   작성날짜 : 2023/05/21
   작성자 : 박시홍
*/
int main() {
	System sys; //프로그램을 실행할 System객체 생성
	sys.doTask(); //프로그램의 메뉴 창을 띄우고, 거기서 입력된 값에 의해 다른 기능을 수행한다.
	fout.close(); //output.txt 파일 닫기
	fin.close(); //input.txt 파일 닫기

	return 0;
}