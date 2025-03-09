/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_decode_exit_status.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:06:12 by aistok            #+#    #+#             */
/*   Updated: 2025/03/09 19:36:51 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "../../main.h"

int	try_decode_exit_status(
		int exit_status,
		int backup_exit_status)
{
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	if (WIFSIGNALED(exit_status))
		return (SIGNAL_BASE + WTERMSIG(exit_status));
	return (backup_exit_status);
}
