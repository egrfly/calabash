/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 04:15:27 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 04:17:22 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_UTILS_H
# define INPUT_UTILS_H

# include "../lex.h"

char	get_current_char(
			t_input_tracker *input_tracker);
char	*get_current_char_pointer(
			t_input_tracker *input_tracker);

#endif
