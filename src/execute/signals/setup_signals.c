/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:41:31 by aistok            #+#    #+#             */
/*   Updated: 2025/03/09 02:51:04 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include "../../interface/interface.h"
#include "./signals.h"

int	readline_waiting_for_input_event(void)
{
	if (g_signal == SIGINT)
		rl_done = true;
	return (0);
}

void	setup_signals(void)
{
	rl_event_hook = readline_waiting_for_input_event;
	setup_signal_handler(SIGINT, sigint_and_sigquit_handler, false);
	setup_signal_handler(SIGQUIT, sigint_and_sigquit_handler, false);
}
