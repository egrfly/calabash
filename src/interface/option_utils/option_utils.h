/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:47:17 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/10 22:54:38 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_UTILS_H
# define OPTION_UTILS_H

# include <stdbool.h>

bool	has_more_options(int argc, int c_option_count,
			int options_end_count);
bool	option_is_unrecognised_or_unsupported(int argc, char **argv,
			int c_option_count);

#endif
