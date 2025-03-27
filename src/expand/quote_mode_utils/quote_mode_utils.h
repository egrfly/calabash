/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_mode_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:38:00 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/27 16:43:21 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_MODE_UTILS_H
# define QUOTE_MODE_UTILS_H

# include <stdbool.h>
# include "../../lex/lex.h"

bool	update_quote_mode_based_on_current_char(
			char *c,
			bool is_heredoc,
			t_quote_mode *quote_mode);

#endif
