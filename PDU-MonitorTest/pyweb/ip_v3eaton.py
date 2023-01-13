from monitor_ip.ip_web import  *

class IpV3EATON(IpWeb):

    def start_fun(self):
        self.login()
        self.setEle()
        self.checkCorrect()
        self.resetToFactory()
        self.driver.quit()

    def checkCorrect(self):
        cfg = self.cfgs
        ip =  self.ip_prefix + cfg['ip_addr'] + '/correct.html'
        self.driver.get(ip); time.sleep(1.1)
        self.driver.switch_to.default_content()
        self.itemCheck("language", int(cfg['language']), '语言选择')
        self.itemCheck("lcdled", cfg['lines'], '相数选择')
        self.itemCheck("modbus", cfg['modbus'], '设备模式')
        self.itemCheck("LCDswitch", cfg['lcd_switch'], '新旧屏')
        self.itemCheck("standard", cfg['standard'], '标准中性')
        self.itemCheck("Log_flag", cfg['log_en'], '日志功能')
        self.macAddrCheck()
        self.itemCheck("IN", cfg['ip_infirst'], '输入ex')
        self.itemCheck("IN1", cfg['ip_insecond'], '输入ea')
        self.itemCheck("OUT1", cfg['ip_outfirst'], '输出ex')
        self.itemCheck("OUT2", cfg['ip_outsecond'], '输出ea')
        self.driver.back(); time.sleep(1)
        
    def resetToFactory(self):
        self.divClick(10)
        self.setSelect("order",1)
        self.execJsAlert("setdevice();")
        self.sendtoMainapp("设备Web出厂设置成功", 1)
        time.sleep(0.5)
