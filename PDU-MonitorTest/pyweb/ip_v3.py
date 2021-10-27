from monitor_ip.ip_web import  *

class IpV3(IpWeb):

    def start_fun(self):
        #self.ip_prefix = 'https://'
        self.login()
        self.setEle()
        self.checkCorrect()
        self.clearLogs()
        self.resetFactory()
        self.driver.quit()

    def setTime(self):
        self.divClick(8)
        self.execJsAlert("check_time()")

    def timeCheck(self):
        self.divClick(8); time.sleep(0.25)
        loctime = self.driver.find_element_by_id('loctime').text
        devtime = self.driver.find_element_by_id('devtime1').text
        if str(devtime[0:15]) in str(loctime):
            msg = '设备时间正常，设备时间{0}'.format(devtime)
            self.sendtoMainapp(msg, 1)
        else:
            msg = '设备时间错误，本地时间{0}，设备时间{1}'.format(loctime, devtime)
            self.sendtoMainapp(msg, 0)

    def clearLogs(self):
        en = self.cfgs['log_en']
        if(int(en) < 1):
            return
        self.timeCheck()
        self.divClick(9)
        jsSheet = "xmlset = createXmlRequest();xmlset.onreadystatechange = setdata;ajaxgets(xmlset, \"/setlclear?a=\" + {0} + \"&\");"
        for num in range(0, 2):
            self.setSelect("loglist", num)
            self.execJs(jsSheet.format(num))
            time.sleep(0.2)
        self.sendtoMainapp('清除日志', 1)

    def checkCorrect(self):
        cfg = self.cfgs
        security = int(self.cfgs['security'])
        ip =  self.ip_prefix + cfg['ip_addr'] + '/correct.html'
        self.driver.get(ip); time.sleep(1.1)
        if(security): time.sleep(1.2)
        self.driver.switch_to.default_content()
        self.itemCheck("language", int(cfg['language']), '语言选择')
        self.itemCheck("modbus", cfg['modbus'], '模式选择')
        self.itemCheck("lcdled", cfg['lines'], '相数选择')
        self.itemCheck("ACDC", cfg['ac'], '交直流选择')
        self.itemCheck("standard", cfg['standard'], '中性/标准选择')
        self.itemCheck("Log_flag", cfg['log_en'], '日志功能设置')
        self.macAddrCheck()
        self.driver.back(); time.sleep(1)
        if(security):time.sleep(1.3)
