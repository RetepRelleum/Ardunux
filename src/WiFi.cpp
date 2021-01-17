#include <WiFi.h>
#include<stdio.h>	//printf
#include<string.h>	//memset
#include<errno.h>	//errno
#include<sys/socket.h>
#include<netdb.h>
#include<ifaddrs.h>
#include<stdlib.h>
#include<unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>

WiFiClass WiFi;

byte WiFiClass::scanNetworks()
{
    return 0;
}

String WiFiClass::SSID(byte wifiAccessPoint)
{
    return String("test");
}

long WiFiClass::RSSI(byte wifiAccessPoint)
{
    return 4;
}

byte WiFiClass::encryptionType(byte wifiAccessPoint)
{
    return WIFI_AUTH_OPEN;
}

byte WiFiClass::begin(String ssid, String pass)
{
    return 0;
}

String WiFiClass::BSSIDstr(byte wifiAccessPoint)
{
    String ret=String("BSSIDstr");
    return ret;

}

IPAddress WiFiClass::localIP()
{
    FILE *f;
    char line[100], *p, *c;

    f = fopen("/proc/net/route", "r");

    while(fgets(line, 100, f))
    {
        p = strtok(line, " \t");
        c = strtok(NULL, " \t");

        if(p!=NULL && c!=NULL)
        {
            if(strcmp(c, "00000000") == 0)
            {
                //		printf("Default interface is : %s \n" , p);
                break;
            }
        }
    }

    //which family do we require , AF_INET or AF_INET6
    int fm = AF_INET;
    struct ifaddrs *ifaddr, *ifa;
    int family, s;
    char host[NI_MAXHOST];

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    //Walk through linked list, maintaining head pointer so we can free list later
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == NULL)
        {
            continue;
        }
        family = ifa->ifa_addr->sa_family;

        if(strcmp( ifa->ifa_name, p) == 0)
        {
            if (family == fm)
            {
                s = getnameinfo( ifa->ifa_addr, (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

                if (s != 0)
                {
                    printf("getnameinfo() failed: %s\n", gai_strerror(s));
                    exit(EXIT_FAILURE);
                }

                //	printf("address: %s", host);
            }
            //	printf("\n");
        }
    }
    freeifaddrs(ifaddr);
    IPAddress ret;
    ret.fromString(host);
    return ret;
}

IPAddress WiFiClass::gatewayIP()
{
    String ip=localIP().toString();
    String re=ip.substring(0,ip.lastIndexOf(".")+1)+"1";
    IPAddress ret;
    ret.fromString(re);
    return ret;
}

byte WiFiClass::status()
{
    return WL_CONNECTED;
}

String WiFiClass::macAddress()
{
    struct ifreq ifr;
    int s;
    if ((s = socket(AF_INET, SOCK_STREAM,0)) < 0)
    {
        perror("socket");
    }
    strcpy(ifr.ifr_name,  "eth0");
    if (ioctl(s, SIOCGIFHWADDR, &ifr) < 0)
    {
        perror("ioctl");
    }
     char *hwaddr = ( char *)ifr.ifr_hwaddr.sa_data;


    String ret= String(hwaddr[0],HEX)+":";
    ret+=String(hwaddr[1],HEX)+":";
    ret+=String(hwaddr[2],HEX)+":";
    ret+=String(hwaddr[3],HEX)+":";
    ret+=String(hwaddr[4],HEX)+":";
    ret+=String(hwaddr[5],HEX);
    return ret;
}


