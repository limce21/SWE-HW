#include "hw3.h"


/*
   함수이름: System::doTask
   기능: 파일에서 입력받은 번호 두개의 값에 따라 별도의 기능을 수행하도록 한다.
   매개변수: 없음
   반환값: 없음

   작성날짜: 2023/05/21
   작성자: 박시홍
*/
void System::doTask()
{
    int menu_level_1 = 0, menu_level_2 = 0; //input.txt파일에서 읽어들일 두개의 변수 초기화
    int is_program_exit = 0; //프로그램 종료 코드 -> 0: 계속 프로그램 실행 / 1: 프로그램 종료
    ClientList* clientList = new ClientList(); //Client객체들을 관리할 ClientList객체 생성 -> 이 객체의 reference들을 각 기능을 수행하라는 controller 생성자의 매개변수로 줄 것임
    GeneralClientList* gcList = new GeneralClientList(); // GeneralClient객체들을 관리할 GeneralClientList객체 생성->이 객체의 reference들을 각 기능을 수행하라는 controller 생성자의 매개변수로 줄 것임
    CompanyClientList* ccList = new CompanyClientList(); // CompanyClient객체들을 관리할 CompanyClientList객체 생성->이 객체의 reference들을 각 기능을 수행하라는 controller 생성자의 매개변수로 줄 것임

    RecruitmentInfoList* rcList = new RecruitmentInfoList(); // 모든 채용정보가 담긴 리스트
    Client* curLogInClient = 0; //현재 로그인되어 있는 Client 객체를 저장하기 위함 -> 이 값이 존재하는 경우, 로그인된 client가 이 변수에 저장되어있고, 이 객체의 정보가 필요한 control 클래스의 생성자에 매개변수로 넣어준다.
    LogIn* logIn = 0; //위의 curLogInClient 객체는 logIn 컨드롤 클래스의 getLogInClient() 호출을 통해 얻어낼 것이므로 logIn 컨트롤러에 접근하기 편하도록 밑의 switch문 밖에 미리 선언해놓는다.

    fin.open(INPUT_FILE_NAME); //input.txt 파일 열기
    fout.open(OUTPUT_FILE_NAME); //output.txt 파일 열기


    while (!is_program_exit)
    {
        // 입력파일에서 메뉴 숫자 2개를 읽기
        fin >> menu_level_1;
        fin >> menu_level_2;

        // 메뉴 구분 및 해당 연산 수행
        switch (menu_level_1)
        {
        case 1:
        {
            switch ((menu_level_2))
            {
            case 1:
            {
                fout << "1.1. 회원가입" << endl;
                SignIn* signIn = new SignIn(clientList, gcList, ccList); //회원가입 컨트롤 클래스 생성

                break;
            }

            case 2:
            {
                fout << "1.2. 회원탈퇴" << endl;

                if (logIn != nullptr) //LogIn컨트롤 클래스가 생성되기도 전에 회원탈퇴를 시도하는 비정상적인 접근을 막기 위함 -> LogIn Control클래스가 생성되었다면
                {
                    curLogInClient = logIn->getLogInClient(); //로그인된 계정을 조회한다
                    if (curLogInClient != nullptr) //로그인된 계정이 null이 아닐 경우에만 회원탈퇴 시도
                    {
                        SignOut* signOut = new SignOut(clientList, gcList, ccList, curLogInClient); //회원 탈퇴 컨트롤 클래스 생성

                    }
                }
                else //LogIn 컨트롤 클래스가한번도 생성된 적이 없는 경우
                {
                    cout << "회원탈퇴 할 수 없습니다" << endl;
                }
                //curLogInClient = logIn->getLogInClient(); //로그인된 계정을 알아온다                
                //SignOut* signOut = new SignOut(clientList, gcList, ccList, curLogInClient);
                break;
            }

            }
            break;
        }

        case 2:
        {
            switch (menu_level_2)
            {
            case 1:
            {
                fout << "2.1. 로그인" << endl;
                //LogIn* logIn = new LogIN(clientList, gcList, ccList);
                logIn = new LogIn(clientList, gcList, ccList); //switch문 밖에 미리 만들어놓은 logIn변수에 LogIn 컨트롤 클래스 객체를 담는다.
                //cout << clientList->count();
                break;


            }
            case 2:
            {
                fout << "2.2. 로그아웃" << endl;
                if (logIn != nullptr) //LogIn컨트롤 클래스가 생성되기도 전에 회원탈퇴를 시도하는 비정상적인 접근을 막기 위함 -> LogIn Control클래스가 생성되었다면
                {
                    curLogInClient = logIn->getLogInClient(); //로그인된 계정을 조회한다
                    if (curLogInClient != nullptr) //로그인된 계정이 있는 경우에만 로그아웃 시도
                    {
                        LogOut* logOut = new LogOut(clientList, gcList, ccList, curLogInClient); //로그아웃 컨트롤 클래스 생성 

                    }
                }

                else //LogIn 컨트롤 클래스가한번도 생성된 적이 없는 경우 
                {
                    cout << "로그아웃 할 수 없습니다" << endl;
                }
                //curLogInClient = logIn->getLogInClient();
                //LogOut* logOut = new LogOut(clientList, gcList, ccList,curLogInClient);

                break;
            }
            }
            break;
        }

        case 3: {
            switch (menu_level_2)
            {
            case 1: // "3.1. 채용 정보 등록“ 메뉴 부분
            {
                fout << "3.1. 채용 정보 등록" << endl;
                if (logIn != nullptr) //한명이라도 로그인이 되어있는 경우에만 실행
                {

                    curLogInClient = logIn->getLogInClient();
                    string tmpid = curLogInClient->getId();
                    CompanyClient* tmpCompanyClient = ccList->findById(tmpid);
                    int tmp = curLogInClient->getType();
                    // int tmp = curLogInClient.getType();
                    if (tmp == 2) {
                        cout << "일반 회원은 채용정보 등록이 불가능합니다.\n";
                    }
                    else {
                        //CompanyClient *companyClient = findByID(로그인된 객체의 id)

                        RegisterRecruitmentInfo* registerRecruitmentInfo = new RegisterRecruitmentInfo(tmpCompanyClient, rcList);
                        //Control 내부에서 방금 등록한 채용정보를 현재 세션으로 반영하는 작업이 필요함


                    }
                }
                else //로그인되어있는 사람이 없는 경우 
                {
                    cout << "채용 정보를 등록할 수 없습니다." << endl;
                }
                break;
            }
            case 2: // "3.2. 채용 정보 조회“ 메뉴 부분
            {
                fout << "3.2. 채용 정보 조회" << endl;
                if (logIn != nullptr) //한명이라도 로그인이 되어있는 경우에만 실행
                {
                    curLogInClient = logIn->getLogInClient();
                    string tmpid = curLogInClient->getId();
                    CompanyClient* tmpCompanyClient = ccList->findById(tmpid);
                    InquireRecruitmentInfo* inquireRecruitmentInfo = new InquireRecruitmentInfo(tmpCompanyClient);
                }
                else //로그인되어있는 사람이 없는 경우 
                {
                    cout << "채용 정보를 조회할 수 없습니다." << endl;
                }
                break;
            }
            }
            break;

        }
        case 4: {
            switch (menu_level_2) {
            case 1: {//채용 정보 검색
                fout << "4.1. 채용정보 검색\n";
                if (logIn != nullptr) {
                    SearchRecruitmentInfo* searchRecruitmentInfo = new SearchRecruitmentInfo(rcList);
                }
                else {
                    cout << "일반회원으로 로그인하고 오십시오.\n";
                }
                break;
            }
            case 2: {//채용 지원
                fout << "4.2. 채용 지원\\n";
                if (logIn != nullptr) {
                    curLogInClient = logIn->getLogInClient();
                    string tmpid = curLogInClient->getId();
                    GeneralClient* tmpGeneralClient = gcList->findById(tmpid);
                    ApplyForRecruitmentInfo* applyForRecruitmentInfo = new ApplyForRecruitmentInfo(tmpGeneralClient,rcList);
                }
                else {
                    cout << "일반회원으로 로그인하고 오십시오.\n";
                }
                break;
            }
            case 3: {//지원 정보 조회
                fout << "4.3. 지원 정보 조회\n";
                if (logIn != nullptr) {
                    curLogInClient = logIn->getLogInClient();
                    string tmpid = curLogInClient->getId();
                    GeneralClient* tmpGeneralClient = gcList->findById(tmpid);
                    InquireApplicationInfo* inquireApplicationInfo = new InquireApplicationInfo(tmpGeneralClient);
                }
                else {
                    cout << "일반 회원으로 로그인하고 재시도 하십시오.\n";
                }
                break;
            }
            case 4: {// 지원 취소
                fout << "4.4. 지원 취소\n";
                if (logIn != nullptr) { //
                    curLogInClient = logIn->getLogInClient(); //현재 로그인된 회원을 알아온다
                    string tmpid = curLogInClient->getId();
                    GeneralClient* tmpGeneralClient = gcList->findById(tmpid); 
                    CancelApplicationInfo* cancelApplicationInfo = new CancelApplicationInfo(tmpGeneralClient, rcList);
                }
                else {
                    cout << "지원 취소가 불가능합니다.\n";
                }
                break;

            }
            }
            break;
        }

        case 6: {
            switch (menu_level_2)
            {
            case 1: // "6.1. 종료“ 메뉴 부분
            {
                fout << "6.1.종료" << endl << endl; 
                is_program_exit = 1;  //종료 코드를 1로 변경
                break;
            }
            }
            break;
        }
        }
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
/*
   함수이름: 앤티티 클래스 Client의 생성자
   기능: 회원을 생성하기 위한 클래스의 생성자로서 기능함
   매개변수: type: 회원 유형 / name: 회원 이름 /id: 회원 id / pw: 회원 비밀번호
   반환값: 없음

   작성날짜: 2023/05/21
   작성자: 박시홍
*/
Client::Client(int type, string name, string id, string pw)
{
    this->type = type;
    this->name = name;
    this->id = id;
    this->pw = pw;
    // this->_num = num;
    this->isLogIn = false;
}


/*
   함수이름: Client::getId
   기능: 해당 회원의 id를 반환한다.
   매개변수: -
   반환값: id

   작성날짜: 2023/05/21
   작성자: 박시홍
*/
string Client::getId()
{
    return this->id;
}


/*
   함수이름: Client::getPw
   기능: 해당 회원의 password를 반환한다.
   매개변수: -
   반환값: pw

   작성날짜: 2023/05/21
   작성자: 박시홍
*/
string Client::getPw()
{
    return this->pw;
}


/*
   함수이름: Client::getTyoe
   기능: 해당 회원의 회원 타입을 반환한다.
   매개변수: -
   반환값: type 1:회사회원 2: 일반회원

   작성날짜: 2023/05/21
   작성자: 박시홍
*/
int Client::getType()
{
    return this->type;
}


/*
   함수이름: Client::getLogInStatus
   기능: 해당 회원의 로그인 상태를 반환한다.
   매개변수: -
   반환값: isLogIn -> true: 로그인 상태 / false: 로그아웃 상태

   작성날짜: 2023/05/21
   작성자: 박시홍
*/
bool Client::getLogInStatus()
{
    return this->isLogIn;
}



// 채용 정보 등록 시 getName
string Client::getName()
{
    return this->name;
}



/*
   함수이름: Client::changeLogInStatus
   기능: 해당 회원의 로그인 상태를 바꿔준다. true->false / false->true
   매개변수: -
   반환값: 없음

   작성날짜: 2023/05/21
   작성자: 박시홍
*/
void Client::changeLogInStatus()
{
    if (this->isLogIn == false)
    {
        this->isLogIn = true;
    }

    else
    {
        this->isLogIn = false;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
   함수이름: 엔티티 클래스 CompanyClient의 생성자
   기능:  회사회원을 생성하기 위한 클래스의 생성자로서 기능함 -> type, name, id, pw는 부모클래스인 Client의 생성자를 통해 생성한다.
   매개변수:
            type: 회원 유형 / name: 회원 이름 /id: 회원 id / pw: 회원 비밀번호 / num: 사업자 번호
   반환값: 없음

   작성날짜: 2023/05/21
   작성자: 박시홍
*/
CompanyClient::CompanyClient(int type, string name, string num, string id, string pw) :Client(type, name, id, pw)
{
    this->bn = num;
}




string CompanyClient::getbn()
{
    return this->bn;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
   함수이름: 엔티티 클래스 GeneralClient의 생성자
   기능:  일반회원을 생성하기 위한 클래스의 생성자로서 기능함 -> type, name, id, pw는 부모클래스인 Client의 생성자를 통해 생성한다.
   매개변수:
            type: 회원 유형 / name: 회원 이름 /id: 회원 id / pw: 회원 비밀번호 / num: 주민ㅂㄴ호
   반환값: 없음

   작성날짜: 2023/05/21
   작성자: 박시홍
*/
GeneralClient::GeneralClient(int type, string name, string num, string id, string pw) :Client(type, name, id, pw)
{
    this->rrn = num;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
   함수이름: ClientList::addClient
   기능: 매개변수로 들어온 회원을 회원 리스트에 추가한다.
   매개변수: Client* -> 추가할 회원 객체
   반환값: 없음

   작성날짜: 2023/05/21
   작성자: 박시홍
*/
void ClientList::addClient(Client* c)
{
    this->cList.push_back(c);
}



/*
   함수이름: ClientList::size
   기능: 회원 리스트의 크기를 반환한다.
   매개변수: 없읍
   반환값: size : 현재 회원 리스트의 크기

   작성날짜: 2023/05/21
   작성자: 박시홍
*/
int ClientList::size()
{
    return this->cList.size();
}



/*
   함수이름: ClientList::getClientList
   기능: 회원 리스트 전체를 반환한다
   매개변수: 없읍
   반환값: vector<Client* > c1
   작성날짜: 2023/05/21
   작성자: 박시홍
*/
vector<Client*> ClientList::getClientList()
{
    vector<Client*> cl;
    for (int i = 0; i < this->size(); i++)
    {
        cl.push_back(this->cList[i]);
    }

    return cl;
}

/*
int ClientList::count()
{
    int c = 0;
    for (int i = 0; i < this->size(); i++)
    {
        if (this->cList[i]->getLogInStatus() == true)
        {
            c++;
        }
    }
    return c;
}
*/


/*
   함수이름: ClientList::destroy
   기능: 입력받은 해당 인덱스의 회원 정보를 삭제한다
   매개변수: idx -> 삭제할 회원의 인덱스값
   반환값: 없음

   작성날짜: 2023/05/21
   작성자: 박시홍
*/
void ClientList::destroy(int idx)
{
    this->cList.erase(cList.begin() + idx); //해당 인덱스의 회원 정보 삭제
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
   함수이름: CompanyClientList::addCompanyClient
   기능: 전달받은 해당 회사 회원 정보를 회사회원 리스트에 삽입한다
   매개변수: 없음
   반환값: 없음

   작성날짜: 2023/05/21
   작성자: 박시홍
*/
void CompanyClientList::addCompanyClient(CompanyClient* c)
{
    this->cCList.push_back(c);
}



/*
   함수이름: CompanyClientList::destroy
   기능: 입력받은 해당 id값과 일치하는 회사 회원 정보를 삭제한다
   매개변수: id -> 삭제할 회원의 id값
   반환값: 없음

   작성날짜: 2023/05/21
   작성자: 박시홍
*/
void CompanyClientList::destroy(string id)
{
    for (int i = 0; i < this->cCList.size(); i++)
    {
        if (cCList[i]->getId() == id)
        {
            this->cCList.erase(cCList.begin() + i);
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
   함수이름: GeneralClientList::addGeneralClient
   기능: 전달받은 해당 일반 회원 정보를 일반회원리스트에 삽입한다
   매개변수: 없음
   반환값: 없음

   작성날짜: 2023/05/21
   작성자: 박시홍
*/
void GeneralClientList::addGeneralClient(GeneralClient* c)
{
    this->gCList.push_back(c);
}


/*
함수이름: GeneralClientList::destroy
기능 : 입력받은 해당 id값과 일치하는 일반 회원 정보를 삭제한다
매개변수 : id->삭제할 회원의 id값
반환값 : 없음

작성날짜 : 2023 / 05 / 31
작성자 : 박시홍
*/
void GeneralClientList::destroy(string id)
{
    for (int i = 0; i < this->gCList.size(); i++)
    {
        if (gCList[i]->getId() == id)
        {
            this->gCList.erase(gCList.begin() + i);
        }
    }
}

string RecruitmentInfo::getBn() {
    return this->bn;
}

RecruitmentInfo* RecruitmentInfoList::findByName(string companyName) {
    int size = rCList.size();
    for (int i = 0; i < size; i++) {
        if (companyName == rCList[i]->getName()) {
            return rCList[i];
        }
    }
}

RecruitmentInfo* RecruitmentInfoList::findByNum(string bn) {
    int size = rCList.size();
    for (int i = 0; i < size; i++) {
        if (bn == rCList[i]->getBn()) {
            return rCList[i];
        }
    }
}

string RecruitmentInfo::getName()const {
    return this->companyName;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
/*
   함수이름: 컨트롤 클래스 SignIn의 생성자
   기능: 회원가입 관련 기능을 수행하기 위한 컨트롤 클래스의 생성자로서 기능함
   매개변수:
            ClientList* list -> 회원들의 정보를 지닌 collection class의 instance
            GeneralClientList*gcList -> 일반 회원들의 정보를 지닌 collection class의 instance
            CompanyClientList*ccList -> 회사 회원들의 정보를 지닌 collection class의 instance
   반환값: 없음

   작성날짜: 2023/05/31
   작성자: 박시홍
*/
SignIn::SignIn(ClientList* list, GeneralClientList* gcList, CompanyClientList* ccList)
{
    SignInUI* signInUI = new SignInUI(this); //바운더리 클래스와 레퍼런스 교환을 위해 바운더리 클래스의 생성자 호출
    this->cList = list; //컨트롤 클래스의 멤버 변수로 회원들의 배열 저장
    this->gcList = gcList; //컨트롤 클래스의 멤버 변수로 일반회원들의 배열 저장
    this->ccList = ccList; //컨트롤 클래스의 멤버 변수로 일반회원들의 배열 저장
    this->pSignInUI = signInUI; //바운더리 클래스의 레퍼런스 값 저장
    pSignInUI->startInterface(); //컨트롤 클래스가 생긴 동시에 startInterface 호출을 바운더리 클래스에게 명령
}

/*
   함수이름: 바운더리 클래스 SignInUI의 생성자
   기능: 회원가입 관련 기능을 수행하기 위한 바운더리 클래스의 생성자로서 기능함
   매개변수:
            SignIn* refSignIn -> 회원 가입과 관련된 컨트롤 클래스의 레퍼런스를 attribute로 가짐

   반환값: 없음

   작성날짜: 2023/05/31
   작성자: 박시홍
*/
SignInUI::SignInUI(SignIn* refSignIn)
{
    this->pSignIn = refSignIn;
    this->id = "";
    this->name = "";
    this->num = "";
    this->pw = "";
    this->type = 0;
}


/*
   함수이름: SignInUI::startInterface
   기능: 회원 유형과 정보를 입력하라는 화면을 보여주고, 필요 정보를 입력받아 컨트롤 클래스에게 입력받은 정보를 보내 회원 등록을 요청한다.
   매개변수: 없음
   반환값: 없음

   작성날짜: 2023/05/31
   작성자: 박시홍
*/
void SignInUI::startInterface()
{
    cout << "회원 유형과 정보를 입력하세요" << endl;
    this->fillInfo();



}


/*
   함수이름: SignInUI::fillInfo
   기능: 회원 가입을 위한 필요 정보를 입력받는 기능을 한다
   매개변수: 없음
   반환값: 없음

   작성날짜: 2023/05/31
   작성자: 박시홍
*/
void SignInUI::fillInfo()
{
    fin >> this->type >> this->name >> this->num >> this->id >> this->pw;
    this->pSignIn->addNewClient(this->type, this->name, this->num, this->id, this->pw);
}



/*
   함수이름: SignIn::addNewClient
   기능: 회원 가입을 위해 입력받은 정보를 이용해 회원 리스트에 저장하고, 회원의 타입에 따라 일반회원/회사회원의 리스트에 저장한다.
   매개변수: clientType -> 입력받은 회원 유형
            name -> 입력받은 회원의 회사이름/이름
            num -> //회원이 입력한 주민번호/사업자번호
             id -> 회원이 입력한 id
             pw ->회원이 입력한 pw
   반환값: 없음

   작성날짜: 2023/05/31
   작성자: 박시홍
*/
void SignIn::addNewClient(int clientType, string name, string num, string id, string pw)
{
    if (clientType == 1) //입력받은 정보 중 type값이 회사회원인 경우
    {
        CompanyClient* cClient = new CompanyClient(clientType, name, num, id, pw); //회사회원 객체 생성
        Client* client = new Client(clientType, name, id, pw); //회원 객체 생성
        this->cList->addClient(client); //회원 리스트에 저장
        this->ccList->addCompanyClient(cClient); //회사 회원 리스트에 저장



    }

    else //입력받은 정보 중 type값이 일반회원인 경우
    {
        GeneralClient* gClient = new GeneralClient(clientType, name, num, id, pw); //일반회원 객체 생성
        Client* client = new Client(clientType, name, id, pw); //회원 객체 생성
        this->cList->addClient(client); //회원 리스트에 저장
        this->gcList->addGeneralClient(gClient); //일반회원 리스트에 저장
    }

    fout << '>' << clientType << ' ' << name << ' ' << num << ' ' << id << ' ' << pw << endl << endl; //파일에 성공 메세지 출력
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////



/*
   함수이름: 컨트롤 클래스 LogIn의 생성자
   기능: 로그인 관련 기능을 수행하기 위한 컨트롤 클래스의 생성자로서 기능함
   매개변수:
            ClientList* list -> 회원들의 정보를 지닌 collection class의 instance
            GeneralClientList*gcList -> 일반 회원들의 정보를 지닌 collection class의 instance
            CompanyClientList*ccList -> 회사 회원들의 정보를 지닌 collection class의 instance
   반환값: 없음

   작성날짜: 2023/05/31
   작성자: 박시홍
*/
LogIn::LogIn(ClientList* list, GeneralClientList* gcList, CompanyClientList* ccList)
{
    LogInUI* logInUI = new LogInUI(this); //바운더리 클래스와 레퍼런스 교환을 위해 바운더리 클래스의 생성자 호출
    this->cList = list; //컨트롤 클래스의 멤버 변수로 회원들의 배열 저장
    this->gcList = gcList; //컨트롤 클래스의 멤버 변수로 일반회원들의 배열 저장
    this->ccList = ccList; //컨트롤 클래스의 멤버 변수로 일반회원들의 배열 저장
    this->pLogInUI = logInUI; //바운더리 클래스의 레퍼런스 값 저장
    this->curLogInClient = nullptr;  //처음 LogIn클래스가 생성될 때 로그인된 계정은 nullptr값임
    pLogInUI->startInterface();  //컨트롤 클래스가 생긴 동시에 startInterface 호출을 바운더리 클래스에게 명령
}



/*
   함수이름: LogIn::tryLogIn
   기능: 로그인을 하기 위해 clientList에 저장된 모든 회원의 정보를 가져온 후, id, pw이 모두 일치하고 로그인이 안되어있는 경우에만 로그인 상태로 바꿔준다.
   매개변수:
             id -> 회원이 입력한 id
             pw ->회원이 입력한 pw
   반환값: 없음

   작성날짜: 2023/05/31
   작성자: 박시홍
*/
void LogIn::tryLogIn(string id, string pw)
{

    vector<Client*> temp; //해당 함수에서 사용할 임시 client* 벡터를 생성
    temp = this->cList->getClientList(); //매개변수로 가져온 cList의 전체 회원들 정보를 temp 배열에 저장
    bool isMatched = false; //id pw이 모두 match되는지 확인할 변수 isMatched는 초기에 false로 초기화

    for (int i = 0; i < temp.size(); i++) //temp배열의 크기(저장된 회원의 수)만큼 반복
    {
        if (temp[i]->getId() == id && temp[i]->getPw() == pw) //해당 인덱스의 회원 id,pw이 입력받은 id,pw와 일치한다면
        {
            isMatched = true; //true값으로 변경
            if (temp[i]->getLogInStatus() == false) //그리고 해당 회원의 로그인 상태가 false라면
            {

                temp[i]->changeLogInStatus(); //해당 회원의 로그인 상태값을 true로 바꿔줌
                this->curLogInClient = temp[i]; //로그인이 되었으므로 LogIn 컨트롤 클래스는 현재 로그인된 client의 정보를 갖고있는다
                fout << '>' << temp[i]->getId() << ' ' << temp[i]->getPw() << endl << endl; //로그인이 완료되면 완료되었다는 정보를 파일에 출력함
                break; //로그인을 시켰으므로 for문 탈출
            }

            else //만약 로그인이 이미 되어있는 사람이 또 로그인을 시도하는 경우
            {
                cout << "이미 로그인된 상태입니다" << endl;
            }

            //break;
        }


    }

    if (isMatched == false) //만약 어떠한 계정도 match되지 않았다면 clientList에 없는 게정임
    {
        cout << "없는 계정입니다." << endl;
    }
}

/*
   함수이름: LogInInUI::getLogInClient
   기능: 로그인 객체에 저장되어있는 현재 로그인된 회원(client)의 레퍼런스를 반환한다
   매개변수: 없음
   반환값: curLogInClient

   작성날짜: 2023/05/31
   작성자: 박시홍
*/
Client* LogIn::getLogInClient()
{
    return this->curLogInClient;
}

/*
   함수이름: 바운더리 클래스 LogInUI의 생성자
   기능: 로그인 관련 기능을 수행하기 위한 바운더리 클래스의 생성자로서 기능함
   매개변수:
            LogIn* refLogIn -> 로그인과 관련된 컨트롤 클래스의 레퍼런스를 attribute로 가짐

   반환값: 없음

   작성날짜: 2023/05/31
   작성자: 박시홍
*/
LogInUI::LogInUI(LogIn* refLogIn)
{
    this->pLogIn = refLogIn;
    this->id = "";
    this->pw = "";

}

/*
   함수이름: LogInInUI::startInterface
   기능: 회원 id와 pw를 입력하라는 화면을 보여주고, 필요 정보를 입력받아 컨트롤 클래스에게 입력받은 정보를 보내 로그인을 요청한다.
   매개변수: 없음
   반환값: 없음

   작성날짜: 2023/05/31
   작성자: 박시홍
*/
void LogInUI::startInterface()
{
    cout << "아이디와 패스워드를 입력하세요" << endl;
    this->fillIDPW();
}



/*
   함수이름: LogInUI::fillIDPW
   기능: 로그인을 위한 필요 정보를 입력받는 기능을 한다
   매개변수: 없음
   반환값: 없음

   작성날짜: 2023/05/31
   작성자: 박시홍
*/
void LogInUI::fillIDPW()
{
    fin >> this->id >> this->pw;
    this->pLogIn->tryLogIn(this->id, this->pw);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/*
   함수이름: 컨트롤 클래스 LogOut의 생성자
   기능: 로그아웃 관련 기능을 수행하기 위한 컨트롤 클래스의 생성자로서 기능함
   매개변수:
            ClientList* list -> 회원들의 정보를 지닌 collection class의 instance
            GeneralClientList*gcList -> 일반 회원들의 정보를 지닌 collection class의 instance
            CompanyClientList*ccList -> 회사 회원들의 정보를 지닌 collection class의 instance
            Client* client -> 로그인된 계정의 정보를 지닌 Client 객체
   반환값: 없음

   작성날짜: 2023/05/31
   작성자: 박시홍
*/
LogOut::LogOut(ClientList* list, GeneralClientList* gcList, CompanyClientList* ccList, Client* client)
{
    LogOutUI* logOutUI = new LogOutUI(this); //바운더리 클래스와 레퍼런스 교환을 위해 바운더리 클래스의 생성자 호출
    this->cList = list; //컨트롤 클래스의 멤버 변수로 회원들의 배열 저장
    this->gcList = gcList; //컨트롤 클래스의 멤버 변수로 일반회원들의 배열 저장
    this->ccList = ccList; //컨트롤 클래스의 멤버 변수로 일반회원들의 배열 저장
    this->curLogInClient = client; //로그인된 Client객체를 저장
    this->pLogOutUI = logOutUI;   //바운더리 클래스의 레퍼런스 값 저장
    this->changeLogInStatus(curLogInClient); //현재 로그인된 계정의 정보를 바탕으로 로그아웃 기능 수행 명령

}


/*
   함수이름: 바운더리 클래스 LogOutUI의 생성자
   기능: 로그아웃 관련 기능을 수행하기 위한 바운더리 클래스의 생성자로서 기능함
   매개변수:
            LogOut* refLogOut -> 로그아웃과 관련된 컨트롤 클래스의 레퍼런스를 attribute로 가짐

   반환값: 없음

   작성날짜: 2023/05/31
   작성자: 박시홍
*/
LogOutUI::LogOutUI(LogOut* refLogOut)
{
    this->pLogOut = refLogOut;

}

/*
   함수이름: LogOut::changeLogInStatus
   기능: 로그아웃을 하기 위해 clientList에 저장된 모든 회원의 정보를 가져온 후, 로그인된 Client의 id와 pw이 일치하는 지 확인
        그 후, match된 계정의 login상태가 true라면 로그인 상태를 false로 바꿔준다.
   매개변수:
             Client* client -> 로그인된 계정
   반환값: 없음

   작성날짜: 2023/05/31
   작성자: 박시홍
*/
void LogOut::changeLogInStatus(Client* client)
{
    vector<Client*> temp; //해당 함수에서 사용할 임시 client* 벡터를 생성
    temp = this->cList->getClientList(); //매개변수로 가져온 cList의 전체 회원들 정보를 temp 배열에 저장
    string id; //로그아웃이 성공될 경우, 로그아웃된 계정을 반환하기 위한 변수
    bool isPossible = false; //로그아웃이 가능한지 알려주는 flag변수 -> true일 경우에는 로그아웃 가능, false인 경우 로그아웃 불가능

    for (int i = 0; i < temp.size(); i++) //temp배열의 크기(저장된 회원의 수)만큼 반복
    {
        if (temp[i]->getId() == client->getId() && temp[i]->getPw() == client->getPw()) //해당 인덱스의 회원 id,pw이 로그인 된 회원의 id,pw와 일치한다면
        {
            if (temp[i]->getLogInStatus() == true) //그리고 그 회원의 로그인 상태가 true라면
            {
                temp[i]->changeLogInStatus(); //해당 client의 로그인 상태값을 false로 바꿔준다.
                id = temp[i]->getId(); //인터페이스에 출력될 로그아웃한 회원의 id값을 받아온다.
                isPossible = true; //로그아웃 flag변수를 true로 바꿔준다
            }
        }
    }


    this->pLogOutUI->startInterface(id, isPossible); //바운더리 클래스에 로그아웃 성공값과 로그아웃한 계정의 id값을 매개변수로 보내준다


}

/*
   함수이름: LogOutUI::startInterface
   기능: 로그아웃이 성공된 경우, 로그아웃한 계정의 id값을 파일에 쓴다.
   매개변수: string id ->로그아웃한 회원의 id값
            flag -> 로그아웃 됨: true / 로그아웃 불가능 -> false
   반환값: 없음

   작성날짜: 2023/05/31
   작성자: 박시홍
*/
void LogOutUI::startInterface(string id, bool flag)
{
    if (flag == true) //로그아웃이 된 경우
    {
        fout << '>' << id << endl << endl;
        cout << "로그아웃 되었습니다." << endl;
    }

    else //로그아웃이 불가능한 경우
    {
        cout << "로그아웃할 수 없습니다." << endl;
    }

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
   함수이름: 컨트롤 클래스 SignOut의 생성자
   기능: 회원탈퇴 관련 기능을 수행하기 위한 컨트롤 클래스의 생성자로서 기능함
   매개변수:
            ClientList* list -> 회원들의 정보를 지닌 collection class의 instance
            GeneralClientList*gcList -> 일반 회원들의 정보를 지닌 collection class의 instance
            CompanyClientList*ccList -> 회사 회원들의 정보를 지닌 collection class의 instance
            Client* client -> 로그인된 계정의 정보를 지닌 Client 객체
   반환값: 없음

   작성날짜: 2023/05/31
   작성자: 박시홍
*/
SignOut::SignOut(ClientList* list, GeneralClientList* gcList, CompanyClientList* ccList, Client* client)
{
    SignOutUI* signOutUI = new SignOutUI(this); //바운더리 클래스와 레퍼런스 교환을 위해 바운더리 클래스의 생성자 호출
    this->cList = list; //컨트롤 클래스의 멤버 변수로 회원들의 배열 저장
    this->gcList = gcList; //컨트롤 클래스의 멤버 변수로 일반회원들의 배열 저장
    this->ccList = ccList; //컨트롤 클래스의 멤버 변수로 일반회원들의 배열 저장
    this->curLogInClient = client; //로그인된 Client객체를 저장
    this->pSignOutUI = signOutUI; //바운더리 클래스의 레퍼런스 값 저장
    this->destroy(curLogInClient); //현제 로그인된 계정 정보를 바탕으로 회원탈퇴 기능 수행

}


/*
   함수이름: 바운더리 클래스 SignOutUI의 생성자
   기능: 회원탈퇴 관련 기능을 수행하기 위한 바운더리 클래스의 생성자로서 기능함
   매개변수:
            SignOut* refSignOut -> 로그아웃과 관련된 컨트롤 클래스의 레퍼런스를 attribute로 가짐

   반환값: 없음

   작성날짜: 2023/05/31
   작성자: 박시홍
*/
SignOutUI::SignOutUI(SignOut* refSignOut)
{
    this->pSignOut = refSignOut;

}


/*
   함수이름: SignOut::destroy
   기능: 회원탈퇴들 하기 위해 clientList에 저장된 모든 회원의 정보를 가져온 후, 로그인된 Client의 id와 pw이 일치하는 지 확인
        그 후, match된 계정의 login상태가 true라면 회원계정을 삭제하고, 해당 계정의 일반/회사회원 유형에 따라 별도로 또 삭제를 요청한다.
   매개변수:
             Client* client -> 로그인 된 계정
   반환값: 없음

   작성날짜: 2023/05/31
   작성자: 박시홍
*/
void SignOut::destroy(Client* client)
{
    vector<Client*> temp; //해당 함수에서 사용할 임시 client* 벡터를 생성
    temp = this->cList->getClientList(); //매개변수로 가져온 cList의 전체 회원들 정보를 temp 배열에 저장
    string id; //회원탈퇴가 성공될 경우, 회원탈퇴된 계정의 id를 반환하기 위한 변수
    bool isPossible = false; //회웥랕퇴 가능한지 확인할 flag변수

    for (int i = 0; i < temp.size(); i++) //temp배열의 크기(저장된 회원의 수)만큼 반복
    {
        if (temp[i]->getId() == client->getId() && temp[i]->getPw() == client->getPw()) //해당 인덱스의 회원 id,pw이 로그인 된 회원의 id,pw와 일치한다면
        {
            if (temp[i]->getLogInStatus() == true) //그리고 그 회원이 로그인 되어있다면
            {
                if (temp[i]->getType() == 1) //그 회원의 type이 회사회원일 경우
                {
                    this->ccList->destroy(temp[i]->getId()); //회사회원 배열에서 해당 회원 삭제(id값이 일치하는 인덱스에서 회사회원 삭제)
                }

                else //그 회원의 type이 일반회원일 경우
                {
                    this->gcList->destroy(temp[i]->getId()); //일반회원 배열에서 해당 회원 삭제(id값이 일치하는 인덱스에서 일반회원 삭제)
                }

                this->cList->destroy(i); //회사회원, 일반회원 구분 없이 client배열에서 해당 회원 삭제
                isPossible = true; //회원탈퇴 진행 상태: true로 변경
                id = temp[i]->getId(); //인터페이스에 출력될 로그아웃한 회원의 id값을 받아온다.
            }
        }
    }


    this->pSignOutUI->startInterface(id, isPossible); //바운더리 클래스에 회원탈퇴 성공값과 회원탈퇴한 계정의 id값을 매개변수로 보내준다
}


/*
   함수이름: SignOutUI::startInterface
   기능: 회원탈퇴가 성공된 경우, 회원탈퇴한 계정의 id값을 파일에 쓴다.
   매개변수: string id ->회원탈퇴한 회원의 id값
            flag -> 회원탈퇴 됨: true / 회원탈퇴 불가능 -> false
   반환값: 없음

   작성날짜: 2023/05/31
   작성자: 박시홍
*/
void SignOutUI::startInterface(string id, bool flag)
{
    if (flag == true)
    {
        fout << '>' << id << endl << endl;
        cout << "회원탈퇴 되었습니다." << endl;
    }

    else
    {
        cout << "회원탈퇴를 할 수 없습니다" << endl;
    }


}

/*
 함수이름: RegisterRecruitmentInfo::RegisterRecruitmentInfo
 기능: RegisterRecruitmentInfo control 클래스의 생성자입니다
 작성날짜: 2023/05/22
 작성자: 김민정
*/
RegisterRecruitmentInfo::RegisterRecruitmentInfo(CompanyClient* companyClient, RecruitmentInfoList* recruitmentInfoList)
{
    this->recruitmentInfoList = recruitmentInfoList;
    this->companyClient = companyClient;
    RegisterRecruitmentInfoUI* registerRecruitmentUI = new RegisterRecruitmentInfoUI(this, this->companyClient);
    registerRecruitmentUI->startInterface();
}

/*
 함수이름: RegisterRecruitmentInfoUI::RegisterRecruitmentInfoUI
 기능: RegisterRecruitmentInfo  boundary 클래스의 생성자입니다
 작성날짜: 2023/05/22
 작성자: 김민정
*/
RegisterRecruitmentInfoUI::RegisterRecruitmentInfoUI(RegisterRecruitmentInfo* registerRecruitmentInfo, CompanyClient* companyClient)
{
    this->registerRecruitmentInfo = registerRecruitmentInfo;
    this->companyClient = companyClient;

}

/*
 함수이름: RegisterRecruitmentInfoUI::startInterface
 기능: RegisterRecruitmentInfoUI에서 입력값을 읽어들이고 RecruitmentInfo에 정보를 추가, 결과를 표시하도록 합니다.
 작성날짜: 2023/05/22
 작성자: 김민정
*/
void RegisterRecruitmentInfoUI::startInterface()
{
    cout << "채용 정보 등록을 위한 필드를 입력하세요" << endl;
    //string task;
    //int numOfApplicant;
    //string finishDate;

    //fin >> task >> numOfApplicant >> finishDate;
    //registerRecruitmentInfo->addNewRecruitmentInfo(task, numOfApplicant, finishDate);
    //result(task, numOfApplicant, finishDate);

    this->registerInput();
}

void RegisterRecruitmentInfoUI::registerInput()
{
    string task;
    int expectedApplicantNum;
    string finishDate;
    fin >> task >> expectedApplicantNum >> finishDate;
    registerRecruitmentInfo->addNewRecruitmentInfo(task, expectedApplicantNum, finishDate);
    result(task, expectedApplicantNum, finishDate);
}

/*
 함수이름: RegisterRecruitmentInfoUI::result
 기능: 사용자에게 입력한 정보를 표시합니다.
 작성날짜: 2023/05/22
 작성자: 김민정
*/
void RegisterRecruitmentInfoUI::result(string task, int expectedApplicantNum, string finishDate)
{
    fout << "> ";
    fout << task;
    fout << " ";
    fout << expectedApplicantNum;
    fout << " " << finishDate << endl<<endl;

}

/*
 함수이름: RegisterRecruitmentInfoUI::addNewRecruitmentInfo
 기능: companyClient에게 RecruitmentInfo를 추가하도록 합니다.
 작성날짜: 2023/05/22
 작성자: 김민정
*/
void RegisterRecruitmentInfo::addNewRecruitmentInfo(string task, int expectedApplicantNum, string finishDate)
{
    RecruitmentInfo *tmp = companyClient->addNewRecruitInfo(task, expectedApplicantNum, finishDate);
    this->recruitmentInfoList->addNewRecruitmentInfoList(tmp);
}

void RecruitmentInfoList::addNewRecruitmentInfoList(RecruitmentInfo* ri) {
    this->rCList.push_back(ri);
}
/*
 함수이름: CompanyClient::addNewRecruitInfo
 기능: company client의 포인터가 RecruitmentInfo를 추가합니다
 작성날짜: 2023/05/22
 작성자: 김민정
*/
RecruitmentInfo* CompanyClient::addNewRecruitInfo(string task, int expectedApplicantNum, string finishDate)
{
    string name;
    string bn;

    name = this->getName();
    bn = this->getbn();
    RecruitmentInfo* newRecruitmentInfo = new RecruitmentInfo(name, bn, task, expectedApplicantNum, finishDate);
    this->registeredList.push_back(newRecruitmentInfo);
    return newRecruitmentInfo;

}

/*
 함수이름: RecruitmentInfo::RecruitmentInfo
 기능: 새로운 RecruitmentInfo 객체를 생성합니다.
 작성날짜: 2023/05/22
 작성자: 김민정
*/
RecruitmentInfo::RecruitmentInfo(string companyName, string bn, string task, int expectedApplicantNum, string finishDate)
{
    this->companyName = companyName;
    this->bn = bn;
    this->task = task;
    this->expectedApplicantNum = expectedApplicantNum;
    this->finishDate = finishDate;
}

/*
 함수이름: InquireRecruitmentInfo::InquireRecruitmentInfo
 기능: InquireRecruitmentInfo control 클래스의 생성자입니다
 작성날짜: 2023/05/22
 작성자: 김민정
*/
InquireRecruitmentInfo::InquireRecruitmentInfo(CompanyClient* companyClient)
{
    this->companyClient = companyClient;
    vector<RecruitmentInfo*> tmp = this->companyClient->getListRegisteredInfo();
    int size = tmp.size();
    
    InquireRecruitmentInfoUI* inquireRecruitmentInfoUI = new InquireRecruitmentInfoUI(this);
    inquireRecruitmentInfoUI->startInterface(tmp);
}

/*
 함수이름: InquireRecruitmentInfoUI::InquireRecruitmentInfo
 기능: InquireRecruitmentInfoUI boundary 클래스의 생성자입니다
 작성날짜: 2023/05/22
 작성자: 김민정
*/
InquireRecruitmentInfoUI::InquireRecruitmentInfoUI(InquireRecruitmentInfo* inquireRecruitmentInfo)
{
    this->inquireRecruitmentInfo = inquireRecruitmentInfo;
}

/*
 함수이름: InquireRecruitmentInfoUI::startInterface
 기능: 사용자인 회사 회원의 RecruitmentInfo를 출력합니다.
 작성날짜: 2023/05/22
 작성자: 김민정
*/
void InquireRecruitmentInfoUI::startInterface(vector<RecruitmentInfo*> riList)
{
    int size = riList.size();
    for (int i = 0; i < size; i++) {
        fout <<"> "<< riList[i]->getTask() << " " << riList[i]->getExpectedApplicantNum() << " " << riList[i]->getFinishDate() << "\n\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////


CompanyClient* CompanyClientList::findById(string id) {
    int size = cCList.size();

    for (int i = 0; i < size; i++) {
        if (id == cCList[i]->getId()) {
            return cCList[i];
        }
    }
}

GeneralClient* GeneralClientList::findById(string id) {
    int size = gCList.size();

    for (int i = 0; i < size; i++) {
        if (id == gCList[i]->getId()) {
            return gCList[i];
        }
    }
}

vector<RecruitmentInfo*> CompanyClient::getListRegisteredInfo() {
    return registeredList;
}


string RecruitmentInfo::getTask() {
    return this->task;
}
int RecruitmentInfo::getApplicantNum() {
    return this->numOfApplicant;
}
string RecruitmentInfo::getFinishDate() {
    return this->finishDate;
}

RecruitmentInfoList* RegisterRecruitmentInfo::getRecruitmentInfoList() {
    return this->recruitmentInfoList;
}

RecruitmentInfo* RegisterRecruitmentInfo::getRegisteredList() {
    return this->registeredList;
}


vector<RecruitmentInfo*> RecruitmentInfoList::getRIList() {
    return this->rCList;
}


void GeneralClient::addApplication(RecruitmentInfo* ri) {
    this->appliedList.push_back(ri);
}

//지원자수 한명 추가
void RecruitmentInfo::addApplicantToRecruitment() {
    this->numOfApplicant += 1;
}

//지원자수 한명 감소
void RecruitmentInfo::subApplicantToRecruitment() {
    this->numOfApplicant -= 1;
}

int RecruitmentInfo::getExpectedApplicantNum() {
    return this->expectedApplicantNum;
}

void RecruitmentInfoList::setRecruitmentInfo(vector<RecruitmentInfo*> riList) {
    this->rCList = riList;
}

//-----------------------------------------------

SearchRecruitmentInfoUI::SearchRecruitmentInfoUI(SearchRecruitmentInfo* searchRecruitmentInfo) {
    this->searchRecruitmentInfo = searchRecruitmentInfo;
}


void SearchRecruitmentInfoUI::startInterface() {
    //입력창을 띄우고 

    string companyName;
    fin >> companyName;


    this->searchRecruitmentInfo->searchRecruitmentInfoListByComName(companyName);

    fout << "> " << this->searchRecruitmentInfo->getResult()->getName() << " " <<
        this->searchRecruitmentInfo->getResult()->getBn() << " " << this->searchRecruitmentInfo->getResult()->getTask() << " " <<
        this->searchRecruitmentInfo->getResult()->getExpectedApplicantNum()<<" " << this->searchRecruitmentInfo->getResult()->getFinishDate() << "\n\n";




}
RecruitmentInfo* SearchRecruitmentInfo::getResult() {
    return this->result;
}

SearchRecruitmentInfo::SearchRecruitmentInfo(RecruitmentInfoList* riList) {
    this->riList = riList;
    this->companyName = "";

    SearchRecruitmentInfoUI* searchRecruitmentInfoUI = new SearchRecruitmentInfoUI(this);
    searchRecruitmentInfoUI->startInterface();
}

void SearchRecruitmentInfo::searchRecruitmentInfoListByComName(string companyName) {
    this->companyName = companyName;
    this->result = this->riList->findByName(companyName);

}


//채용 지원

ApplyForRecruitmentInfoUI::ApplyForRecruitmentInfoUI(ApplyForRecruitmentInfo* applyForRecruitmentInfo) {
    this->applyForRecruitmentInfo = applyForRecruitmentInfo;
}

void ApplyForRecruitmentInfoUI::applyForRecruitmentInfoByNum(string bn) {
    this->applyForRecruitmentInfo->addApplicant(bn);
}


void ApplyForRecruitmentInfoUI::startInterface(RecruitmentInfoList* riList) {

    vector<RecruitmentInfo*> tmp;
    tmp = riList->getRIList();
    int size = tmp.size();
    for (int i = 0; i < size; i++) {
        fout << "> " << tmp[i]->getName() << " " << tmp[i]->getBn() << " " << tmp[i]->getTask() << "\n\n";
    }

    string tmpBn;
    fin >> tmpBn;
    this->applyForRecruitmentInfoByNum(tmpBn);

}



ApplyForRecruitmentInfo::ApplyForRecruitmentInfo(GeneralClient* gClient, RecruitmentInfoList* riList) {
    this->gClient = gClient;
    this->riList = riList;//현재 등록된 채용정보 리스트
    vector<RecruitmentInfo*> tmp = riList->getRIList();

    sort(tmp.begin(), tmp.end(), CompareRecruitmentInfo());

    RecruitmentInfoList* tmpRiList = new RecruitmentInfoList(); \
    tmpRiList->setRecruitmentInfo(tmp);

    ApplyForRecruitmentInfoUI* applyForRecruitmentInfoUI = new ApplyForRecruitmentInfoUI(this);

    applyForRecruitmentInfoUI->startInterface(tmpRiList);
}


//
void ApplyForRecruitmentInfo::addApplicant(string bn) {
    appliedRecruitmentInfo = this->riList->findByNum(bn);
    this->gClient->addApplication(appliedRecruitmentInfo);
    this->appliedRecruitmentInfo->addApplicantToRecruitment();//이 채용정보에 지원자수 하나 추가해야함
    fout << endl << "> " << "지원완료: " << this->appliedRecruitmentInfo->getName() << ' ' << this->appliedRecruitmentInfo->getBn() << ' ' << this->appliedRecruitmentInfo->getTask() << endl << endl;
}

// 채용지원

// 지원정보조회
InquireApplicationInfo::InquireApplicationInfo(GeneralClient* gClient) {
    this->gClient = gClient;
    this->gcAppliedList = gClient->getListAppliedInfo();

    vector<RecruitmentInfo*> tmp = gcAppliedList;//해당 회원이 지원한 회원정보 리스트

    sort(tmp.begin(), tmp.end(), CompareRecruitmentInfo());

    InquireApplicationInfoUI* inquireApplicationInfoUI = new InquireApplicationInfoUI();
    inquireApplicationInfoUI->startInterface(tmp);
}




void InquireApplicationInfoUI::startInterface(vector<RecruitmentInfo*> gcAppliedList) {
    int size = gcAppliedList.size();

    for (int i = 0; i < size; i++) {
        fout << "> " << gcAppliedList[i]->getName() << " " << gcAppliedList[i]->getTask() << " " << gcAppliedList[i]->getExpectedApplicantNum()
            << " " << gcAppliedList[i]->getFinishDate() << "\n\n";
    }
}


bool CompareRecruitmentInfo::operator()(const RecruitmentInfo* a, const RecruitmentInfo* b) {
    string aName = a->getName();
    string bName = b->getName();
    if (aName != bName) {
        return aName < bName;
    }
    else {//사실 회사이름이 같은 경우는 없지만 compile을 위한 예외 처리
        return aName > bName;

    }
}

//

CancelApplicationInfo::CancelApplicationInfo(GeneralClient* gClient, RecruitmentInfoList* riList)
{    
    this->gClient = gClient;
    this->riList = riList;

    
    vector<RecruitmentInfo*> tmp = riList->getRIList();

    sort(tmp.begin(), tmp.end(), CompareRecruitmentInfo());

    RecruitmentInfoList* tmpRiList = new RecruitmentInfoList();
    tmpRiList->setRecruitmentInfo(tmp);

    CancelApplicationInfoUI* cancelApplicationInfoUI = new CancelApplicationInfoUI(this);

    cancelApplicationInfoUI->startInterface(tmpRiList);
}



CancelApplicationInfoUI::CancelApplicationInfoUI(CancelApplicationInfo* cancelApplicationInfo)
{
    this->cancelApplicationInfo = cancelApplicationInfo;
    this->bn = "";
}

bool compare(RecruitmentInfo* a, RecruitmentInfo* b) {
    return a->getName() < b->getName(); 
}

void CancelApplicationInfoUI::startInterface(RecruitmentInfoList* riList)
{
    vector<RecruitmentInfo*> tmp;
    tmp = riList->getRIList();
    int size = tmp.size();
    for (int i = 0; i < size; i++) {
        fout << "> " << tmp[i]->getName() << " " << tmp[i]->getBn() << " " << tmp[i]->getTask() << "\n\n";
    }

    this->bnInput();
    //int size = this->cancelApplicationInfo->gcRiList.size();

    
    
}

void CancelApplicationInfoUI::bnInput()
{
    fin >> this->bn;
    this->cancelApplicationInfo->cancelApplication(this->bn); 
}

vector<RecruitmentInfo*> GeneralClient::getListAppliedInfo() {
    return this->appliedList;
}


void CancelApplicationInfo::cancelApplication(string bn)
{
    //컨트롤이 갖고 있는 일반회원의 지원 정보 리스트에서 bn값과 일치하는 채용 정보를 리스트에서 삭제한다
    for (int i = 0; i < this->gcRiList.size(); i++)
    {
        if (gcRiList[i]->getBn() == bn)
        {
            //this->cCList.erase(cCList.begin() + i);
            this->gcRiList.erase(gcRiList.begin() + i);
        }
    }
    //컨트롤이 갖고 있는 전체 채용 정보리스트에서 bn값과 일치하는 채용 정보의 지원자 수를 감소시킨다.

    int tmpSize = this->riList->getRIList().size();

    for (int i = 0; i < tmpSize; i++)
    {
        if (riList[i].getRIList()[i]->getBn() == bn)
        {
            riList[i].getRIList()[i]->subApplicantToRecruitment();
        }
    }

    cout << "정상적으로 삭제되었습니다" << endl;
    
   

}