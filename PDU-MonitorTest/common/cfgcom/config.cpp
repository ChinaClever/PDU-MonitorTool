/*
 * 配置文件公共基类
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "config.h"

Cfg::Cfg()
{
    mCfg = CfgCom::bulid();
    item = new sCfgItem();

    initCnt();
    initErrData();
    initCfgDev();
    initCurrentNum();
}

Cfg *Cfg::bulid()
{
    static Cfg* sington = nullptr;
    if(sington == nullptr)
        sington = new Cfg();
    return sington;
}


int Cfg::initAddr()
{
    item->vref = read("vref", false,"Sys").toBool();
    return read("addr", 1,"Sys").toInt();
}

void Cfg::setAddr(int addr)
{
    write("addr", addr, "Sys");
    write("vref", item->vref,"Sys");
}

void Cfg::initErrData()
{
    item->err.volErr = read("vol", 1,"Err").toInt();
    item->err.curErr = read("cur", 1,"Err").toInt();
    item->err.powErr = read("pow", 100,"Err").toInt();
}

void Cfg::writeErrData()
{
    write("vol", item->err.volErr, "Err");
    write("cur", item->err.curErr, "Err");
    write("pow", item->err.powErr, "Err");
}

void Cfg::initCnt()
{
    item->cnt.num = read("num", 0, "Cnt").toInt();
    item->cnt.all = read("all", 0, "Cnt").toInt();
    item->cnt.ok = read("ok", 0, "Cnt").toInt();
    item->cnt.err = read("err", 0, "Cnt").toInt();
}

void Cfg::writeCnt()
{
    write("num", item->cnt.num, "Cnt");
    write("all", item->cnt.all, "Cnt");
    write("ok", item->cnt.ok, "Cnt");
    write("err", item->cnt.err, "Cnt");
}



void Cfg::initCfgDev()
{
    item->user = read("user", "", "User").toString();
    item->cTh.type = read("cth_type", 1).toInt();
    item->cTh.vol_min = read("vol_min", 80).toInt();
    item->cTh.vol_max = read("vol_max", 276).toInt();
    item->cTh.cur_min = read("cur_min", 0).toInt();
    item->cTh.cur_max = read("cur_max", 320).toInt();
    item->cTh.enModify = read("en_modify", 0).toInt();

    QString g = "siCfg";
    item->si.led = false;
    item->si.si_mod = read("si_mod", 0, g).toInt();
    item->si.ac = read("ac", 1, g).toInt();
    item->si.lines = read("lines", 1, g).toInt();

    g = "ipCfg";
    item->ip.addr = read("ip_addr", "192.168.1.163", g).toString();
    item->ip.version = read("version", 1, g).toInt();
    item->ip.lines = read("lines", 1, g).toInt();
    item->ip.modbus = read("modbus", 0, g).toInt();
    item->ip.log = read("log_en", 0, g).toInt();
    item->ip.security = read("security", 0, g).toInt();
    item->ip.standard = read("standard", 0, g).toInt();
    item->ip.language = read("language", 1, g).toInt();
    item->ip.lcd = read("lcd", 0, g).toInt();
    item->ip.protocol = read("protocol", 0, g).toInt();
    item->sw_ver = read("sw_ver", "", g).toString();
    item->ip.inFirst = read("ip_inFirst", "IEC309", g).toString();
    item->ip.inSecond = read("ip_inSecond", "18A", g).toString();
    item->ip.outFirst = read("ip_outFirst", "20xC13", g).toString();
    item->ip.outSecond = read("ip_outSecond", "4xC19", g).toString();
}

void Cfg::writeCfgDev()
{
    write("user", item->user, "User");
    write("cth_type", item->cTh.type);
    write("vol_min", item->cTh.vol_min);
    write("vol_max", item->cTh.vol_max);
    write("cur_min", item->cTh.cur_min);
    write("cur_max", item->cTh.cur_max);
    write("en_modify", item->cTh.enModify);

    QString g = "siCfg";
    //write("si_mod", item->si.si_mod, g);
    //write("ac", item->si.ac, g);
    //write("lines", item->si.lines, g);

    g = "ipCfg";
    write("ip_addr", item->ip.addr, g);
    write("version", item->ip.version, g);
    write("lines", item->ip.lines, g);
    write("modbus", item->ip.modbus, g);
    write("log_en", item->ip.log, g);
    write("standard", item->ip.standard, g);
    write("language", item->ip.language, g);
    write("security", item->ip.security, g);
    write("lcd", item->ip.lcd, g);
    write("protocol", item->ip.protocol, g);
    write("sw_ver", item->sw_ver, g);
    write("ip_inFirst", item->ip.inFirst, g);
    write("ip_inSecond", item->ip.inSecond, g);
    write("ip_outFirst", item->ip.outFirst, g);
    write("ip_outSecond", item->ip.outSecond, g);
}


/**
 * @brief 获取串口名称
 * @return 串口名
 */
QString Cfg::getSerialName(const QString &key)
{
    return mCfg->read(key, "", "Serial").toString();
}

/**
 * @brief 设置串口名
 * @param name
 */
void Cfg::setSerialName(const QString &key, const QString &v)
{
    mCfg->write(key, v, "Serial");
}

QString Cfg::getSerialBr(const QString &com)
{
    QString key = QString("BR_%1").arg(com);
    return mCfg->read(key, "", "Serial").toString();
}

void Cfg::setSerialBr(const QString &com, const QString &br)
{
    QString key = QString("BR_%1").arg(com);
    mCfg->write(key, br, "Serial");
}


/**
 * @brief 根据名称获取配置文件数值
 * @return 对应的配置文件数值
 */
QVariant Cfg::read(const QString &key, const QVariant &v, const QString &g)
{
    return mCfg->read(key, v, g);
}

/**
 * @brief 设置对应名称的配置文件数值
 * @param value
 * @param name
 */
void Cfg::write(const QString &key, const QVariant& v, const QString &g)
{
    mCfg->write(key, v, g);
}

/**
 * @brief 获取当前用户名称
 * @return 用户名
 */
QString Cfg::getLoginName()
{
    return mCfg->read("name", "admin", "Login").toString();
}

/**
 * @brief 设置当前用户名
 * @param name
 */
void Cfg::setLoginName(const QString &name)
{
    mCfg->write("name", name, "Login");
}


void Cfg::setDate()
{
    QString value = QDate::currentDate().toString("yyyy-MM-dd");
    write("date", value, "Date");
}

bool Cfg::getDate()
{
    bool ret = false;
    QString str = read("date","","Date").toString();
    if(!str.isEmpty()) {
        QDate date = QDate::fromString(str, "yyyy-MM-dd");
        if(QDate::currentDate() > date) ret = true;
    }

    return ret;
}

void Cfg::setCurrentNum()
{
    setDate();
    write("num", item->currentNum, "Date");
}

void Cfg::initCurrentNum()
{
    bool ret = getDate();
    if(ret) {
        item->currentNum = 0;
        setCurrentNum();
    } else {
        int value = read("num", 0,"Date").toInt();
        item->currentNum = value;
    }
}
