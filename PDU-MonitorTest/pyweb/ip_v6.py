from monitor_ip.ip_web import  *

class IpV6(IpWeb):

    def start_fun(self):
        self.login()
        self.checkCorrect()
        self.setEle()
        if(int(self.cfgs['version'])==6):
            self.divClick(2)
            self.checkIpv6Threshold()
        self.resetIpv6Factory()
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
        self.itemCheck("language", int(cfg['language'])+1, '语言选择')
        self.macAddrCheck()
        time.sleep(1)
        if(int(self.cfgs['version'])==7):
            self.btnClick("Button2")
            self.driver.switch_to.frame('ifrm')
            self.checkIpv6Threshold()
            self.driver.back(); time.sleep(1)
        self.driver.back(); time.sleep(1)
        if(security):time.sleep(1.3)
        
    def resetIpv6Factory(self):
        self.divClick(8)
        self.setSelect("order",1)
        self.execJsAlert("setdevice();")
        self.sendtoMainapp("设备Web出厂设置成功", 1)
        time.sleep(0.5)
