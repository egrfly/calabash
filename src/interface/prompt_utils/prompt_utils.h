/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:33:20 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 04:36:07 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_UTILS_H
# define PROMPT_UTILS_H

# define ESC_CYAN "\001\033[36m\002"
# define ESC_GREEN "\001\033[32m\002"
# define ESC_RED "\001\033[31m\002"
# define ESC_END "\001\033[0m\002"

# define SHORT_PROMPT_COMPONENT_MAX 16
# define LONG_PROMPT_COMPONENT_MAX 32
# define EXIT_STATUS_LENGTH_MAX 3

void	get_short_prompt_component(
			char *buffer,
			char *command,
			char **argv);
void	update_command_prompt(
			char *prompt,
			int exit_status);

#endif
