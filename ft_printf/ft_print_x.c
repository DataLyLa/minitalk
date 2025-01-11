/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylaurol <lylaurol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:34:14 by lylaurol          #+#    #+#             */
/*   Updated: 2024/07/30 03:35:05 by lylaurol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "printf.h"

int	ft_print_x(unsigned int value, t_type type)
{
	unsigned int	num;
	int				minus;

	minus = 0;
	num = ft_absolute(value, &minus);
	if (type == TYPE_LX)
		return (ft_putn_ui(num, BASE16, LHS_16));
	return (ft_putn_ui(num, BASE16, UHS_16));
}