/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:47:17 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/27 22:07:49 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_UTILS_H
# define OPTION_UTILS_H

# include <stdbool.h>

bool	option_is_unrecognised_or_unsupported(int argc, char **argv,
			int c_option_count);

#endif
