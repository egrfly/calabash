/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:40:31 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 15:33:04 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "ft_binary_tree.h"

int	execute(t_binary_tree *tree, char *program_name, char **envp);
int	execute_builtin_command(
		const char *command, char *const *argv, char *const *envp);

#endif
