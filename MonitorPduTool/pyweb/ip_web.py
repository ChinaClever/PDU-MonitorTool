from selenium import webdriver
from selenium.webdriver.support.select import Select
import configparser
import time
import os

class IpWeb:

    def __init__(self):
        self.ip_prefix = "http://"
        self.initCfg()
        self.initDriver()

    def initDriver(self):
        try:
            self.driver = webdriver.Firefox(executable_path="geckodriver.exe")
        except ValueError:
            self.driver = webdriver.Chrome(executable_path="chromedriver.exe")

    @staticmethod
    def getCfg():
        cf = configparser.ConfigParser()
        fn = os.path.expanduser('~') + "/.MonitorPduTool/cfg.ini"
        cf.read(fn, 'utf-8-sig')  # 读取配置文件，如果写文件的绝对路径，就可以不用os模块
        return cf

    def initCfg(self):
        items = IpWeb.getCfg().items("Cfg")  # 获取section名为Mysql-Database所对应的全部键值对
        self.cfgs = {'ip_version':1, 'ip_addr': '192.168.1.163', 'log_en':0}
        for it in items:
            self.cfgs[it[0]] = it[1]

    def login(self):
        ip =  self.ip_prefix +self.cfgs['ip_addr']+'/'
        user = 'admin'
        pwd = 'admin'
        self.driver.get(ip)
        self.setItById("name", user)
        self.setItById("psd", pwd)
        self.execJs("login()")
        time.sleep(1)
        
    def setEle(self):
        self.divClick(3)
        jsSheet = " claerset = createXmlRequest();claerset.onreadystatechange = clearrec;ajaxget(claerset, \"/energyzero?a=\" + {0}+\"&\");"        
        for num in range(0, 4):
            self.execJs(jsSheet.format(num))

    def setSelect(self, id, v):
        it = self.driver.find_element_by_id(id)
        Select(it).select_by_index(v)
        time.sleep(1)

    def setItById(self, id, v):
        it = self.driver.find_element_by_id(id)
        it.clear()
        it.send_keys(str(v))
        time.sleep(1)

    def btnClick(self, id):
        self.driver.find_element_by_id(id).click()
        time.sleep(1)

    def alertClick(self, id):
        self.btnClick(id)
        self.driver.switch_to.alert.accept()
        time.sleep(1)

    def divClick(self, id):
        self.driver.switch_to.default_content()
        self.execJs("clk({0})".format(id))
        self.driver.switch_to.frame('ifrm')

    def execJs(self, js):
        self.driver.execute_script(js)
        time.sleep(1)

    def execJsAlert(self, js):
        self.execJs(js)
        self.driver.switch_to.alert.accept()
        time.sleep(1)
        
    def resetFactory(self):
        v = self.cfgs['ip_version']
        aj = 'ajaxget'
        if(3 == int(v)):
            aj += 's'
            self.divClick(10)
        else:
            self.divClick(8)
        self.setSelect("order",1)
        jsSheet = "xmlset = createXmlRequest();xmlset.onreadystatechange = setdata;{0}(xmlset, \"/setsys?a=1\" + \"&\");"
        self.execJs(jsSheet.format(aj))
        time.sleep(1)





