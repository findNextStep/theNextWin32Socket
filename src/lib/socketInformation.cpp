#include "socketInformation.h"
#include "socketBase.h"
#include <stdlib.h>
#include <stdio.h>
#include <Nb30.h>
#include <iostream>
using namespace std;
namespace theNextSocket {
BOOL GetHostIP(char * inData) {
    char name[255];
    int re;
    (re = gethostname ( name, sizeof(name)));
    if (re == SOCKET_ERROR) {
        return false;
    }
    hostent* pHostent = gethostbyname(name);
    hostent& he = *pHostent;
    sockaddr_in sa;
    for (int nAdapter=0; he.h_addr_list[nAdapter]; nAdapter++) {
        memcpy ( &sa.sin_addr.s_addr, he.h_addr_list[nAdapter],he.h_length);
        strcpy(inData,inet_ntoa(*(struct in_addr *)he.h_addr_list[nAdapter]));
    }
    return TRUE;
} std::string getIP() {
    WSAManager manage;
    char ip[30];
    if (!GetHostIP(ip)) {
        return "false";
    }
    std::string re;
    for (int i=0; ip[i]!='\0'; ++i) {
        re.push_back(ip[i]);
    }
    return re;
} typedef struct _ASTAT_ {
    ADAPTER_STATUS adapt;
    NAME_BUFFER NameBuff [30];
} ASTAT, *PASTAT;
void _getMac(char * mac) {
    ASTAT Adapter;
    NCB Ncb;
    UCHAR uRetCode;
    LANA_ENUM lenum;
    int i = 0;
    memset(&Ncb, 0, sizeof(Ncb));
    Ncb.ncb_command = NCBENUM;
    Ncb.ncb_buffer = (UCHAR *)&lenum;
    Ncb.ncb_length = sizeof(lenum);
    uRetCode = Netbios( &Ncb );
    for(i=0; i < lenum.length ; i++) {
        memset(&Ncb, 0, sizeof(Ncb));
        Ncb.ncb_command = NCBRESET;
        Ncb.ncb_lana_num = lenum.lana[i];
        uRetCode = Netbios( &Ncb );
        memset(&Ncb, 0, sizeof(Ncb));
        Ncb.ncb_command = NCBASTAT;
        Ncb.ncb_lana_num = lenum.lana[i];
        strcpy((char *)Ncb.ncb_callname, "* ");
        Ncb.ncb_buffer = (unsigned char *) &Adapter;
        Ncb.ncb_length = sizeof(Adapter);
        uRetCode = Netbios( &Ncb );
        if (uRetCode == 0) {
            sprintf(mac, "%02X%02X%02X%02X%02X%02X ",
                    Adapter.adapt.adapter_address[0],
                    Adapter.adapt.adapter_address[1],
                    Adapter.adapt.adapter_address[2],
                    Adapter.adapt.adapter_address[3],
                    Adapter.adapt.adapter_address[4],
                    Adapter.adapt.adapter_address[5]
                   );
        }
    }
} std::string getMAC() {
    char mac[30];
    _getMac(mac);
    std::string re;
    for (int i=0; mac[i]!='\0'; ++i) {
        re.push_back(mac[i]);
    }
    return re;
}
}