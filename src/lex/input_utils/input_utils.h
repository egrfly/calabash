/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 04:15:27 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 07:07:46 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_UTILS_H
# define INPUT_UTILS_H

# include <stdbool.h>
# include "../lex.h"

char	*get_current_char_pointer(
			t_input_tracker *input_tracker);
char	get_current_char(
			t_input_tracker *input_tracker);
char	*get_next_char_pointer(
			t_input_tracker *input_tracker);
char	get_next_char(
			t_input_tracker *input_tracker);
bool	in_escaped_section(
			t_input_tracker *input_tracker);
void	leave_escaped_section(
			t_input_tracker *input_tracker);

#endif
