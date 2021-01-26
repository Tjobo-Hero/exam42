
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

typedef struct s_list
{
	int width;
	int precision;
	int has_precision;
	int is_neg;
	int count;
	int len;
	va_list ap;
}		t_list;

void clear_struct(t_list *data)
{
	data->width = 0;
	data->precision = 0;
	data->has_precision = 0;
	data->is_neg = 0;
	data->len = 0;
}
void ft_putchar(char c, t_list *data)
{
	write(1, &c, 1);
	data->count += 1;
}
void print_s(char *str, t_list *data)
{
	int i;


	if (str == NULL)
		str = "(null)";
	i = 0;
	while(str[i] != '\0')
		i++;
	data->len = i;
	i = 0;
	if (data->has_precision && data->precision < data->len)
		data->len = data->precision;
	while (data->width > data->len)
	{
		ft_putchar(' ', data);
		data->width--;
	}
	while (data->len > 0)
	{
		ft_putchar(str[i], data);
		i++;
		data->len--;
	}
	
}

void ft_putnbr(long n, t_list *data)
{
	if (n >= 10)
	{
		ft_putnbr(n / 10, data);
		ft_putnbr(n % 10, data);
	}
	else 
		ft_putchar(n + 48, data);

}
void print_d(long n, t_list *data)
{
	long ncopy;

	if (n < 0)
	{
		n = n * -1;
		data->is_neg = 1;
		data->width--;
	}
	ncopy = n;
	while (ncopy > 0)
	{
		ncopy = ncopy / 10;
		data->len++;
	}
	if (n == 0)
		data->len = 1;
	if (data->has_precision && data->precision > data->len)
		data->width = data->width - (data->precision - data->len);
	while (data->width > data->len)
	{
		ft_putchar(' ', data);
		data->width--;
	}
	if (data->is_neg && data->precision >= data->len)
		ft_putchar('-', data);
	while (data->precision > data->len)
	{
		ft_putchar('0', data);
		data->precision--;
	}
	if (data->is_neg && data->precision < data->len)
		ft_putchar('-', data);
	if (data->has_precision && data->precision == 0 && n == 0)
	{
		if (data->width > 0)
			ft_putchar(' ', data);
		return ;
	}
	ft_putnbr(n, data);
}

void ft_puthex(long n, t_list *data)
{
	int i;

	i = 0;
	if (n >= 16)
	{
		ft_puthex(n / 16, data);
		ft_puthex(n % 16, data);
	}
	else if (n > 9)
	{
		while (n > 9)
		{
			n--;
			i++;
		}
		ft_putchar(96 + i, data);
	}
	else
		ft_putchar(n + 48, data);
	
}

void print_x(long n, t_list *data)
{
	long ncopy;

	ncopy = n;
	while (ncopy > 0)
	{
		ncopy = ncopy / 16;
		data->len++;
	}
	if (n == 0)
		data->len = 1;
	if (data->has_precision && data->precision > data->len)
		data->width = data->width - (data->precision - data->len);
	while (data->width > data->len)
	{
		ft_putchar(' ', data);
		data->width--;
	}
	while (data->precision > data->len)
	{
		ft_putchar('0', data);
		data->precision--;
	}
	if (data->has_precision && data->precision == 0 && n == 0)
	{
		if (data->width > 0)
			ft_putchar(' ', data);
		return ;
	}
	ft_puthex(n, data);

}

void look_for_width_and_flags(const char **str, t_list *data)
{
	while (**str >= '0' && **str <= '9')
	{
		data->width = data->width * 10 + (**str - 48);
		(*str)++;
	}
	if (**str == '.')
	{
		data->has_precision = 1;
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			data->precision = data->precision * 10 + (**str - 48);
			(*str)++;
		}
	}
	if (**str == 's')
		print_s(va_arg(data->ap, char*), data);
	if (**str == 'd')
		print_d(va_arg(data->ap, int), data);
	if (**str == 'x')
		print_x(va_arg(data->ap, unsigned int), data);
	(*str)++;

}

int ft_printf(const char *str, ...)
{
	t_list data;

	data.count = 0;
	va_start(data.ap, str);
	while (*str != '\0')
	{
		if (*str == '%')
		{
			str++;
			clear_struct(&data);
			look_for_width_and_flags(&str, &data);
		}
		if (*str != '%' && *str != '\0')
		{
			ft_putchar(str[0], &data);
			str++;
		}
	}
	va_end(data.ap);
	return (data.count);
}