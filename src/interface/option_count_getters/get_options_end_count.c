/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options_end_count.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:27:44 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/05 16:55:34 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

int	get_options_end_count(int argc, char **argv)
{
	int	option_count;
	int	options_end_count;

	option_count = 0;
	while (1 + option_count < argc
		&& ft_strstarts(argv[1 + option_count], "-")
		&& !(!ft_strcmp(argv[1 + option_count], "-")
			|| !ft_strcmp(argv[1 + option_count], "--")))
		option_count++;
	options_end_count = 0;
	if (1 + option_count + options_end_count < argc
		&& (!ft_strcmp(argv[1 + option_count + options_end_count], "-")
			|| !ft_strcmp(argv[1 + option_count + options_end_count], "--")))
		options_end_count++;
	return (options_end_count);
}
