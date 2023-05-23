#ifndef APPLY_H
#define APPLY_H
#include "hw3.h"


//class 전방선언
class SearchRecruitmentInfoUI;
class SearchRecruitmentInfo;
class CancelApplicationIfoUI;
class CancelApplicationIfo;

class CancelApplicationIfoUI
{
private:
	CancelApplicationIfo* cancelApplicationIfo;
	string bn;
public:
	CancelApplicationIfoUI(CancelApplicationIfo* cancelApplicationIfo);
	void startInterface();
};

class CancelApplicationIfo
{
private:
	GeneralClient* gClient;
	RecruitmentInfoList* riList;
	RecruitmentInfo* appliedRecruitmentInfo;


public:
	CancelApplicationIfo(GeneralClient* gClient, RecruitmentInfoList* riList);
	void cancelApplication(string bn);
};


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
	ApplyForRecruitmentInfoUI(ApplyForRecruitmentInfo*applyForRecruitmentInfo);
	void startInterface(RecruitmentInfoList *riList);
	void applyForRecruitmentInfoByNum(string bn);
};


class ApplyForRecruitmentInfo {
private:
	GeneralClient *gClient;
	RecruitmentInfoList* riList;
	RecruitmentInfo* appliedRecruitmentInfo;

public:
	bool compare(RecruitmentInfo &a, RecruitmentInfo&b);
	ApplyForRecruitmentInfo(GeneralClient* gClient, RecruitmentInfoList* riList);
	void addApplicant(string bn);
};

// 채용 지원

class InquireApplicationInfoUI {
private:

public:
	void startInterface();
};



class InquireApplicationInfo {
private:

public:

};

#endif // !APPLY_H


