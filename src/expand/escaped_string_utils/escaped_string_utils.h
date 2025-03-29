/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escaped_string_utils.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:13:36 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 17:08:47 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ESCAPED_STRING_UTILS_H
# define ESCAPED_STRING_UTILS_H

# include <stdbool.h>
# include <stdlib.h>

size_t	strlen_with_escapes(
			char *str,
			bool is_double_quoted);
char	*strcat_with_escapes(
			char *dest,
			const char *src,
			bool is_double_quoted);
void	strcat_number(
			char *dest,
			int nbr);

#endif
