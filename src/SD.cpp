// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include "SD.h"

#include <sys/statvfs.h>

using namespace fs;

SDFS::SDFS() {};

bool SDFS::begin(uint8_t ssPin)
{
    return true;
}

void SDFS::end()
{
}

sdcard_type_t SDFS::cardType()
{
    return CARD_NONE;
}

uint64_t SDFS::cardSize()
{
    struct statvfs stat;
    if (statvfs("/", &stat) != 0)
    {
        // error happens, just quits here
        return -1;
    }

    return stat.f_bsize * stat.f_bavail;
}

uint64_t SDFS::totalBytes()
{
    struct statvfs stat;
    if (statvfs("/", &stat) != 0)
    {
        // error happens, just quits here
        return -1;
    }

    return stat.f_bsize * stat.f_bavail;
}

uint64_t SDFS::usedBytes()
{
  struct statvfs stat;
    if (statvfs("/", &stat) != 0)
    {
        // error happens, just quits here
        return -1;
    }

    return stat.f_bsize * (stat.f_bavail-stat.f_bfree);
}

SDFS SD ;
