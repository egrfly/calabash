/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_more_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:46:48 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/10 22:47:03 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	has_more_options(int argc, int c_option_count,
			int options_end_count)
{
	return (1 + c_option_count + options_end_count < argc);
}
