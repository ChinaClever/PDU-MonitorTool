/*
 *
 *  Created on: 2020年10月1日
 *      Author: Lzy
 */
#include "datapacket.h"

sDataPacket::sDataPacket()
{
    pro = new sProgress();
    for(int i=0; i<DEV_NUM; ++i) {
        dev[i] = new sDevData;
        clear(i);
    }
}

void sDataPacket::clear(int id)
{
    memset(dev[id], 0, sizeof(sDevData));
}


sDataPacket *sDataPacket::bulid()
{
    static sDataPacket* sington = nullptr;
    if(sington == nullptr)
        sington = new sDataPacket();
    return sington;
}

void sDataPacket::init()
{
    clear();
    pro->step = Test_Fun;
    pro->result = Test_Info;
    pro->startTime = QTime::currentTime();
}

void sDataPacket::updatePro(bool pass, const QString &str)
{
    if(!pass) {
        pro->step = Test_Over;
        pro->result = Test_Fail;
    }

    pro->pass << pass;
    pro->itPass << pass;

    pro->item << str;
    pro->status << str;
}
