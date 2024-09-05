//
// Created by ender on 04/09/2024.
//

#ifndef EFTP_H
#define EFTP_H

enum EFTP {
    EFTDISCOVER = 0x1,
    EFTCONN = 0x2,
    EFTINFO = 0x3,
    EFTDIR = 0x4,
    EFTSEND = 0x5,
    EFTSTATUS = 0x6,
    EFTREAD = 0x7
};

enum EFTP_INFOS {
    DIR = 0x1,
    SINGLE = 0x2,
};

#endif //EFTP_H
