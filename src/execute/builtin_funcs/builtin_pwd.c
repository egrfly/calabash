/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/10 05:57:07 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_binary_tree.h"
#include "ft_stdio.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../execute.h"
#include "../execution_funcs/execution_funcs.h"

int	builtin_pwd(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	char	*path;

	(void)node;
	(void)tokens_and_syntax_tree;
	(void)program_vars;
	path = getcwd(NULL, 0);
	ft_printf("%s\n", path);
	free(path);
	return (SUCCESS);
}
