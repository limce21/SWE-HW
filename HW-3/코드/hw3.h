#ifndef HW3_H
#define HW3_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdlib.h>

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
클래스 멤버변수:
클래스 멤버함수:
작성날짜 : 2023/05/31
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
클래스 멤버변수:
클래스 멤버함수:
작성날짜 : 2023/05/31
작성자 : 박시홍
*/
class GeneralClient : public Client
{
private:
	string _rrn; //일반회원의 주민번호
	vector<RecruitmentInfo*> appliedList;//해당 회원이 지원한 리스트

public:
	
	GeneralClient(int type, string name, string num, string id, string pw); //일반회원 객체의 생성자
	void addApplication(RecruitmentInfo* ri);
	vector<RecruitmentInfo*> getListAppliedInfo();

};




/*
클래스 이름 : CompanyClient <Entity 클래스> : Client 클래스를 상속함 -> 사업자 번호 필드만 따로 가짐
클래스 멤버변수:
클래스 멤버함수:
작성날짜 : 2023/05/31
작성자 : 박시홍
*/
class CompanyClient : public Client
{
private:
	string _bn; //회사회원의 사업자 번호
	vector<RecruitmentInfo*> registeredList;
public:
	CompanyClient(int type, string name, string num, string id, string pw); //회사회원 객체의 생성자
	RecruitmentInfo* addNewRecruitInfo(string _task, int numOfApplicant, string _finishDate); // 채용 정보 생성하기
	string getbn(); // 사업자정보 반환하기
	vector<RecruitmentInfo*> getListRegisteredInfo();


};




/*
클래스 이름 : ClientList <Collection 클래스> : 모든 Client들에 대한 포인터들을 저장함
클래스 멤버변수:
클래스 멤버함수:
작성날짜 : 2023/05/31
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

	//int count(); 


};




/*
클래스 이름 : GeneralClientList <Collection 클래스> : 모든 GeneralClient들에 대한 포인터들을 저장함
			-> ex) 일반회원의 경우, ClientList에도 포함되어있고, GeneralClientList에도 포함되어있다
클래스 멤버변수:
클래스 멤버함수:
작성날짜 : 2023/05/31
작성자 : 박시홍
*/
class GeneralClientList
{
private:
	vector<GeneralClient*> gCList; // GeneralClient 포인터 배열
public:

	void addGeneralClient(GeneralClient* C); //GeneralClientList의 attribute인 gCList에 새로 회원가입한 일반 회원 정보를 넣어줌
	void destroy(string id); //해당 id값을 지닌 GeneralClient 객체를 gCList에서 지움
	GeneralClient* findById(string id);//해당리스트에서 id를 기준으로 회원찾는것
};


/*
클래스 이름 : CompanyClientList <Collection 클래스> : 모든 CompanyClient들에 대한 포인터들을 저장함
			-> ex) 회사회원의 경우, ClientList에도 포함되어있고, CompanyClientList에도 포함되어있다
클래스 멤버변수:
클래스 멤버함수:
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
	CompanyClient* findById(string id);
};


/*
클래스 이름 : RecruitmentInfo 클래스
클래스 멤버변수:
클래스 멤버함수:
작성날짜 : 2023/05/22
작성자 : 김민정
*/
class RecruitmentInfo {
private:
	string companyName;
	string bn;
	string task;
	int numOfApplicant;//지원자수
	int expectedApplicantNum;//모집인원
	string finishDate;

public:
	RecruitmentInfo(string companyName, string bn, string task, int expectedApplicantNum, string finishDate);
	//RecruitmentInfo* getRecruitmentInfoDetails(RecruitmentInfo* ri);필요없는듯?
	
	string getName()const;//compare작성할때 읽기전용으로만 읽을 수 있음
	string getBn();
	string getTask();
	int getApplicantNum();
	int getExpectedApplicantNum();
	string getFinishDate();
	void addApplicantToRecruitment();
	
};

class RecruitmentInfoList {
private:
	vector<RecruitmentInfo*> rCList; // GeneralClient 포인터 배열

public:
	
	
	void setRecruitmentInfo(vector<RecruitmentInfo*> riList);
	//RecruitmentInfoList(vector<RecruitmentInfo*>riList);
	vector<RecruitmentInfo*> getRIList();
	void addNewRecruitmentInfoList(RecruitmentInfo* ri);
	RecruitmentInfo* findByName(string companyName);
	RecruitmentInfo* findByNum(string bn);
	bool compare(const RecruitmentInfo* a, const RecruitmentInfo* b);//자신의 리스트를 오름차순 정렬로 정렬하는 함수

};

/*
클래스 이름 : SignInUI <Boundary 클래스> : 회원 가입과 관련된 interface를 담당한다.
클래스 멤버변수:
클래스 멤버함수:
작성날짜 : 2023/05/31
작성자 : 박시홍
*/
class SignInUI {
private:

	SignIn* pSignIn; //회원 가입과 관련된 컨트롤 클래스의 레퍼런스를 attribute로 가진다. -> 이를 통해 control 클래스의 public 멤버함수 호출 가능
	int type; //회원이 입력한 회원 type값
	string name; //회원이 입력한 이름/회사이름
	string num;  //회원이 입력한 주민번호/사업자번호
	string id; //회원이 입력한 id
	string pw; //회원이 입력한 pw



public:
	SignInUI(SignIn* refSignIn); //바운더리 클래스의 생성자-> 컨트롤 클래스의 레퍼런스를 attribute로 가짐
	void startInterface(); //회원 유형과 정보를 입력하라는 화면을 보여줌
	void fillInfo(); //각 회원에게 필요 정보를 입력받고, 컨트롤 클래스에게 회원가입하라는 addNewClient함수 호출함


};

/*
클래스 이름 : SignIn <Control 클래스> : 회원 가입과 관련된 control을 담당한다.
클래스 멤버변수:
클래스 멤버함수:
작성날짜 : 2023/05/31
작성자 : 박시홍
*/
class SignIn {
	SignInUI* pSignInUI; //바운더리 클래스의 레퍼런스를 저장할 공간
	ClientList* cList; //회원들의 정보를 지닌 collection class의 instance
	CompanyClientList* ccList; //회사 회원들의 정보를 지닌 collection class의 instance
	GeneralClientList* gcList; //일반 회원들의 정보를 지닌 collection class의 instance

public:
	SignIn(ClientList* list, GeneralClientList* gcList, CompanyClientList* ccList); //컨트롤 클래스의 생성자-> 바운더리 클래스의 레퍼런스를 attribute로 가짐
	void addNewClient(int type, string name, string num, string id, string pw); //바운더리 클래스에서 매개변수로 받은 회원의 정보를 이용해 회원 리스트에 저장하고, 회원의 타입에 따라 일반회원/회사회원의 리스트에 저장한다. 
};


/*

클래스 이름 : LogIn <Control 클래스> : 로그인과 관련된 control을 담당한다.
클래스 멤버변수:
클래스 멤버함수:
작성날짜 : 2023/05/31
작성자 : 박시홍
*/
class LogIn {
private:

	LogInUI* pLogInUI; //바운더리 클래스의 레퍼런스를 저장할 공간
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
클래스 멤버변수:
클래스 멤버함수:
작성날짜 : 2023/05/31
작성자 : 박시홍
*/
class LogInUI {
private:

	LogIn* pLogIn; //컨트롤 클래스의 레퍼런스를 저장할 공간
	string id; //회원이 입력한 id
	string pw; //회원이 입력한 pw



public:
	LogInUI(LogIn* refLogIn); //바운더리 클래스의 생성자-> 컨트롤 클래스의 레퍼런스를 attribute로 가짐
	void startInterface();  //회원 id와 pw를 입력하라는 화면을 보여줌
	void fillIDPW(); //각 회원에게 필요 정보를 입력받고, 컨트롤 클래스에게 로그인 시도하라는 tryLogIn 함수 호출함


};


/*
클래스 이름 : LogOut <Control 클래스> : 로그아웃과 관련된 control을 담당한다.
클래스 멤버변수:
클래스 멤버함수:
작성날짜 : 2023/05/31
작성자 : 박시홍
*/
class LogOut {
private:

	LogOutUI* pLogOutUI; //바운더리 클래스의 레퍼런스를 저장할 공간
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
클래스 멤버변수:
클래스 멤버함수:
작성날짜 : 2023/05/31
작성자 : 박시홍
*/
class LogOutUI {
private:

	LogOut* pLogOut; //컨트롤 클래스의 레퍼런스를 저장할 공간


public:
	LogOutUI(LogOut* refSignOut); //바운더리 클래스의 생성자-> 컨트롤 클래스의 레퍼런스를 attribute로 가짐
	void startInterface(string id, bool flag); //로그아웃되었다는 메세지를 화면에 보여줌


};


/*
클래스 이름 : SignOut <Control 클래스> : 회원탈퇴와 관련된 control을 담당한다.
클래스 멤버변수:
클래스 멤버함수:
작성날짜 : 2023/05/31
작성자 : 박시홍
*/
class SignOut {
private:

	SignOutUI* pSignOutUI; //바운더리 클래스의 레퍼런스를 저장할 공간
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
클래스 멤버변수:
클래스 멤버함수:
작성날짜 : 2023/05/31
작성자 : 박시홍
*/
class SignOutUI {
private:

	SignOut* pSignOut;




public:
	SignOutUI(SignOut* refSignOut);  //바운더리 클래스의 생성자-> 컨트롤 클래스의 레퍼런스를 attribute로 가짐
	void startInterface(string id, bool flag); //회원탈퇴되었다는 메세지를 화면에 보여줌


};


/*
클래스 이름 : RegisterRecruitmentInfo <Control 클래스>: 채용 등록을 담당합니다.
클래스 멤버변수:
클래스 멤버함수:
작성날짜 : 2023/05/22
작성자 : 김민정
*/
class RegisterRecruitmentInfo
{
private:
	RegisterRecruitmentInfoUI* registerRecruitmentInfoUI; // 바운더리 클래스의 레퍼런스를 저장합니다.
	CompanyClient* companyClient; // 회사 회원
	RecruitmentInfo* registeredList;
	RecruitmentInfoList* recruitmentInfoList;

public:
	RegisterRecruitmentInfo(CompanyClient* companyClient, RecruitmentInfoList* recruitmentInfoList);
	void addNewRecruitmentInfo(string task, int numOfApplicant, string finishDate); // recruitment info에 정보를 추가합니다
	RecruitmentInfoList* getRecruitmentInfoList();
	RecruitmentInfo* getRegisteredList();
};

//this->re.push_back()

/*
클래스 이름 : RegisterRecruitmentInfoUI <Boundary 클래스>: 채용 등록을 담당합니다.
클래스 멤버변수:
클래스 멤버함수:
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
	void startInterface(); // 인터페이스 시작
	void result(string task, int numOfApplicant, string finishDate); // 사용자의 화면에 결과를 표시합니다
	void registerInput(); //파일에서 입력값을 받아들임
};

/*
클래스 이름 : InquireRecruitmentInfo <Control 클래스>: 채용 조회를 담당합니다.
클래스 멤버변수:
클래스 멤버함수:
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
클래스 이름 : InquireRecruitmentInfo <Boundary 클래스>: 채용 조회를 담당합니다.
클래스 멤버변수:
클래스 멤버함수:
작성날짜 : 2023/05/22
작성자 : 김민정
*/
class InquireRecruitmentInfoUI
{
private:
	InquireRecruitmentInfo* inquireRecruitmentInfo;
public:
	InquireRecruitmentInfoUI(InquireRecruitmentInfo* inquireRecruitmentInfo);
	void startInterface(vector<RecruitmentInfo*> riList); // 사용자인 회사 회원의 RecruitmentInfo를 보여줍니다.
};


//-------------------------------
// 채용정보검색

class SearchRecruitmentInfoUI {
private:
	SearchRecruitmentInfo* searchRecruitmentInfo;
public:
	SearchRecruitmentInfoUI(SearchRecruitmentInfo* searchRecruitmentInfo);
	void startInterface();


};



class SearchRecruitmentInfo {
private:
	RecruitmentInfoList* riList;
	string companyName;
	RecruitmentInfo* result;
public:
	SearchRecruitmentInfo(RecruitmentInfoList* riList);
	RecruitmentInfo* getResult();
	void setCompanyName(string companyName);
	void searchRecruitmentInfoListByComName(string name);
};
//채용정보검색

//채용 지원
/*
*/
class ApplyForRecruitmentInfoUI {
private:
	string bn;
	ApplyForRecruitmentInfo* applyForRecruitmentInfo;
public:
	ApplyForRecruitmentInfoUI(ApplyForRecruitmentInfo* applyForRecruitmentInfo);
	void startInterface(RecruitmentInfoList* riList);
	void applyForRecruitmentInfoByNum(string bn);
};


class ApplyForRecruitmentInfo {
private:
	GeneralClient* gClient; //지원하려고하는 일반 회원
	RecruitmentInfoList* riList; //현재 등록된 채용정보
	RecruitmentInfo* appliedRecruitmentInfo;//로그인한 일반회원이 지원한 채용목록	


public:
	ApplyForRecruitmentInfo(GeneralClient* gClient, RecruitmentInfoList* riList);
	void addApplicant(string bn);
};

// 채용 지원

// 지원 정보 조회

class InquireApplicationInfoUI {
private:

public:
	//	InquireApplicationInfoUI();
	void startInterface(vector<RecruitmentInfo*> gcAppliedList);
};



class InquireApplicationInfo {
private:
	GeneralClient* gClient;
	vector<RecruitmentInfo*> gcAppliedList;
public:
	
	InquireApplicationInfo(GeneralClient* gClient);

};


class CompareRecruitmentInfo {//RecruitmentInfo pointer를 비교하는 클래스

public:
	bool operator()(const RecruitmentInfo* a, const RecruitmentInfo* b);
};


#endif // !1



