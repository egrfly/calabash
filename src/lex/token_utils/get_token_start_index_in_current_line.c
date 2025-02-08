/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_start_index_in_current_line.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 00:34:27 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/06 00:36:12 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_token_start_index_in_current_line(
		int current_line_index,
		int start_line_index,
		int start_index_in_start_line)
{
	if (current_line_index == start_line_index)
		return (start_index_in_start_line);
	else
		return (0);
}
