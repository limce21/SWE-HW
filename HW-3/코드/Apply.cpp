#include "Apply.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdlib.h>


SearchRecruitmentInfoUI::SearchRecruitmentInfoUI(SearchRecruitmentInfo *searchRecruitmentInfo) {
	this->searchRecruitmentInfo = searchRecruitmentInfo;
}


void SearchRecruitmentInfoUI::startInterface() {
	//입력창을 띄우고 
	string companyName;
	fin >> companyName;
	
	this->searchRecruitmentInfo->searchRecruitmentInfoListByComName(companyName);
	
	fout << "> " << this->searchRecruitmentInfo->getResult()->getName() << " "<<
		this->searchRecruitmentInfo->getResult()->getBn() << " " << this->searchRecruitmentInfo->getResult()->getTask() << " " << 
		this->searchRecruitmentInfo->getResult()->getApplicantNum() << this->searchRecruitmentInfo->getResult()->getFinishDate()<<"\n";

	


}
RecruitmentInfo* SearchRecruitmentInfo::getResult() {
	return this->result;
}

SearchRecruitmentInfo::SearchRecruitmentInfo(RecruitmentInfoList* riList) {
	this->riList = riList;

	SearchRecruitmentInfoUI* searchRecruitmentInfoUI = new SearchRecruitmentInfoUI(this);
	searchRecruitmentInfoUI->startInterface();
}

void SearchRecruitmentInfo::searchRecruitmentInfoListByComName(string companyName) {
	this->companyName = companyName;
	this->result = this->riList->findByName(companyName);

}


//채용 지원

ApplyForRecruitmentInfoUI::ApplyForRecruitmentInfoUI(ApplyForRecruitmentInfo *applyForRecruitmentInfo) {
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
		fout << tmp[i]->getName() << " " << tmp[i]->getBn() << " " << tmp[i]->getTask() 
			<< " " << tmp[i]->getApplicantNum() << " " << tmp[i]->getFinishDate() << "\n";
	}

	string tmpBn;
	fin >> tmpBn;
	this->applyForRecruitmentInfoByNum(tmpBn);
	
}


ApplyForRecruitmentInfo::ApplyForRecruitmentInfo(GeneralClient* gClient, RecruitmentInfoList* riList) {
	this->gClient = gClient;
	this->riList = riList;
	vector<RecruitmentInfo*> tmp = riList->getRIList();
	sort(tmp.begin(), tmp.end(), compare);//정렬
	RecruitmentInfoList* tmpRiList = new RecruitmentInfoList(tmp);

	ApplyForRecruitmentInfoUI* applyForRecruitmentInfoUI = new ApplyForRecruitmentInfoUI(this);

	applyForRecruitmentInfoUI->startInterface(tmpRiList);
}

bool ApplyForRecruitmentInfo::compare(RecruitmentInfo &a, RecruitmentInfo&b) {
	string aName = a.getName();
	string bName = b.getName();
	if (aName != bName) {
		return aName < bName;
	}
	else {//회사이름이 같은 경우는 사실 존재하지 않음.
		return true;
	}
}

//
void ApplyForRecruitmentInfo::addApplicant(string bn) {
	appliedRecruitmentInfo = this->riList->findByNum(bn);
	this->gClient->addApplication(appliedRecruitmentInfo);
	this->appliedRecruitmentInfo->addApplicantToRecruitment();//이 채용정보에 지원자수 하나 추가해야함
}
