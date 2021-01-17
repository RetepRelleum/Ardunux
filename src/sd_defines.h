
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
#ifndef _SD_DEFINES_H_
#define _SD_DEFINES_H_

typedef enum {
    CARD_NONE,
    CARD_MMC,
    CARD_SD,
    CARD_SDHC,
    CARD_UNKNOWN
} sdcard_type_t;

#define TF_CS   4  // TF (Micro SD Card) CS pin
#define TS_CS   12 // Touch Screen CS pin
#define TFT_CS  14 // TFT CS pin
#define TFT_LED 32 // TFT backlight control pin
#define TFT_RST 33 // TFT reset pin
#define TFT_DC  27 // TFT DC pin

#define SS      TF_CS
#endif /* _SD_DISKIO_H_ */
