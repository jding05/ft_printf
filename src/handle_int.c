/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sding <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 22:52:58 by sding             #+#    #+#             */
/*   Updated: 2018/04/28 16:22:15 by sding            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

intmax_t	get_int_type_by_length(va_list ap, t_arg *arg)
{
	intmax_t	nb;

	nb = va_arg(ap, intmax_t);
	if (arg->length == h && arg->conversion != 'D')
		nb = (short int)nb;
	else if (arg->length == l || arg->conversion == 'D')
		nb = (long int)nb;
	else if (arg->length == hh)
		nb = (signed char)nb;
	else if (arg->length == ll)
		nb = (long long int)nb;
	else if (arg->length == j)
		nb = (intmax_t)nb;
	else if (arg->length == z)
		nb = (size_t)nb;
	else
		nb = (int)nb;
	return (nb);
}

/*
** for type d and type i
** flag_hash: has no effect for d, i
** flag_zero: padded on the left with 0, has no effect if there is a precision
** flag_minus: do left adjusted, override flag_zero if both exist
** flag_space: padd one space before pos nb, not neg nb
** flag_plus: add signed
** precision_nb < 0: like flag_minus
** precision: give min number of digits to appear for d, i
** field_width pad space, precision_nb pad 0
** if there is a percision, flag_zero = 0;
*/

int			handle_int(va_list ap, t_arg *arg)
{
	intmax_t	nb;
	int			arg_len;

	if (arg->precision || arg->flag_minus)
		arg->flag_zero = 0;
	nb = get_int_type_by_length(ap, arg);
	if (nb < 0)
	{
		nb = -nb;
		arg->neg_arg_int = 1;
	}
	arg_len = ft_nbrlen(nb);
	arg->print_count += arg_len;
	if (arg->flag_minus == 0 && arg->flag_zero == 0)
		int_output1(nb, arg, arg_len);
	else if (arg->flag_minus == 1)
		int_output2(nb, arg, arg_len);
	else if (arg->flag_zero == 1)
		int_output3(nb, arg, arg_len);
	return (arg->print_count);
}

/*
** when there is both field width and precison nb
*/

void		int_output1(intmax_t nb, t_arg *arg, int arg_len)
{
	intmax_t	pad_space_nb;
	intmax_t	pad_zero_nb;

	pad_space_nb = MAX(arg->width_nb - arg_len, 0);
	pad_zero_nb = MAX(arg->precision_nb - arg_len, 0);
	if (pad_space_nb > 0 || pad_zero_nb > 0)
	{
		if (pad_zero_nb >= pad_space_nb)
		{
			print_int_sign(arg);
			print_padded_char(pad_zero_nb, arg, '0');
		}
		if (pad_zero_nb < pad_space_nb)
		{
			if (arg->flag_plus || arg->flag_space || arg->neg_arg_int)
				print_padded_char(pad_space_nb - pad_zero_nb - 1, arg, ' ');
			else
				print_padded_char(pad_space_nb - pad_zero_nb, arg, ' ');
			print_int_sign(arg);
			print_padded_char(pad_zero_nb, arg, '0');
		}
	}
	else if (pad_space_nb <= 0 && pad_zero_nb <= 0)
		print_int_sign(arg);
	ft_putnbr_intmax_t(nb);
}

void		int_output2(intmax_t nb, t_arg *arg, int arg_len)
{
	intmax_t	pad_space_nb;
	intmax_t	pad_zero_nb;

	if (arg->flag_plus || arg->flag_space || arg->neg_arg_int)
		pad_space_nb = MAX(arg->width_nb - arg_len - 1, 0);
	else
		pad_space_nb = MAX(arg->width_nb - arg_len, 0);
	pad_zero_nb = MAX(arg->width_nb - arg_len, 0);
	print_int_sign(arg);
	print_padded_char(pad_zero_nb - pad_space_nb, arg, '0');
	ft_putnbr_intmax_t(nb);
	print_padded_char(pad_space_nb, arg, ' ');
}

/*
** flag_zero == 1, presicion doesn't work
*/

void		int_output3(intmax_t nb, t_arg *arg, int arg_len)
{
	intmax_t	pad_zero_nb;

	if (arg->neg_arg_int)
	{
		pad_zero_nb = MAX(arg->width_nb - arg_len - 1, 0);
		print_int_sign(arg);
	}
	else
		pad_zero_nb = MAX(arg->width_nb - arg_len, 0);
	print_padded_char(pad_zero_nb, arg, '0');
	ft_putnbr_intmax_t(nb);
}
