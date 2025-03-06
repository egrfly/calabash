/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_if_out_of_memory.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:48:20 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 03:11:41 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_stdio.h"
#include "../../interface/interface.h"
#include "../execute.h"
#include "../execution_utils/execution_utils.h"
#include "./command_utils.h"

void	exit_if_out_of_memory(
			char *program_name,
			t_exec_params *exec_params,
			t_tokens_and_syntax_tree *tokens_and_syntax_tree)
{
	ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
		program_name);
	destroy_exec_params(exec_params);
	destroy_tokens_and_syntax_tree(tokens_and_syntax_tree);
	exit(GENERAL_FAILURE);
}
