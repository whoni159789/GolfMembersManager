#ifndef MEMBERSENTITY_H
#define MEMBERSENTITY_H

#pragma once

#include <vector>           // vector를 이용해 data를 올릴 것
#include <string>
#include <iostream>
#include "MemberInfo.h"

class MembersEntity
{
private:
    std::vector<MemberInfo> vecMembersList;
    MemberInfo memberInfo;
    FILE *fpDBData;
    
public:
    MembersEntity();
    ~MembersEntity();
    void loadMembersInfo();
    void registerMember(int *cardNum);
    void addMemberInfo(MemberInfo member);
    bool delMeberInfo(int *cardNum);
    bool findMemberInfo(std::string name);
    bool findMemberInfo(int *cardNum);
    void printMemberInfo(std::string name);
    void printMemberInfo(int *cardNum);
    int searchMemberID(int *cardNum);
    char* searchMemberName(int *cardNum);
    void modifyMemberInfo(int *cardNum);
    void memoryToDB();
};

#endif