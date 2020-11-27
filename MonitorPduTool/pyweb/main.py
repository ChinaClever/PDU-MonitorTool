from pyweb.ip_v1 import  *
from pyweb.ip_v3 import  *



if __name__ == '__main__':
    v = IpWeb.getCfg().get("Cfg", "ip_version")

    if(3 == int(v)):
        app = IpV3()
        app.start_fun()
    else:
        app = IpV1()
        app.start_fun()

