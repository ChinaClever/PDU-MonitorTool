from monitor_ip.ip_web import  *

class IpV1HUADA(IpWeb):

    def start_fun(self):
        self.login()
        self.setEle()
        self.checkCorrect()
        self.resetFactory()
        self.driver.quit()

    def checkCorrect(self):
        cfg = self.cfgs
        security = int(self.cfgs['security'])
        ip =  self.ip_prefix + cfg['ip_addr'] + '/correct.html'
        self.driver.get(ip); time.sleep(1.1)
        self.driver.switch_to.default_content()
        self.itemCheck("language", int(cfg['language']), '语言选择')
        self.itemCheck("modbus", cfg['modbus'], '模式选择')
        self.itemCheck("lcdled", cfg['lines'], '相数选择')
        self.itemCheck("LCDswtich", 1, '新旧屏')
        self.itemCheck("Code_flag", security, '液晶屏/段码屏')
        self.itemCheck("CodePrecision", int(self.cfgs['log_en']), '段码屏精度')
        self.itemCheck("ACDC", cfg['ac'], '交直流选择')
        self.macAddrCheck()
        self.driver.back(); time.sleep(1)

    #def setCorrect(self):
        #cfg = self.cfgs
        #security = int(self.cfgs['security'])
        #ip =  self.ip_prefix + cfg['ip'] + '/correct.html'
        #self.driver.get(ip); time.sleep(1.2)
        #self.driver.switch_to.default_content()
        #self.setItById("language", int(cfg['ip_language']), '设备语言')
        #self.setItById("modbus", cfg['ip_modbus'], '设备模式')
        #self.setItById("lcdled", cfg['ip_lines'], '设备相数')
        
        #self.setItById("LCDswtich", 1, '新旧屏')
        #self.setItById("Code_flag", security, '液晶屏/段码屏')
        #self.setItById("CodePrecision", int(self.cfgs['log_en']), '段码屏精度')
        #self.setItById("ACDC", cfg['ip_ac'], '交直流')
        #self.setMacAddr()
        #self.alertClick("Button3")
        #self.sendtoMainapp("设备后台网页配置成功", 1)
        #self.driver.back(); time.sleep(1)
    








