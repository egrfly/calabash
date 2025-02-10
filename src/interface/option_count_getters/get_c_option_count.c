/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_c_option_count.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:27:21 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/10 22:27:30 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

int	get_c_option_count(int argc, char **argv)
{
	int	c_option_count;

	c_option_count = 0;
	while (1 + c_option_count < argc
		&& !ft_strcmp(argv[1 + c_option_count], "-c"))
		c_option_count++;
	return (c_option_count);
}
