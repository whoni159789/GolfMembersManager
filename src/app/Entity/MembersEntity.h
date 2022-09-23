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
    void addMemberInfo(MemberInfo member);
    bool delMeberInfo(int *cardNum);
    void memoryToDB();
    void printMemberInfo(int index);
    void printMemberInfo(std::string name);
    void printMemberInfo(int *cardNum);
    bool findMemberInfo(int index);
    bool findMemberInfo(std::string name);
    bool findMemberInfo(int *cardNum);
    void searchMemberInfo(int *cardNum);
    int searchMemberID(int *cardNum);
    void modifyMemberInfo(int *cardNum);
};

#endif