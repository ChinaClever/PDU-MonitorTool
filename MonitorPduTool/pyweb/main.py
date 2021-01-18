from monitor_ip.ip_v1 import  *
from monitor_ip.ip_v3 import  *
from monitor_ip.ip_web import  *


if __name__ == '__main__':
    v = IpWeb.getCfg().get("ipCfg", "version")

    if(int(v)>1):
        app = IpV3()
        app.start_fun()
    else:
        app = IpV1()
        app.start_fun()

