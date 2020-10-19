/*
 *
 *  Created on: 2020年10月1日
 *      Author: Lzy
 */
#include "datapacket.h"

sDataPacket::sDataPacket()
{
    for(int i=0; i<DEV_NUM; ++i) {
        dev[i] = new sDevData;
        clear(i);
    }
}

void sDataPacket::clear(int id)
{
    memset(dev[id], 0, sizeof(sDevData));
    status.clear();
}


sDataPacket *sDataPacket::bulid()
{
    static sDataPacket* sington = nullptr;
    if(sington == nullptr)
        sington = new sDataPacket();
    return sington;
}
