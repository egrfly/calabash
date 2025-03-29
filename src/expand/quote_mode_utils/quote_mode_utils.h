/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_mode_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:38:00 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 18:42:21 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_MODE_UTILS_H
# define QUOTE_MODE_UTILS_H

# include <stdbool.h>
# include "../../lex/lex.h"

bool	update_quote_mode_based_on_current_char(
			char *c,
			t_quote_mode *quote_mode,
			t_quote_mode base_quote_mode);
bool	should_expand(
			char *str,
			t_quote_mode *quote_mode,
			t_quote_mode base_quote_mode);

#endif
