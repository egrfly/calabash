/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_getters.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:08:39 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 12:48:54 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_GETTERS_H
# define LINE_GETTERS_H

# include "../interface.h"

# define LATEST_LINE 0

char	*access_input_lines(t_access_mode mode, char **new_input_lines);
char	*noninteractive_get_next_line_from_split_string(void *arg);
char	*noninteractive_get_next_line_from_file_descriptor(void *arg);
char	*interactive_get_next_line_from_standard_input(void *arg);

#endif
