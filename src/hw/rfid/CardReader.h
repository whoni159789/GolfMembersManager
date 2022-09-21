#ifndef CARDREADER_H
#define CARDREADER_H

#pragma once

#include <iostream>
#include "mfrc522.h"
#include "DeviceData.h"

class CardReader : public mfrc522   // public과 protected(외부 사용 X, 상속 사용 O)만 사용 가능
{
private:
    uint8_t rfidData[16];
    DeviceData cardData;

public:
    CardReader(SPI *spi);
    ~CardReader();
    bool isCard();
    DeviceData getCardNumber();


};

#endif