#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

void    parseError(const char *error)
{
    write(STDERR_FILENO, error, strlen(error));
    exit(1);
}

int     main(int ac, char **av)
{
    if (ac != 2)
        parseError("Wrong number of arguments\n");
    return 0;
}