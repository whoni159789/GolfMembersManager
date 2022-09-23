#include "MembersEntity.h"
#include <cstring>          // = #include <string.h>

MembersEntity::MembersEntity()
{
    loadMembersInfo();
}

MembersEntity::~MembersEntity()
{

}

void MembersEntity::loadMembersInfo()
{
    fpDBData = fopen("memberLists.bin", "r");                        // r+ : read하면서 write도 할 수 있다.
    if(fpDBData == NULL)
    {
        fprintf(stderr, "file open error!\n");
        return;
    }
    while(fread(&memberInfo, sizeof(MemberInfo), 1, fpDBData))       // fpDBData를 1번 읽는다. / memberInfo : Buffer에 해당함
    {
        vecMembersList.push_back(memberInfo);                        // 읽은 데이터를 vecMembersList에 넣는다.
    }
    fclose(fpDBData);
}

void MembersEntity::printMemberInfo(int index)
{
    if(index > (int)vecMembersList.size())
    {
        fprintf(stderr, "Out of range member count!\n");
        return;
    }

    printf("%04d, %s, %s, %s, %0x-%0x-%0x-%0x-%0x\n", 
    vecMembersList[index].id,
    vecMembersList[index].name,
    vecMembersList[index].address,
    vecMembersList[index].phoneNumber,
    vecMembersList[index].cardNum[0],
    vecMembersList[index].cardNum[1],
    vecMembersList[index].cardNum[2],
    vecMembersList[index].cardNum[3],
    vecMembersList[index].cardNum[4]
    );
}

void MembersEntity::printMemberInfo(std::string name)
{
    for(const auto &member : vecMembersList)
    {
        if(strcmp(member.name, name.c_str()) == 0)
        {
            printf("%04d, %s, %s, %s, %0x-%0x-%0x-%0x-%0x\n", 
            member.id,
            member.name,
            member.address,
            member.phoneNumber,
            member.cardNum[0],
            member.cardNum[1],
            member.cardNum[2],
            member.cardNum[3],
            member.cardNum[4]);
            return;
        }
    }
}

void MembersEntity::printMemberInfo(int *cardNum)
{
    for(const auto &member : vecMembersList)
    {
        if(memcmp(member.cardNum, cardNum, sizeof(member.cardNum)) == 0)
        {
            printf("%04d, %s, %s, %s, %0x-%0x-%0x-%0x-%0x\n", 
            member.id,
            member.name,
            member.address,
            member.phoneNumber,
            member.cardNum[0],
            member.cardNum[1],
            member.cardNum[2],
            member.cardNum[3],
            member.cardNum[4]);
            return;
        }
    }
}

bool MembersEntity::findMemberInfo(int index)
{
    for(const auto &member : vecMembersList)
    {
        if(member.id == index)
        {
            return true;
        }
    }
    return false;
}

bool MembersEntity::findMemberInfo(std::string name)
{
    for(const auto &member : vecMembersList)
    {
        if(strcmp(member.name, name.c_str()) == 0)
        {
            return true;
        }
    }
    return false;
}

bool MembersEntity::findMemberInfo(int *cardNum)
{
    for(const auto &member : vecMembersList)
    {
        if(memcmp(member.cardNum, cardNum, sizeof(member.cardNum)) == 0)
        {
            return true;
        }
    }
    return false;
}

void MembersEntity::searchMemberInfo(int *cardNum)
{
    for(const auto &member : vecMembersList)
    {
        if(memcmp(member.cardNum, cardNum, sizeof(member.cardNum)) == 0)
        {
            printf("%s", member.name);
        }
    }
}

int MembersEntity::searchMemberID(int *cardNum)
{
    for(const auto &member : vecMembersList)
    {
        if(memcmp(member.cardNum, cardNum, sizeof(member.cardNum)) == 0)
        {
            return member.id;
        }
    }
}

void MembersEntity::addMemberInfo(MemberInfo member)
{
    vecMembersList.push_back(member);
}

bool MembersEntity::delMeberInfo(int *cardNum)
{   
    std::vector<MemberInfo>::iterator itrMember;    // 중간에 데이터를 집어넣고 싶을 때는 insert() 사용 -> 해당 주소값을 주어야 한다.
    itrMember = vecMembersList.begin();             // vecMembersList vector의 첫 번째 주소를 itrMemver에게 준다.
    for(itrMember; itrMember != vecMembersList.end() ; itrMember++)
    {
        if(memcmp(itrMember->cardNum, cardNum, sizeof(itrMember->cardNum)) == 0)
        {
            vecMembersList.erase(itrMember);
            return true;
        }
    }
    return false;                                   // vector 기능을 통해 생긴 heap 영역의 배열 중간에 있는 데이터를 삭제할 때 사용 -> 해당 주소값을 입력해야함
                                                    // 하지만 insert와 erase 시에는 loading이 많아지기 때문에 좋지 않다.(array이기 때문에)
}

void MembersEntity::modifyMemberInfo(int *cardNum)
{
    MemberInfo tempMember;
    tempMember.id = searchMemberID(cardNum);

    std::vector<MemberInfo>::iterator itrMember;    
    itrMember = vecMembersList.begin();             
    for(itrMember; itrMember != vecMembersList.end() ; itrMember++)
    {
        if(memcmp(itrMember->cardNum, cardNum, sizeof(itrMember->cardNum)) == 0)
        {
            vecMembersList.erase(itrMember);
            
            std::cout << "Name : ";
            std::cin >> tempMember.name;
            std::cout << "Address : ";
            std::cin >> tempMember.address;
            std::cout << "PhoneNumber : ";
            std::cin >> tempMember.phoneNumber;
            memcpy(tempMember.cardNum, cardNum, sizeof(tempMember.cardNum));
            
            vecMembersList.insert(itrMember, tempMember);
            printf("%s's information is updated!\n", tempMember.name);
        }
    }
    
}

void MembersEntity::memoryToDB()
{
    // vecMembersList의 값을 file에 write
    // 1. file open
    // 2. vdcMembersList의 값을 하나씩 read
    // 3. vecMembersList의 끝까지 file에 write
    // 4. file close

    fpDBData = fopen("memberLists.bin", "w");   // 기존 값에 덮어씌우기 할 때는 mode를 w로
    FILE *fpDBData2 = fopen("memberLists.txt", "w");
    if(fpDBData == NULL)
    {
        fprintf(stderr, "file open error!\n");
        return;
    }
    for(const auto &member : vecMembersList)
    {
        fwrite(&member, sizeof(member), 1, fpDBData);
        fprintf(fpDBData2, "%05d, %s\n", member.id, member.name);
    }
    fclose(fpDBData);
    fclose(fpDBData2);
}