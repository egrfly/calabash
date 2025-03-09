/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigquit_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:32:58 by aistok            #+#    #+#             */
/*   Updated: 2025/03/09 22:49:10 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include "./signals.h"

void	sigquit_handler(
			int signal_received,
			siginfo_t *info,
			void *ucontext)
{
	(void)signal_received;
	(void)info;
	(void)ucontext;
	g_signal = SIGQUIT;
	if (!rl_done)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
