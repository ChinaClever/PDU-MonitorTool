from pyweb.ip_web import  *

class IpV1(IpWeb):

    def start_fun(self):
        self.login()
        self.setEle()
        self.resetFactory()
        self.driver.close()
    








