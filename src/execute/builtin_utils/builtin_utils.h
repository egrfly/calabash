/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 03:21:34 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 21:56:55 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_UTILS_H
# define BUILTIN_UTILS_H

# include "ft_binary_tree.h"
# include "../../interface/interface.h"
# include "../execute.h"

# define START 0

typedef enum e_builtin
{
	NOT_A_BUILTIN,
	BUILTIN_COLON,
	BUILTIN_DOT,
	BUILTIN_ALIAS,
	BUILTIN_BG,
	BUILTIN_BIND,
	BUILTIN_BUILTIN,
	BUILTIN_CALLER,
	BUILTIN_CD,
	BUILTIN_COMMAND,
	BUILTIN_COMPGEN,
	BUILTIN_COMPLETE,
	BUILTIN_COMPOPT,
	BUILTIN_DECLARE,
	BUILTIN_DIRS,
	BUILTIN_DISOWN,
	BUILTIN_ECHO,
	BUILTIN_ENABLE,
	BUILTIN_ENV,
	BUILTIN_EVAL,
	BUILTIN_EXEC,
	BUILTIN_EXIT,
	BUILTIN_EXPORT,
	BUILTIN_FC,
	BUILTIN_FG,
	BUILTIN_GETOPTS,
	BUILTIN_HASH,
	BUILTIN_HELP,
	BUILTIN_HISTORY,
	BUILTIN_JOBS,
	BUILTIN_LET,
	BUILTIN_LOCAL,
	BUILTIN_LOGOUT,
	BUILTIN_MAPFILE,
	BUILTIN_POPD,
	BUILTIN_PUSHD,
	BUILTIN_PWD,
	BUILTIN_READ,
	BUILTIN_READARRAY,
	BUILTIN_READONLY,
	BUILTIN_RETURN,
	BUILTIN_SET,
	BUILTIN_SHIFT,
	BUILTIN_SHOPT,
	BUILTIN_SOURCE,
	BUILTIN_SUSPEND,
	BUILTIN_TIMES,
	BUILTIN_TRAP,
	BUILTIN_TYPE,
	BUILTIN_TYPESET,
	BUILTIN_ULIMIT,
	BUILTIN_UMASK,
	BUILTIN_UNALIAS,
	BUILTIN_UNSET,
	BUILTIN_WAIT,
}	t_builtin;

t_builtin	get_builtin(
				char *command);
int			execute_builtin(
				t_binary_tree_node *node,
				t_fixed_program_elements *fixed_program_elements,
				t_program_vars *program_vars);

#endif
