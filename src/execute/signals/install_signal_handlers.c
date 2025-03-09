/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   install_signal_handlers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:41:31 by aistok            #+#    #+#             */
/*   Updated: 2025/03/09 21:51:53 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include "./signals.h"

int	break_if_sigint_received(void)
{
	if (g_signal == SIGINT)
		rl_done = true;
	return (0);
}

void	install_signal_handlers(void)
{
	rl_event_hook = break_if_sigint_received;
	install_signal_handler(SIGINT, sigint_handler);
	install_signal_handler(SIGQUIT, sigquit_handler);
}
