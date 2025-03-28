/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:09:21 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 17:56:23 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAR_UTILS_H
# define CHAR_UTILS_H

# include <stdbool.h>

bool	isalpha_or_underscore(
			char c);
bool	isalnum_or_underscore(
			char c);
bool	is_expandable_char(
			char c);

#endif
