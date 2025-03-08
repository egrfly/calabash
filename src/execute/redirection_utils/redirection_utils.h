/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:27:41 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 05:23:54 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_UTILS_H
# define REDIRECTION_UTILS_H

# include <stdbool.h>
# include "ft_list.h"
# include "../../parse/parse.h"

# define OPEN_FAILURE -1
# define DUP_FAILURE -1

bool	open_redirection_file(
			int *fd,
			char *file_name,
			int mode,
			char *program_name);
void	register_redirection_reset_instruction(
			t_redirection_reset_instruction *reset_instruction,
			int fd_to_reset);
bool	perform_redirections(
			t_list *redirections,
			char *program_name);
void	revert_redirections(
			t_list *redirections);

#endif
