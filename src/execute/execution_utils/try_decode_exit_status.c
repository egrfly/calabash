/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_decode_exit_status.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:06:12 by aistok            #+#    #+#             */
/*   Updated: 2025/03/09 22:40:52 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/wait.h>
#include "ft_stdio.h"
#include "../../main.h"

int	try_decode_exit_status(
		int exit_status,
		int backup_exit_status)
{
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	if (WIFSIGNALED(exit_status))
	{
		if (WTERMSIG(exit_status) == SIGINT)
			ft_printf("^C\n");
		else if (WTERMSIG(exit_status) == SIGQUIT && WCOREDUMP(exit_status))
			ft_printf("^\\Quit (core dumped)\n");
		else if (WTERMSIG(exit_status) == SIGQUIT)
			ft_printf("^\\Quit\n");
		return (SIGNAL_BASE + WTERMSIG(exit_status));
	}
	return (backup_exit_status);
}
