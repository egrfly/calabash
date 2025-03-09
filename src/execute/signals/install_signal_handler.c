/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   install_signal_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:38:47 by aistok            #+#    #+#             */
/*   Updated: 2025/03/09 22:35:05 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>

void	install_signal_handler(
			int signal_received,
			void (*signal_handler)(
				int signal_received,
				siginfo_t *info,
				void *ucontext))
{
	struct sigaction	sigaction_with_signal_handler;

	sigaction_with_signal_handler.sa_sigaction = signal_handler;
	sigemptyset(&sigaction_with_signal_handler.sa_mask);
	sigaction_with_signal_handler.sa_flags = SA_SIGINFO | SA_RESTART;
	sigaction(signal_received, &sigaction_with_signal_handler, NULL);
}
