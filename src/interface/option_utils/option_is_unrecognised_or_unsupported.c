/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_is_unrecognised_or_unsupported.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:48:10 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/10 22:48:36 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_string.h"

bool	option_is_unrecognised_or_unsupported(int argc, char **argv,
			int c_option_count)
{
	return (c_option_count + 1 < argc
		&& ft_strcmp(argv[1 + c_option_count], "-")
		&& ft_strcmp(argv[1 + c_option_count], "--")
		&& ft_strstarts(argv[1 + c_option_count], "-"));
}
