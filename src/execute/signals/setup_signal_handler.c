/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signal_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:38:47 by aistok            #+#    #+#             */
/*   Updated: 2025/03/06 14:10:57 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_string.h"

/* QUESTION: the last parameter may not make any sense? */
void	setup_signal_handler(
			int signal_received,
			void (*function_to_call)(), int block_signal_received)
{
	struct sigaction	sa_new;
	struct sigaction	sa_orig;

	ft_memset(&sa_new, 0x00, sizeof(sa_new));
	sigemptyset(&sa_new.sa_mask);
	if (block_signal_received)
		sigaddset(&sa_new.sa_mask, signal_received);
	sa_new.sa_flags = SA_SIGINFO;
	sa_new.sa_sigaction = function_to_call;
	sigaction(signal_received, &sa_new, &sa_orig);
}
