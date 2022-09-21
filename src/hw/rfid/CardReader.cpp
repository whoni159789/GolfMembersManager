#include "CardReader.h"

CardReader::CardReader(SPI *spi) : mfrc522(spi)
{}

CardReader::~CardReader()
{}

bool CardReader::isCard()
{
    uint8_t byte = mfrc522_request(PICC_REQALL, rfidData);
    if(byte == CARD_FOUND)   // 상속 시 Method 자체만 불러오면 된다.
        return true;
    else
        return false;

    return false;
}

DeviceData CardReader::getCardNumber()
{
    mfrc522_get_card_serial(rfidData);
    cardData.devName = "CardReader";
    cardData.devData.clear();
    for(const auto data : rfidData)
        cardData.devData.push_back((int)data);

    return cardData;
}