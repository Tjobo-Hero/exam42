

#include <unistd.h>

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void   check_other(char c, char *str1)
{
    int i;

    i = 0;
    while (str1[i] != '\0')
    {
        if (c == str1[i])
            return ;
        i++;
    }
    ft_putchar(c);
}

void   check_str2(char *str1, char *str2)
{
    int i;
    int j;

    i = 0;
    while (str2[i] != '\0')
    {
        j = i;
        if (i == 0)
            check_other(str2[i], str1);
        while (j > 0)
        {
            j--;
            if (str2[i] == str2[j])
                break ;
        }
        if (str2[i] != str2[j])
            check_other(str2[i], str1);
        i++;
    }
}

void   ft_union(char *str1, char *str2)
{
    int i;
    int j;

    i = 0;
    while (str1[i] != '\0')
    {
        j = i;
        if (i == 0)
            ft_putchar(str1[i]);
        while (j > 0)
        {
            j--;
            if (str1[i] == str1[j])
                break ;
        }
        if (str1[i] != str1[j])
            ft_putchar(str1[i]);
        i++;
    }
    check_str2(str1, str2);
}

int     main(int argc, char **argv)
{
    if (argc != 3)
    {
        write(1, "\n", 1);
        return (0);
    }
    ft_union(argv[1], argv[2]);
    write(1, "\n", 1);
    return (0);
}