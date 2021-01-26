/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   inter.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: exam <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 13:02:44 by exam          #+#    #+#                 */
/*   Updated: 2020/01/07 13:17:04 by exam          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	inter2(char c, char *str2)
{
	int i;

	i = 0;
	while (str2[i])
	{
		if (str2[i] == c)
		{
			write(1, &c, 1);
			return ;
		}
		i++;
	}
}

void	inter(char *str, char *str2)
{
	int i;
	int j;

	i = 1;
	if (str[0] == 0)
		return ;
	inter2(str[0], str2);
	while (str[i])
	{
		j = i;
		while (j > 0)
		{
			j--;
			if (str[i] == str[j])
				break ;
		}
		if (str[i] != str[j])
			inter2(str[i], str2);
		i++;
	}
}

int		main(int argc, char **argv)
{
	if (argc != 3)
	{
		write(1, "\n", 1);
		return (0);
	}
	inter(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}
