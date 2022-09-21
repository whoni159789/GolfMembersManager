#ifndef DEVICEDATA_H
#define DEVICEDATA_H

#pragma once

#include <string>
#include <vector>

struct DeviceData
{
    std::string devName;
    std::vector<uint8_t> devData;
};

#endif