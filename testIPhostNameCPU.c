#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int get_hostinfo(char* name, char* ip, char* id) {
    struct hostent *hp = NULL;
    char szName[255] = {0};
    char *szIP = NULL;
    if(gethostname(szName, sizeof(szName)) == -1) {
        return -1;
    }
    int sfd, intr;
    struct ifreq buf[16];
    struct ifconf ifc;
    sfd = socket (AF_INET, SOCK_DGRAM, 0);
    if (sfd < 0) {
        return -2;
    }
    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = (caddr_t)buf;
    if (ioctl(sfd, SIOCGIFCONF, (char *)&ifc)) {
        return -3;
    }
    intr = ifc.ifc_len / sizeof(struct ifreq);
    while (intr-- > 0 && ioctl(sfd, SIOCGIFADDR, (char *)&buf[intr]));
    close(sfd);
    szIP = inet_ntoa(((struct sockaddr_in*)(&buf[intr].ifr_addr))-> sin_addr);
    strcpy(name, szName);
    strcpy(ip, szIP);
    sprintf(id, "%08x", gethostid());
    return 0;
}

int get_cpucount() {
    return (int)sysconf(_SC_NPROCESSORS_ONLN);
}

int main(int argc, char const* argv[])
{
    char host_name[128];
    char host_ip[128];
    char host_id[128];
    char expiration[128];
    memset(host_name, 0 ,sizeof(host_name));
    memset(host_ip, 0 ,sizeof(host_ip));
    memset(host_id, 0 ,sizeof(host_id));
    memset(expiration, 0 ,sizeof(expiration));
    int hostret = get_hostinfo(host_name, host_ip, host_id);
    int cpu_num = get_cpucount();

    printf("%d\n",hostret);
    printf("%s\n",host_name);
    printf("%s\n",host_ip);
    printf("%s\n",host_id);
    printf("%d\n",cpu_num);

    return 0;
}
