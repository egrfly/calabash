/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:40:31 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 15:22:56 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdbool.h>

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

typedef int	(*t_builtin_cmd_function)(char *const *, char *const *);

int			builtin_echo(char *const *argv, char *const *envp);
int			builtin_cd(char *const *argv, char *const *envp);
int			builtin_pwd(char *const *argv, char *const *envp);
int			builtin_export(char *const *argv, char *const *envp);
int			builtin_unset(char *const *argv, char *const *envp);
int			builtin_env(char *const *argv, char *const *envp);
int			builtin_exit(char *const *argv, char *const *envp);

t_builtins	get_builtin_cmd_index(const char *command);
bool		is_builtin_command(const char *command);

#endif
