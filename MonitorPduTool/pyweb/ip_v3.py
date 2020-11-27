from pyweb.ip_web import  *

class IpV3(IpWeb):

    def start_fun(self):
        self.ip_prefix = 'https://'
        self.login()
        self.setEle()
        self.clearLogs()
        self.resetFactory()
        self.driver.close()

    def setTime(self):
        self.divClick(8)
        self.execJsAlert("check_time()")

    def clearLogs(self):
        en = self.cfgs['log_en']
        if(int(en) < 1):
            return
        self.setTime()
        self.divClick(9)
        jsSheet = "xmlset = createXmlRequest();xmlset.onreadystatechange = setdata;ajaxgets(xmlset, \"/setlclear?a=\" + {0} + \"&\");"
        for num in range(0, 2):
            self.setSelect("loglist", num)
            self.execJs(jsSheet.format(num))
            time.sleep(1)

    