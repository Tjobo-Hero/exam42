/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: exam <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 13:19:38 by exam          #+#    #+#                 */
/*   Updated: 2020/01/07 14:50:33 by exam          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

typedef struct		s_flags
{
	int width;
	int dot;
	int pres;
	int co;
	va_list arg;
}					t_flags;

void	init(t_flags *f)
{
	f->width =  0;
	f->dot = 0;
	f->pres = 0;
}

void	ft_putchar(char c, t_flags *f)
{
	write(1, &c, 1);
	f->co = f->co + 1;
}

void	ft_putnbr(long num, t_flags *f)
{
	if (num > 9)
	{
		ft_putnbr((num / 10), f);
		ft_putnbr((num % 10), f);
		return ;
	}
	ft_putchar((num + 48), f);
}

void	ft_putnbr_hex(unsigned long num, t_flags *f)
{
	int i;

	i = 0;
	if (num > 15)
	{
		ft_putnbr_hex((num / 16), f);
		ft_putnbr_hex((num % 16), f);
		return ;
	}
	if (num > 9)
	{
		while (num > 10)
		{
			i++;
			num--;
		}
		ft_putchar(('a' + i), f);
		return ;
	}
	ft_putchar((num + 48), f);
}

void	hex(t_flags *f)
{
	unsigned long num;
	unsigned long savenum;
	int i;

	num = va_arg(f->arg, unsigned int);
	i = 0;
	savenum = num;
	while (savenum >= 1)
	{
		savenum = savenum / 16;
		i++;
	}
	while (f->width > i && f->width > f->pres)
	{
		ft_putchar(' ', f);
		f->width--;
	}
	while (f->pres > i)
	{
		ft_putchar('0', f);
		f->pres--;
	}
	if (f->pres == 0 && f->dot == 1 && num == 0)
		return ;
	ft_putnbr_hex(num, f);
}

void	digit(t_flags *f)
{
	long num;
	long savenum;
	int i;
	int min;

	min = 0;
	num = va_arg(f->arg, int);
	i = 0;
	if (num < 0)
	{
		f->width--;
		num = num * -1;
		min = 1;
	}
	savenum = num;
	while (savenum >= 1)
	{
		savenum = savenum / 10;
		i++;
	}
	while (f->width > i && f->width > f->pres)
	{
		ft_putchar(' ', f);
		f->width--;
	}
	if (min == 1)
		ft_putchar('-', f);
	while (f->pres > i)
	{
		ft_putchar('0', f);
		f->pres--;
	}
	if (f->pres == 0 && f->dot == 1 && num == 0)
		return ;
	ft_putnbr(num, f);
}

void	string(t_flags *f)
{
	char *str;
	int i;
	int j;

	i = 0;
	j = 0;
	str = va_arg(f->arg, char *);
	if (!str)
		str = "(null)";
	while (str[i])
		i++;
	if (f->pres < i && f->dot == 1)
		i = f->pres;
	while (f->width > i)
	{
		ft_putchar(' ', f);
		f->width--;
	}
	while (i > 0)
	{
		ft_putchar(str[j], f);
		j++;
		i--;
	}
}

void	found_perc(const char **s, t_flags *f)
{
	while (**s >= '0' && **s <= '9')
	{
		f->width = f->width * 10 + **s - 48;
		(*s)++;
	}
	if (**s == '.')
	{
		f->dot = 1;
		(*s)++;
		while (**s >= '0' && **s <= '9')
		{
			f->pres = f->pres * 10 + **s - 48;
			(*s)++;
		}
	}
	if (**s == 'd')
		digit(f);
	if (**s == 'x')
		hex(f);
	if (**s == 's')
		string(f);
	if (**s != 0)
		(*s)++;
}

int		ft_printf(const char *s, ... )
{
	t_flags f;

	f.co = 0;
	va_start(f.arg, s);
	while (*s)
	{
		if (*s == '%')
		{
			init(&f);
			s++;
			found_perc(&s, &f);
		}
		else
		{
			ft_putchar(*s, &f);
			s++;
		}
	}
	va_end(f.arg);
	return (f.co);
}
