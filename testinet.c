
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char const* argv[])
{
    int valid=0;
    struct sockaddr_in in_addr;
    char tmp[100] = "112.215.26.254";
    if(inet_aton(tmp, &in_addr)!=0)
    {
        valid = 0x0003;
    }
    printf("%d\n",valid);
    printf("%X\n",in_addr);

    return 0;
}
