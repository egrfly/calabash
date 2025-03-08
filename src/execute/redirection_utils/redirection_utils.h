/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:27:41 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 15:47:52 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_UTILS_H
# define REDIRECTION_UTILS_H

# include <stdbool.h>
# include "ft_list.h"
# include "../../parse/parse.h"

# define IS_HERE_DOC true
# define NOT_HERE_DOC false

bool	open_redirection_file(
			int *fd,
			char *file_name,
			int mode,
			bool is_here_doc);
void	register_redirection_reset_instruction(
			t_redirection_reset_instruction *reset_instruction,
			int fd_to_reset);
bool	perform_redirections(
			t_list *redirections);
bool	perform_read_or_write_redirection(
			t_redirection *redirection,
			int mode,
			int fallback_left_fd,
			bool is_here_doc);
bool	perform_write_or_append_both_redirection(
			t_redirection *redirection,
			int truncate_or_append);
bool	perform_input_or_output_duplication(
			t_redirection *redirection,
			int fallback_left_fd);
void	revert_redirections(
			t_list *redirections);

#endif
