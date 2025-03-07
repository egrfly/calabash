/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:40:31 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/07 00:54:34 by aistok           ###   ########.fr       */
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
}	t_builtins;

typedef int	(*t_builtin_cmd_function)(
				const char **, t_program_name_and_env *);

int			builtin_echo(
				const char **argv,
				t_program_name_and_env *program_name_and_env);
int			builtin_cd(
				const char **argv,
				t_program_name_and_env *program_name_and_env);
int			builtin_pwd(
				const char **argv,
				t_program_name_and_env *program_name_and_env);
int			builtin_export(
				const char **argv,
				t_program_name_and_env *program_name_and_env);
int			builtin_unset(
				const char **argv,
				t_program_name_and_env *program_name_and_env);
int			builtin_env(
				const char **argv,
				t_program_name_and_env *program_name_and_env);
int			builtin_exit(
				const char **argv,
				t_program_name_and_env *program_name_and_env);

t_builtins	get_builtin_cmd_index(const char *command);
bool		is_builtin_command(const char *command);

#endif
