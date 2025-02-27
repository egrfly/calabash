/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_more_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:46:48 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 19:01:07 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	has_more_arguments(int argc, int option_count)
{
	return (1 + option_count < argc);
}
