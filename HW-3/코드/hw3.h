#ifndef HW3_H
#define HW3_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdlib.h>
#include <map>

using namespace std;

#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt" //입력 파일 이름 정의
#define OUTPUT_FILE_NAME "output.txt" //출력 파일 이름 정의


static ifstream fin; //파일 입력 관련 전역변수
static ofstream fout; //파일 출력 관련 전역변수

//채용 정보 시스템과 관련된 클래스들을 전방선언한다.
class System;
class SignInUI;
class SignIn;
class SignOut;
class SignOutUI;
class LogIn;
class LogInUI;
class LogOut;
class LogOutUI;
class RegisterRecruitmentInfo;
class RegisterRecruitmentInfoUI;
class InquireRecruitmentInfo;
class InquireRecruitmentInfoUI;
class CancelApplicationInfoUI;
class CancelApplicationInfo;
class ViewStatisticsOfRegisteredRecruitmentInfo;
class ViewStatisticsOfRegisteredRecruitmentInfoUI;
class ViewStatisticsOfAppliedInfo;
class ViewStatisticsOfAppliedInfoUI;
class Client;
class ClientList;
class GeneralClientList;
class CompanyClientList;
class GeneralClient;
class CompanyClient;
class RecruitmentInfo;
class SearchRecruitmentInfoUI;
class SearchRecruitmentInfo;
class ApplyForRecruitmentInfoUI;
class ApplyForRecruitmentInfo;

/*
클래스 이름 : System
클래스 멤버 변수:  -

기능 : 채용 정보 시스템에 대한 다음과 같은 기능을 구현함


	< public 멤버함수 >
	 1. void doTask()
	   -> 파일에서 입력받은 정보에 따라 별도의 기능들을 수행한다.


작성날짜 : 2023/05/31
작성자 : 박시홍
*/
class System
{
public:
	void doTask();

};



/*
클래스 이름 : Client <Entity 클래스>
클래스 멤버변수: int type / string id / string pw / bool isLogIn
클래스 멤버함수: 
				Client(int type, string name, string id, string pw);  //회원 객체의 생성자
				string getId(); //회원의 id값 반환
				string getPw(); //회원의 pw값 반환
				bool getLogInStatus(); //회원의 로그인 상태값 반환 : true 또는 false
				void changeLogInStatus(); //회원의 로그인 상태값 바꿔주기 : true->false / false->true
				int getType(); //회원의 type값 반환 : 1->회사회원 2->일반회원
				string getName(); //회원의 이름 반환
작성날짜 : 2023/05/21
작성자 : 박시홍
*/
class Client
{
private:
	int type; //회원의 type-> 1. 회사회원 / 2. 일반회원
	string id;//회원의 id
	string pw;//회원의 pw 
	string name;//회원의 이름
	//string _num;//회원이 가진 번호 -> 회사회원:사업자번호 / 일반회원: 주민번호
	bool isLogIn; //회원의 login 상태 정보 -> true: 로그인 상태 / false: 로그아웃 상태

public:
	Client(int type, string name, string id, string pw);  //회원 객체의 생성자
	string getId(); //회원의 id값 반환
	string getPw(); //회원의 pw값 반환
	bool getLogInStatus(); //회원의 로그인 상태값 반환 : true 또는 false
	void changeLogInStatus(); //회원의 로그인 상태값 바꿔주기 : true->false / false->true
	//void destroy();
	int getType(); //회원의 type값 반환 : 1->회사회원 2->일반회원
	string getName(); //회원의 이름 반환
};




/*
클래스 이름 : GeneralClient <Entity 클래스> : Client 클래스를 상속함 -> 주민번호 필드만 따로 가짐
클래스 멤버변수: string rrn / vector<RecruitmentInfo*> appliedList
클래스 멤버함수: GeneralClient(int type, string name, string num, string id, string pw); //일반회원 객체의 생성자
				void addApplication(RecruitmentInfo* ri);
				vector<RecruitmentInfo*> getListAppliedInfo();//여기부터 작업하기
				void subApplication(string bn);
				
작성날짜 : 2023/05/21
작성자 : 박시홍
*/
class GeneralClient : public Client
{
private:
	string rrn; //일반회원의 주민번호
	vector<RecruitmentInfo*> appliedList;//해당 일반회원이 지원한 채용공고 목록

public:
	
	GeneralClient(int type, string name, string num, string id, string pw); //일반회원 객체의 생성자
	void addApplication(RecruitmentInfo* ri);
	vector<RecruitmentInfo*> getListAppliedInfo();//여기부터 작업하기
	void subApplication(string bn);

};




/*
클래스 이름 : CompanyClient <Entity 클래스> : Client 클래스를 상속함 -> 사업자 번호 필드만 따로 가짐
클래스 멤버변수: string bn / vector<RecruitmentInfo*> registeredList;
클래스 멤버함수:
				CompanyClient(int type, string name, string num, string id, string pw); //회사회원 객체의 생성자
				RecruitmentInfo* addNewRecruitInfo(string _task, int expectedApplicantNum, string _finishDate); // 채용 정보 생성하기
				string getbn(); // 사업자정보 반환하기
				vector<RecruitmentInfo*> getListRegisteredInfo(); //회사회원이 올린 채용정보 반환하기
작성날짜 : 2023/05/21
작성자 : 박시홍
*/
class CompanyClient : public Client
{
private:
	string bn; //회사회원의 사업자 번호
	vector<RecruitmentInfo*> registeredList; //회사회원이 등록한 채용정보 리스트
public:
	CompanyClient(int type, string name, string num, string id, string pw); //회사회원 객체의 생성자
	RecruitmentInfo* addNewRecruitInfo(string _task, int expectedApplicantNum, string _finishDate); // 채용 정보 생성하기
	string getbn(); // 사업자정보 반환하기
	vector<RecruitmentInfo*> getListRegisteredInfo(); //회사회원이 올린 채용정보 반환하기


};




/*
클래스 이름 : ClientList <Collection 클래스> : 모든 Client들에 대한 포인터들을 저장함
클래스 멤버변수: vector<Client*> cList
클래스 멤버함수:
				void addClient(Client* C); //ClientList의 attribute인 cList에 새로 회원가입한 회원 정보를 넣어줌
				int size(); //cList의 벡터 크기 반환
				vector<Client*> getClientList(); //cList에 대한 모든 client객체들의 리스트를 반환
				void destroy(int idx); //해당 인덱스의 client 객체를 cList에서 지움
작성날짜 : 2023/05/21
작성자 : 박시홍
*/
class ClientList
{
private:
	vector<Client*> cList; //Client 포인터 배열

public:
	void addClient(Client* C); //ClientList의 attribute인 cList에 새로 회원가입한 회원 정보를 넣어줌

	int size(); //cList의 벡터 크기 반환

	vector<Client*> getClientList(); //cList에 대한 모든 client객체들의 리스트를 반환

	void destroy(int idx); //해당 인덱스의 client 객체를 cList에서 지움

};




/*
클래스 이름 : GeneralClientList <Collection 클래스> : 모든 GeneralClient들에 대한 포인터들을 저장함
			-> ex) 일반회원의 경우, ClientList에도 포함되어있고, GeneralClientList에도 포함되어있다
클래스 멤버변수: vector<GeneralClient*> gCList
클래스 멤버함수:
				void addGeneralClient(GeneralClient* C); //GeneralClientList의 attribute인 gCList에 새로 회원가입한 일반 회원 정보를 넣어줌
				void destroy(string id); //해당 id값을 지닌 GeneralClient 객체를 gCList에서 지움
				GeneralClient* findById(string id); //일반회원 리스트에서 id값을 바탕으로 일반회원을 찾아서 반환한다.
작성날짜 : 2023/05/21
작성자 : 박시홍
*/
class GeneralClientList
{
private:
	vector<GeneralClient*> gCList; // GeneralClient 포인터 배열
public:

	void addGeneralClient(GeneralClient* C); //GeneralClientList의 attribute인 gCList에 새로 회원가입한 일반 회원 정보를 넣어줌
	void destroy(string id); //해당 id값을 지닌 GeneralClient 객체를 gCList에서 지움
	GeneralClient* findById(string id); //일반회원 리스트에서 id값을 바탕으로 일반회원을 찾아서 반환한다.
};


/*
클래스 이름 : CompanyClientList <Collection 클래스> : 모든 CompanyClient들에 대한 포인터들을 저장함
			-> ex) 회사회원의 경우, ClientList에도 포함되어있고, CompanyClientList에도 포함되어있다
클래스 멤버변수: vector<CompanyClient*> cCList; // CompanyClient 포인터 배열
클래스 멤버함수:
				void addCompanyClient(CompanyClient* C);  //CompanyClientList의 attribute인 cCList에 새로 회원가입한 회사 회원 정보를 넣어줌
				void destroy(string id); //해당 id값을 지닌 CompanyClient 객체를 cCList에서 지움
				CompanyClient* findById(string id); 회사회원의 id값을 바탕으로 회사회원의 리스트에서 회사회원을 찾아 반환한다.
작성날짜 : 2023/05/31
작성자 : 박시홍
*/
class CompanyClientList
{
private:
	vector<CompanyClient*> cCList; // CompanyClient 포인터 배열
public:
	void addCompanyClient(CompanyClient* C);  //CompanyClientList의 attribute인 cCList에 새로 회원가입한 회사 회원 정보를 넣어줌
	void destroy(string id); //해당 id값을 지닌 CompanyClient 객체를 cCList에서 지움
	CompanyClient* findById(string id); //회사회원의 id값을 바탕으로 회사회원의 리스트에서 회사회원을 찾아 반환한다.
};


/*
클래스 이름 : RecruitmentInfo <Entity 클래스> 채용정보객체
클래스 멤버변수: string companyName / string bn / string task / int numOfApplicant / int expectedApplicantNum / string finishDate
클래스 멤버함수: RecruitmentInfo(string companyName, string bn, string task, int expectedApplicantNum, string finishDate)
				 string getName()const//compare > 작성할때 읽기전용으로만 읽을 수 있음
				 string getBn()
				 string getTask()
				 int getApplicantNum()
				 int getExpectedApplicantNum()
				 string getFinishDate()
				 void addApplicantToRecruitment()
				 void subApplicantToRecruitment()
작성날짜 : 2023/05/22
작성자 : 김민정
*/
class RecruitmentInfo {
private:
	string companyName;
	string bn;
	string task;
	int numOfApplicant;
	int expectedApplicantNum;
	string finishDate;

public:
	RecruitmentInfo(string companyName, string bn, string task, int expectedApplicantNum, string finishDate);
	string getName()const;
	string getBn();
	string getTask();
	int getApplicantNum();
	int getExpectedApplicantNum();
	string getFinishDate();
	void addApplicantToRecruitment();
	void subApplicantToRecruitment();
};

/*
클래스 이름 : RecruitmentInfoList <Collection 클래스> : 모든 RecruitmentInfo에 대한 포인터들 저장
클래스 멤버변수: vector<RecruitmentInfo*> rCList > GeneralClient 포인터 배열
클래스 멤버함수: void setRecruitmentInfo(vector<RecruitmentInfo*> riList)
				 vector<RecruitmentInfo*> getRIList()const
				 void addNewRecruitmentInfoList(RecruitmentInfo* ri)
				 RecruitmentInfo* findByName(string companyName)
				 RecruitmentInfo* findByNum(string bn)
작성날짜 : 2023/05/22
작성자 : 김민정
*/
class RecruitmentInfoList {
private:
	vector<RecruitmentInfo*> rCList;

public:
	void setRecruitmentInfo(vector<RecruitmentInfo*> riList);
	vector<RecruitmentInfo*> getRIList()const;
	void addNewRecruitmentInfoList(RecruitmentInfo* ri);
	RecruitmentInfo* findByName(string companyName);
	RecruitmentInfo* findByNum(string bn);
};

/*
클래스 이름 : SignInUI <Boundary 클래스> : 회원 가입과 관련된 interface를 담당한다.
클래스 멤버변수: SignIn* signIn / int type / string name / string num / string id / string pw
클래스 멤버함수:
				SignInUI(SignIn* signIn); //바운더리 클래스의 생성자-> 컨트롤 클래스의 레퍼런스를 attribute로 가짐
				void startInterface(); //회원 유형과 정보를 입력하라는 화면을 보여줌
				void fillInfo(); //각 회원에게 필요 정보를 입력받고, 컨트롤 클래스에게 회원가입하라는 addNewClient함수 호출함
작성날짜 : 2023/05/21
작성자 : 박시홍
*/
class SignInUI {
private:

	SignIn* signIn; //회원 가입과 관련된 컨트롤 클래스의 레퍼런스를 attribute로 가진다. -> 이를 통해 control 클래스의 public 멤버함수 호출 가능
	int type; //회원이 입력한 회원 type값
	string name; //회원이 입력한 이름/회사이름
	string num;  //회원이 입력한 주민번호/사업자번호
	string id; //회원이 입력한 id
	string pw; //회원이 입력한 pw



public:
	SignInUI(SignIn* signIn); //바운더리 클래스의 생성자-> 컨트롤 클래스의 레퍼런스를 attribute로 가짐
	void startInterface(); //회원 유형과 정보를 입력하라는 화면을 보여줌
	void fillInfo(); //각 회원에게 필요 정보를 입력받고, 컨트롤 클래스에게 회원가입하라는 addNewClient함수 호출함


};

/*
클래스 이름 : SignIn <Control 클래스> : 회원 가입과 관련된 control을 담당한다.
클래스 멤버변수: SignInUI* signInUI / ClientList* cList / CompanyClientList* ccList / GeneralClientList* gcList
클래스 멤버함수:
				SignIn(ClientList* list, GeneralClientList* gcList, CompanyClientList* ccList); 
				//컨트롤 클래스의 생성자-> 바운더리 클래스의 레퍼런스를 attribute로 가짐
				void addNewClient(int type, string name, string num, string id, string pw); 
				//바운더리 클래스에서 매개변수로 받은 회원의 정보를 이용해 회원 리스트에 저장하고, 회원의 타입에 따라 일반회원/회사회원의 리스트에 저장한다. 

작성날짜 : 2023/05/21
작성자 : 박시홍
*/
class SignIn {
	SignInUI* signInUI; //바운더리 클래스의 레퍼런스를 저장할 공간
	ClientList* cList; //회원들의 정보를 지닌 collection class의 instance
	CompanyClientList* ccList; //회사 회원들의 정보를 지닌 collection class의 instance
	GeneralClientList* gcList; //일반 회원들의 정보를 지닌 collection class의 instance

public:
	SignIn(ClientList* list, GeneralClientList* gcList, CompanyClientList* ccList); //컨트롤 클래스의 생성자-> 바운더리 클래스의 레퍼런스를 attribute로 가짐
	void addNewClient(int type, string name, string num, string id, string pw); //바운더리 클래스에서 매개변수로 받은 회원의 정보를 이용해 회원 리스트에 저장하고, 회원의 타입에 따라 일반회원/회사회원의 리스트에 저장한다. 
};


/*
클래스 이름 : LogIn <Control 클래스> : 로그인과 관련된 control을 담당한다.
클래스 멤버변수: LogInUI* logInUI / ClientList* cList / CompanyClientList* ccList / GeneralClientList* gcList / Client* curLogInClient
클래스 멤버함수:
				LogIn(ClientList* list, GeneralClientList* gcList, CompanyClientList* ccList); 
				//컨트롤 클래스의 생성자-> 바운더리 클래스의 레퍼런스를 attribute로 가짐

				void tryLogIn(string id, string pw); 
				//로그인이 가능한 경우, client의 isLogIn필드를 false에서 true로 바꿔준다

				Client* getLogInClient(); 
				//현재 로그인된 회원이 누구인지 반환해주는 함수
작성날짜 : 2023/05/21
작성자 : 박시홍
*/
class LogIn {
private:

	LogInUI* logInUI; //바운더리 클래스의 레퍼런스를 저장할 공간
	ClientList* cList; //회원들의 정보를 지닌 collection class의 instance
	CompanyClientList* ccList; //회사 회원들의 정보를 지닌 collection class의 instance
	GeneralClientList* gcList; //일반 회원들의 정보를 지닌 collection class의 instance
	Client* curLogInClient; //현재 로그인된 회원의 reference를 담을 공간

public:
	LogIn(ClientList* list, GeneralClientList* gcList, CompanyClientList* ccList); //컨트롤 클래스의 생성자-> 바운더리 클래스의 레퍼런스를 attribute로 가짐
	void tryLogIn(string id, string pw); //로그인이 가능한 경우, client의 isLogIn필드를 false에서 true로 바꿔준다
	Client* getLogInClient(); //현재 로그인된 회원이 누구인지 반환해주는 함수
};


/*
클래스 이름 : LogInUI <Boundary 클래스> : 로그인과 관련된 interface를 담당한다.
클래스 멤버변수: LogIn* logIn / string id / string pw
클래스 멤버함수: 
				LogInUI(LogIn* logIn); //바운더리 클래스의 생성자-> 컨트롤 클래스의 레퍼런스를 attribute로 가짐
				void startInterface();  //회원 id와 pw를 입력하라는 화면을 보여줌
				void fillIDPW(); //각 회원에게 필요 정보를 입력받고, 컨트롤 클래스에게 로그인 시도하라는 tryLogIn 함수 호출함
작성날짜 : 2023/05/21
작성자 : 박시홍
*/
class LogInUI {
private:

	LogIn* logIn; //컨트롤 클래스의 레퍼런스를 저장할 공간
	string id; //회원이 입력한 id
	string pw; //회원이 입력한 pw



public:
	LogInUI(LogIn* logIn); //바운더리 클래스의 생성자-> 컨트롤 클래스의 레퍼런스를 attribute로 가짐
	void startInterface();  //회원 id와 pw를 입력하라는 화면을 보여줌
	void fillIDPW(); //각 회원에게 필요 정보를 입력받고, 컨트롤 클래스에게 로그인 시도하라는 tryLogIn 함수 호출함


};


/*
클래스 이름 : LogOut <Control 클래스> : 로그아웃과 관련된 control을 담당한다.
클래스 멤버변수: LogOutUI* logOutUI / ClientList* cList / CompanyClientList* ccList / GeneralClientList* gcList / Client* curLogInClient
클래스 멤버함수: 
				private: void changeLogInStatus(Client* client); //현재 로그인되어있는 계정을 로그아웃 시키는 기능을 함
				LogOut(ClientList* list, GeneralClientList* gcList, CompanyClientList* ccList, Client* client); //컨트롤 클래스의 생성자-> 바운더리 클래스의 레퍼런스를 attribute로 가짐
작성날짜 : 2023/05/21
작성자 : 박시홍
*/
class LogOut {
private:

	LogOutUI* logOutUI; //바운더리 클래스의 레퍼런스를 저장할 공간
	ClientList* cList; //회원들의 정보를 지닌 collection class의 instance
	CompanyClientList* ccList; //회사 회원들의 정보를 지닌 collection class의 instance
	GeneralClientList* gcList; //일반 회원들의 정보를 지닌 collection class의 instance
	Client* curLogInClient; //로그인 객체가 매개변수로 전달해준 현재 로그인 된 client계정을 저장할 공간
	void changeLogInStatus(Client* client); //현재 로그인되어있는 계정을 로그아웃 시키는 기능을 함

public:
	LogOut(ClientList* list, GeneralClientList* gcList, CompanyClientList* ccList, Client* client); //컨트롤 클래스의 생성자-> 바운더리 클래스의 레퍼런스를 attribute로 가짐


};


/*
클래스 이름 : LogOutUI <Boundary 클래스> : 로그아웃과 관련된 interface를 담당한다.
클래스 멤버변수: LogOut* logOut
클래스 멤버함수:
				LogOutUI(LogOut* signOut); //바운더리 클래스의 생성자-> 컨트롤 클래스의 레퍼런스를 attribute로 가짐
				void startInterface(string id, bool flag); //로그아웃되었다는 메세지를 화면에 보여줌
작성날짜 : 2023/05/21
작성자 : 박시홍
*/
class LogOutUI {
private:

	LogOut* logOut; //컨트롤 클래스의 레퍼런스를 저장할 공간


public:
	LogOutUI(LogOut* signOut); //바운더리 클래스의 생성자-> 컨트롤 클래스의 레퍼런스를 attribute로 가짐
	void startInterface(string id, bool flag); //로그아웃되었다는 메세지를 화면에 보여줌


};


/*
클래스 이름 : SignOut <Control 클래스> : 회원탈퇴와 관련된 control을 담당한다.
클래스 멤버변수: SignOutUI* signOutUI / ClientList* cList / CompanyClientList* ccList / GeneralClientList* gcList / Client* curLogInClient
클래스 멤버함수:
				private: void destroy(Client* client); //로그인 되어있는 해당 회원을 탈퇴시킴
				SignOut(ClientList* list, GeneralClientList* gcList, CompanyClientList* ccList, Client* client);  
				//컨트롤 클래스의 생성자-> 바운더리 클래스의 레퍼런스를 attribute로 가짐
작성날짜 : 2023/05/31
작성자 : 박시홍
*/
class SignOut {
private:

	SignOutUI* signOutUI; //바운더리 클래스의 레퍼런스를 저장할 공간
	ClientList* cList; //회원들의 정보를 지닌 collection class의 instance
	CompanyClientList* ccList; //회사 회원들의 정보를 지닌 collection class의 instance
	GeneralClientList* gcList; //일반 회원들의 정보를 지닌 collection class의 instance
	Client* curLogInClient; //로그인 객체가 매개변수로 전달해준 현재 로그인 된 client계정을 저장할 공간
	void destroy(Client* client); //로그인 되어있는 해당 회원을 탈퇴시킴

public:
	SignOut(ClientList* list, GeneralClientList* gcList, CompanyClientList* ccList, Client* client);  //컨트롤 클래스의 생성자-> 바운더리 클래스의 레퍼런스를 attribute로 가짐

};


/*
클래스 이름 : SignOutUI <Boundary 클래스> : 회원탈퇴와 관련된 interface를 담당한다.
클래스 멤버변수: SignOut* signOut
클래스 멤버함수:
			SignOutUI(SignOut* signOut);  //바운더리 클래스의 생성자-> 컨트롤 클래스의 레퍼런스를 attribute로 가짐
			void startInterface(string id, bool flag); //회원탈퇴되었다는 메세지를 화면에 보여줌	
작성날짜 : 2023/05/21
작성자 : 박시홍
*/
class SignOutUI {
private:

	SignOut* signOut;


public:
	SignOutUI(SignOut* signOut);  //바운더리 클래스의 생성자-> 컨트롤 클래스의 레퍼런스를 attribute로 가짐
	void startInterface(string id, bool flag); //회원탈퇴되었다는 메세지를 화면에 보여줌


};


/*
클래스 이름 : RegisterRecruitmentInfo <Control 클래스>: 채용 등록을 담당합니다.
클래스 멤버변수: RegisterRecruitmentInfoUI* registerRecruitmentInfoUI > 바운더리 클래스의 레퍼런스를 저장합니다.
				 CompanyClient* companyClient > 회사 회원
				 RecruitmentInfo* registeredList
				 RecruitmentInfoList* recruitmentInfoList
클래스 멤버함수: RegisterRecruitmentInfo(CompanyClient* companyClient, RecruitmentInfoList* recruitmentInfoList)
				 void addNewRecruitmentInfo(string task, int expectedApplicantNum, string finishDate) > recruitment info에 정보를 추가합니다.
				 RecruitmentInfoList* getRecruitmentInfoList()
				 RecruitmentInfo* getRegisteredList()
작성날짜 : 2023/05/22
작성자 : 김민정
*/
class RegisterRecruitmentInfo
{
private:
	RegisterRecruitmentInfoUI* registerRecruitmentInfoUI;
	CompanyClient* companyClient;
	RecruitmentInfo* registeredList;
	RecruitmentInfoList* recruitmentInfoList;

public:
	RegisterRecruitmentInfo(CompanyClient* companyClient, RecruitmentInfoList* recruitmentInfoList);
	void addNewRecruitmentInfo(string task, int expectedApplicantNum, string finishDate);
	RecruitmentInfoList* getRecruitmentInfoList();
	RecruitmentInfo* getRegisteredList();
};


/*
클래스 이름 : RegisterRecruitmentInfoUI <Boundary 클래스>: 채용 등록을 담당합니다.
클래스 멤버변수: RegisterRecruitmentInfo* registerRecruitmentInfo
				 CompanyClient* companyClient
클래스 멤버함수: RegisterRecruitmentInfoUI(RegisterRecruitmentInfo* registerRecruitmentInfo, CompanyClient* companyClient)
				 void startInterface() > 입력값을 읽어들입니다.
				 void result(string task, int expectedApplicantNum, string finishDate) > 사용자의 화면에 결과를 표시합니다.
				 void registerInput() > 파일에서 입력값을 받아들입니다.
작성날짜 : 2023/05/21
작성자 : 김민정
*/
class RegisterRecruitmentInfoUI
{
private:
	RegisterRecruitmentInfo* registerRecruitmentInfo;
	CompanyClient* companyClient;

public:
	RegisterRecruitmentInfoUI(RegisterRecruitmentInfo* registerRecruitmentInfo, CompanyClient* companyClient);
	void startInterface(); 
	void result(string task, int expectedApplicantNum, string finishDate); 
	void registerInput(); 
};

/*
클래스 이름 : InquireRecruitmentInfo <Control 클래스>: 채용 조회를 담당합니다.
클래스 멤버변수:CompanyClient* companyClient
클래스 멤버함수:InquireRecruitmentInfo(CompanyClient* companyClient)
작성날짜 : 2023/05/22
작성자 : 김민정
*/
class InquireRecruitmentInfo
{
private:
	CompanyClient* companyClient;
public:
	InquireRecruitmentInfo(CompanyClient* companyClient);

};

/*
클래스 이름 : InquireRecruitmentInfoUI <Boundary 클래스>: 채용 조회를 담당합니다.
클래스 멤버변수: InquireRecruitmentInfo* inquireRecruitmentInfo > 바운더리 클래스의 레퍼런스를 저장할 공간입니다.
클래스 멤버함수: InquireRecruitmentInfoUI(InquireRecruitmentInfo* inquireRecruitmentInfo)
				 void startInterface(vector<RecruitmentInfo*> riList) > 사용자인 회사 회원의 RecruitmentInfo를 보여줍니다.
작성날짜 : 2023/05/22
작성자 : 김민정
*/
class InquireRecruitmentInfoUI
{
private:
	InquireRecruitmentInfo* inquireRecruitmentInfo;
public:
	InquireRecruitmentInfoUI(InquireRecruitmentInfo* inquireRecruitmentInfo);
	void startInterface(vector<RecruitmentInfo*> riList);
};



/*
클래스이름:
클래스 멤버변수:
	SearchRecruitmentInfo* searchRecruitmentInfo: Control클래스의 Reference
	string companyName; 회원이 입력한 회사이름
클래스 멤버함수:
	void startInterface(): 검색창을 입력할 화면을 보여주는 함수
	void fillInput(): 검색을 받는 함수
작성 날짜: 2023/05/22
작성자: 신유승
*/

class SearchRecruitmentInfoUI {
private:
	SearchRecruitmentInfo* searchRecruitmentInfo;
	string companyName;
public:
	SearchRecruitmentInfoUI(SearchRecruitmentInfo* searchRecruitmentInfo);
	void startInterface();
	void fillInput();


};
/*
클래스이름 : SearchRecruitmentInfo <Control 클래스>: 채용정보검색을 담당함.
클래스 멤버변수: 
	RecruitmentInfoList *riList; 현재 세션에서 등록된 채용공고목록
	string companyName: 회원이 검색한 회사이름
	RecruitmentInfo* result: 회원이 검색한 회사의 채용목록
클래스 멤버함수:
	RecruitmentInfo* getResult(): 검색 결과 RecruitmentInfo를 반환하는 함수
	void searchRecruitmentInfoListByComName(string name): 등록된 채용공고에서 검색된 회사이름으로 채용공고를 찾는 함수
작성 날짜: 2023/05/22
작성자: 신유승
*/
class SearchRecruitmentInfo {
private:
	RecruitmentInfoList* riList;
	string companyName;
	RecruitmentInfo* result;
	SearchRecruitmentInfoUI* searchRecruitmentInfoUI;
public:
	SearchRecruitmentInfo(RecruitmentInfoList* riList);
	RecruitmentInfo* getResult();
	void searchRecruitmentInfoListByComName(string name);
};
	

/*
클래스 이름: ApplyForRecruitmentInfoUI <Boundary> 클래스: 채용 지원을 담당함
클래스 멤버변수:
	string bn; 회원이 지원할 회사의 사업자 번호
	ApplyForRecruitmentInfo* applyForRecruitmentInfo: Control Class의 Reference
클래스 멤버함수:
	void startInterface(RecruitmentInfoList* riList); 등록된 채용정보 리스트를 보여주는 함수
	void fillComName(); 일반 회원이 지원할 회사의 사업자 번호를 입력하는 함수
*/
class ApplyForRecruitmentInfoUI {
private:
	string bn;
	ApplyForRecruitmentInfo* applyForRecruitmentInfo;
public:
	ApplyForRecruitmentInfoUI(ApplyForRecruitmentInfo* applyForRecruitmentInfo);
	void startInterface(RecruitmentInfoList* riList);
	void fillComName();
};

/*
클래스이름: ApplyForRecruitmentInfo <Control> 클래스 : 채용 지원을 담당함
클래스 멤버변수:
	GeneralClient* gClient: 지원하려고하는 일반 회원
	RecruitmentInfoList* riList: 현재 등록된 채용 공고 목록
	RecruitmentInfo* appliedRecruitmentInfo: 로그인한 일반회원이 지원한 채용공고

클래스 멤버함수:
	void addApplicant(string bn): bn을 사업자번호로 가진 채용공고에 지원하는 기능
작성날짜: 2023/05/23
작성자: 신유승
*/

class ApplyForRecruitmentInfo {
private:
	GeneralClient* gClient;
	RecruitmentInfoList* riList;
	RecruitmentInfo* appliedRecruitmentInfo;
	ApplyForRecruitmentInfoUI* applyForRecruitmentInfoUI;

public:
	ApplyForRecruitmentInfo(GeneralClient* gClient, RecruitmentInfoList* riList);
	void addApplicant(string bn);
};

/*
클래스 이름: InquireApplicationInfoUI <Boundary> 클래스: 지원정보 조회를 담당함
클래스 멤버변수:
클래스 멤버함수:
	void startInterface(vector<RecruitmentInfo*> gcAppliedList); 일반회원이 지원한 지원정보 목록을 나열해줌
작성날짜: 2023/05/23
작성자: 신유승
*/

class InquireApplicationInfoUI {
private:
	
public:
	
 	void startInterface(vector<RecruitmentInfo*> gcAppliedList);
};

/*
클래스 이름: InquireApplicationInfo <Control>클래스 지원 정보 조회를 담당함.
클래스 멤버변수:
	GeneralClient* gClient; 지원 내역을 조회할 일반 회원
	vector<RecruitmentInfo*> gcAppliedList; 일반회원이 지원한 회원 목록 리스트
클래스 멤버함수:

작성 날짜: 2023/05/23
작성자: 신유승
*/

class InquireApplicationInfo {
private:
	GeneralClient* gClient;
	vector<RecruitmentInfo*> gcAppliedList;
	InquireApplicationInfoUI* inquireApplicationInfoUI;
public:
	InquireApplicationInfo(GeneralClient* gClient);
};

/*
클래스 이름: CompareRecruitmentInfo 기능 : RecruitmentInfo의 pointer를 비교하는 클래스
클래스 멤버 변수: 없음
클래스 멤버 함수: bool operator()(const RecruitmentInfo* a, const RecruitmentInfo* b): 두 RecruitmentInfo를 비교하는 oeprator
작성 날짜: 2023/05/23
작성자: 신유승
*/


class CompareRecruitmentInfo {//RecruitmentInfo pointer를 비교하는 클래스

public:
	bool operator()(const RecruitmentInfo* a, const RecruitmentInfo* b);
};

/*
클래스 이름 : CancelApplicationInfoUI <Boundary 클래스>: 지원 취소를 담당합니다.
클래스 멤버변수: CancelApplicationInfo* cancelApplicationInfo > 바운더리 클래스의 레퍼런스를 저장할 공간입니다.
클래스 멤버함수: CancelApplicationInfoUI(CancelApplicationInfo* cancelApplicationInfo)
				 void startInterface(RecruitmentInfoList* riList)
작성날짜 : 2023/05/22
작성자 : 김민정
*/
class CancelApplicationInfoUI
{
private:
	CancelApplicationInfo* cancelApplicationInfo;
	
public:
	CancelApplicationInfoUI(CancelApplicationInfo* cancelApplicationInfo);
	void startInterface(RecruitmentInfoList* riList);
};

/*
클래스 이름 : CancelApplicationInfo <Control 클래스>: 지원 취소를 담당합니다.
클래스 멤버변수: GeneralClient* gClient > 현재 취소하려는 일반회원입니다.
				 RecruitmentInfoList* riList > 현재 등록되어있는 채용공고목록입니다.
				 vector<RecruitmentInfo*> gcRiList > 일반회원이 지원한 채용공고 목록입니다.
				 RecruitmentInfo* toCancelRecruitmentInfo > 본인이 지원한 취소를 원하는 채용 공고입니다.
				 CancelApplicationInfoUI* cancelApplicationInfoUI > 컨트롤 클래스의 레퍼런스를 저장할 공간입니다.
				 string bn > 일반회원이 취소하려는 채용 공고의 사업자번호입니다.
클래스 멤버함수: CancelApplicationInfo(GeneralClient* gClient, RecruitmentInfoList* riList)
				 void cancelApplication(string bn)
작성날짜 : 2023/05/22
작성자 : 김민정
*/
class CancelApplicationInfo
{
private:
	GeneralClient* gClient;//현재 취소하려는 일반회원
	RecruitmentInfoList* riList;//현재 등록되어있는 채용공고목록]
	vector<RecruitmentInfo*> gcRiList;//일반회원이 지원한 채용공고 목록
	RecruitmentInfo* toCancelRecruitmentInfo;//본인이 지원한, 취소하려는, 채용 공고
	CancelApplicationInfoUI* cancelApplicationInfoUI;
	string bn;//일반회원이 취소하려는 bn


public:
	CancelApplicationInfo(GeneralClient* gClient, RecruitmentInfoList* riList);
	void cancelApplication(string bn);
};

/*
클래스 이름 : ViewStatisticsOfRegisteredRecruitmentInfo <Control 클래스>: 회사회원 통계를 담당합니다.
클래스 멤버변수: 
	CompanyClient*cClient -> 회사 회원들의 정보를 지닌 CompanyClient 객체
	ViewstatisticsOfRegisteredRecruitmentInfo*viewStatisticsOfRegisteredRecruitmentInfo -> 바운더리 클래스의 레퍼런스를 저장할 공간
클래스 멤버함수:
	printStatisticsInfo(CompanyClient *cClient) -> 모든 채용정보에 대해 업무별 지원자 수를 보여준다.
작성날짜 : 2023/05/22
작성자 : 임채은
*/
class ViewStatisticsOfRegisteredRecruitmentInfo{
private:
	CompanyClient* cClient;
	ViewStatisticsOfRegisteredRecruitmentInfo* viewStatisticsOfRegisteredRecruitmentInfo;
public:
	ViewStatisticsOfRegisteredRecruitmentInfo(CompanyClient *cClient);
	void printStatisticsInfo(CompanyClient *cClient);
};

/*
클래스 이름 : ViewStatisticsOfRegisteredRecruitmentInfo <Boundary 클래스>: 회사회원 통계를 담당합니다.
클래스 멤버변수:
	ViewstatisticsOfRegisteredRecruitmentInfo*viewStatisticsOfRegisteredRecruitmentInfo -> 컨트롤 클래스의 레퍼런스를 저장할 공간
클래스 멤버함수:
작성날짜 : 2023/05/22
작성자 : 임채은
*/
class ViewStatisticsOfRegisteredRecruitmentInfoUI{
private:
	ViewStatisticsOfRegisteredRecruitmentInfo* viewStatisticsOfRegisteredRecruitmentInfo;
public:
};

/*
클래스 이름 : ViewStatisticsOfAppliedInfo <Control 클래스>: 일반회원 통계를 담당합니다.
클래스 멤버변수:
	GeneralClient *gClient -> 일반 회원들의 정보를 지닌 GeneralClient 객체
	ViewStatisticsOfAppliedInfo *viewStatisticsOfAppliedInfo -> 바운더리 클래스의 레퍼런스를 저장할 공간
클래스 멤버함수:
	printStatisticsInfo(GeneralClient *gClient) -> 모든 지원정보에 대해 업무별 지원 횟수를 보여준다.
작성날짜 : 2023/05/22
작성자 : 임채은
*/
class ViewStatisticsOfAppliedInfo{
private:
	GeneralClient *gClient;
	ViewStatisticsOfAppliedInfo *viewStatisticsOfAppliedInfo;
public:
	ViewStatisticsOfAppliedInfo(GeneralClient *gClient);
	void printStatisticsInfo(GeneralClient *gClient); 
};

/*
클래스 이름 : ViewStatisticsOfAppliedInfo <Boundary 클래스>: 일반회원 통계를 담당합니다.
클래스 멤버변수: 
	ViewStatisticsOfAppliedInfo* viewStatisticsOfAppliedInfo -> 컨트롤 클래스의 레퍼런스를 저장할 공간
클래스 멤버함수:
작성날짜 : 2023/05/22
작성자 : 임채은
*/
class ViewStatisticsOfAppliedInfoUI{
private:
	ViewStatisticsOfAppliedInfo* viewStatisticsOfAppliedInfo;
public:
};

#endif // !1



