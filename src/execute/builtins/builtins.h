/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:40:31 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/09 23:17:06 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdbool.h>
# include "../../interface/interface.h"

typedef enum e_builtins
{
	BUILTIN_NOT_FOUND = 0,
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT,
	BUILTIN_HISTORY,
}	t_builtins;

typedef int	(*t_builtin_cmd_function)(
				char **, t_program_vars *);

int			builtin_echo(
				char **argv,
				t_program_vars *program_vars);
int			builtin_cd(
				char **argv,
				t_program_vars *program_vars);
int			builtin_pwd(
				char **argv,
				t_program_vars *program_vars);
int			builtin_export(
				char **argv,
				t_program_vars *program_vars);
int			builtin_unset(
				char **argv,
				t_program_vars *program_vars);
int			builtin_env(
				char **argv,
				t_program_vars *program_vars);
int			builtin_exit(
				char **argv,
				t_program_vars *program_vars);
int			builtin_history(
				char **argv,
				t_program_vars *program_vars);

t_builtins	get_builtin_cmd_index(const char *command);
bool		is_builtin_command(const char *command);

#endif
