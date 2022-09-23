#include "golfMembershipManager.h"

golfMembershipManager::golfMembershipManager()
// mfrc522 *rfid = new mfrc522(new SPI(10, 3000000)); 
// -> STACK : 작은 내용 (1M), HEAP : 큰 내용 (4G)
// Listener *listener = new Listener(&rfid);
{
    // listener = new Listener();
}

golfMembershipManager::~golfMembershipManager()
{

}

void golfMembershipManager::run()
{
    while(1)
    {
        listener->checkEvent();
        delay(10);
    }
}