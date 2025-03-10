/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_getters.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:08:39 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 08:46:16 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_GETTERS_H
# define LINE_GETTERS_H

char	*noninteractive_get_next_line_from_file_descriptor(
			void *arg);
char	*interactive_get_next_line_from_standard_input(
			void *arg);
char	*noninteractive_get_null_line(
			void *arg);

#endif
