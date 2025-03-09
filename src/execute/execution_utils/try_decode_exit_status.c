/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_decode_exit_status.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:06:12 by aistok            #+#    #+#             */
/*   Updated: 2025/03/09 17:16:20 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>

int	try_decode_exit_status(
		int exit_status,
		int alternative_exit_status)
{
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	if (WIFSIGNALED(exit_status))
		return (WTERMSIG(exit_status) + 128);
	return (alternative_exit_status);
}
