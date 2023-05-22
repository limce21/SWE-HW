#include "hw3.h"

void System::doTask()
{
    int menu_level_1 = 0, menu_level_2 = 0;
    int is_program_exit = 0;
    ClientList* clientList = new ClientList();
    GeneralClientList* gcList = new GeneralClientList();
    CompanyClientList* ccList = new CompanyClientList();
    Client* curLogInClient=0;
    LogIn* logIn=0;

    fin.open(INPUT_FILE_NAME);
    fout.open(OUTPUT_FILE_NAME);


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
                SignIn* signIn = new SignIn(clientList, gcList, ccList);

                break;
            }

            case 2:
            {
                fout << "1.2. 회원탈퇴" << endl;
                
                if (logIn != nullptr) //한명이라도 로그인이 되어있는 경우에만 실행
                {
                    curLogInClient = logIn->getLogInClient(); //로그인된 계정을 알아온다
                    if (curLogInClient != nullptr) //로그인된 계정이 있는 경우에만 회원탈퇴 시도
                    {
                        SignOut* signOut = new SignOut(clientList, gcList, ccList, curLogInClient);

                    }
                }
                else //로그인되어있는 사람이 없는 경우 
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
                logIn = new LogIn(clientList, gcList, ccList);
                //cout << clientList->count();
                break;


            }
            case 2:
            {
                fout << "2.2. 로그아웃" << endl;
                if (logIn != nullptr) //한명이라도 로그인이 되어있는 경우에만 실행
                {
                    curLogInClient = logIn->getLogInClient(); //로그인된 계정을 알아온다
                    if (curLogInClient != nullptr) //로그인된 계정이 있는 경우에만 회원탈퇴 시도
                    {
                        LogOut* logOut = new LogOut(clientList, gcList, ccList, curLogInClient);

                    }
                }

                else
                {
                    cout<<"로그아웃 할 수 없습니다" << endl;
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
                    CompanyClient *tmpCompanyClient = ccList->findById(tmpid);
                    int tmp = curLogInClient->getType();
                    // int tmp = curLogInClient.getType();
                    if (tmp == 2) {
                        cout << "일반 회원은 채용정보 등록이 불가능합니다.\n";
                    }
                    else {
                        //CompanyClient *companyClient = findByID(로그인된 객체의 id)
                        
                        RegisterRecruitmentInfo* registerRecruitmentInfo = new RegisterRecruitmentInfo(tmpCompanyClient);
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
     
        case 6: {
            switch (menu_level_2)
            {
            case 1: // "6.1. 종료“ 메뉴 부분
            {
                fout << "6.1.종료" << endl << endl;
                is_program_exit = 1; 
                break;
            }
            }
            break;
        }
        }
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

Client::Client(int type, string name, string id, string pw)
{
    this->type = type;
    this->_name = name;
    this->_id = id;
    this->_pw = pw;
    // this->_num = num;
    this->_isLogIn = false;
}

string Client::getId()
{
    return this->_id;
}

string Client::getPw()
{
    return this->_pw;
}
int Client::getType()
{
    return this->type;
}
bool Client::getLogInStatus()
{
    return this->_isLogIn;
}

// 채용 정보 등록 시 getName
string Client::getName()
{
    return this->_name;
}

void Client::changeLogInStatus()
{
    if (this->_isLogIn == false)
    {
        this->_isLogIn = true;
    }

    else
    {
        this->_isLogIn = false;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
CompanyClient::CompanyClient(int type, string name, string num, string id, string pw) :Client(type, name, id, pw)
{
    this->_bn = num;
}

string CompanyClient::getbn()
{
    return this->_bn;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
GeneralClient::GeneralClient(int type, string name, string num, string id, string pw) :Client(type, name, id, pw)
{
    this->_rrn = num;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClientList::addClient(Client* c)
{
    this->cList.push_back(c);
}

int ClientList::size()
{
    return this->cList.size();
}

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

   작성날짜: 2023/05/31
   작성자: 박시홍
*/
void ClientList::destroy(int idx)
{
    this->cList.erase(cList.begin() + idx); //해당 인덱스의 회원 정보 삭제
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////


void CompanyClientList::addCompanyClient(CompanyClient* c)
{
    this->cCList.push_back(c);
}


/*
   함수이름: CompanyClientList::destroy
   기능: 입력받은 해당 id값과 일치하는 회사 회원 정보를 삭제한다
   매개변수: id -> 삭제할 회원의 id값
   반환값: 없음

   작성날짜: 2023/05/31
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
SignIn::SignIn(ClientList* list,GeneralClientList*gcList, CompanyClientList*ccList)
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
    this->pSignIn->addNewClient(this->type, this->name, this->num, this->id, this->pw);


    
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
        CompanyClient* cClient = new CompanyClient(clientType,name, num, id, pw); //회사회원 객체 생성
        Client* client = new Client(clientType,name, id, pw); //회원 객체 생성
        this->cList->addClient(client); //회원 리스트에 저장
        this->ccList->addCompanyClient(cClient); //회사 회원 리스트에 저장
        
        
        
    }

    else //입력받은 정보 중 type값이 일반회원인 경우
    {
        GeneralClient* gClient = new GeneralClient(clientType,name, num, id, pw); //일반회원 객체 생성
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
                fout <<'>'<<temp[i]->getId() << ' ' << temp[i]->getPw() << endl<<endl; //로그인이 완료되면 완료되었다는 정보를 파일에 출력함
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
        cout<<"없는 계정입니다." << endl;
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
    this->pLogIn->tryLogIn(this->id, this->pw);
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
LogOut::LogOut(ClientList* list, GeneralClientList* gcList, CompanyClientList* ccList,Client* client)
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

    
       this->pLogOutUI->startInterface(id,isPossible); //바운더리 클래스에 로그아웃 성공값과 로그아웃한 계정의 id값을 매개변수로 보내준다
    
    
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

   
    this->pSignOutUI->startInterface(id,isPossible); //바운더리 클래스에 회원탈퇴 성공값과 회원탈퇴한 계정의 id값을 매개변수로 보내준다
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
void SignOutUI::startInterface(string id,bool flag)
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
RegisterRecruitmentInfo::RegisterRecruitmentInfo(CompanyClient* companyClient)
{
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
    string _task;
    int numOfApplicant;
    string _finishDate;

    fin >> _task >> numOfApplicant >> _finishDate;
    registerRecruitmentInfo->addNewRecruitmentInfo(_task, numOfApplicant, _finishDate);
    result(_task, numOfApplicant, _finishDate);
}

/*
 함수이름: RegisterRecruitmentInfoUI::result
 기능: 사용자에게 입력한 정보를 표시합니다.
 작성날짜: 2023/05/22
 작성자: 김민정
*/
void RegisterRecruitmentInfoUI::result(string _task, int numOfApplicant, string _finishDate)
{
    fout << "> ";
    fout << _task;
    fout << " ";
    fout << numOfApplicant; 
    fout << " " << _finishDate << endl;

}

/*
 함수이름: RegisterRecruitmentInfoUI::addNewRecruitmentInfo
 기능: companyClient에게 RecruitmentInfo를 추가하도록 합니다.
 작성날짜: 2023/05/22
 작성자: 김민정
*/
void RegisterRecruitmentInfo::addNewRecruitmentInfo(string _task, int numOfApplicant, string _finishDate)
{
    companyClient->addNewRecruitInfo(_task, numOfApplicant, _finishDate);
}

/*
 함수이름: CompanyClient::addNewRecruitInfo
 기능: company client의 포인터가 RecruitmentInfo를 추가합니다
 작성날짜: 2023/05/22
 작성자: 김민정
*/
void CompanyClient::addNewRecruitInfo(string _task, int numOfApplicant, string _finishDate)
{
    string name;
    string bn;

    name = this->getName();
    bn = this->getbn();
    RecruitmentInfo* newRecruitmentInfo = new RecruitmentInfo(name, bn, _task, numOfApplicant, _finishDate);
}

/*
 함수이름: RecruitmentInfo::RecruitmentInfo
 기능: 새로운 RecruitmentInfo 객체를 생성합니다.
 작성날짜: 2023/05/22
 작성자: 김민정
*/
RecruitmentInfo::RecruitmentInfo(string _companyName, string _bn, string _task, int numOfApplicant, string _finishDate)
{
    this->_companyName = _companyName;
    this->_bn = _bn;
    this->_task = _task;
    this->numOfApplicant = numOfApplicant;
    this->_finishDate = _finishDate;
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
    InquireRecruitmentInfoUI* inquireRecruitmentInfoUI = new InquireRecruitmentInfoUI(this);
    inquireRecruitmentInfoUI->startInterface();
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
void InquireRecruitmentInfoUI::startInterface()
{

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

