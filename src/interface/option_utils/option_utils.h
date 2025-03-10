/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:47:17 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 10:36:09 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_UTILS_H
# define OPTION_UTILS_H

# include <stdbool.h>

bool	is_option_sequence_consisting_of_chars(
			const char *argument,
			const char *charset);
bool	option_is_unrecognised_or_unsupported(int argc, char **argv,
			int c_option_count);

#endif
