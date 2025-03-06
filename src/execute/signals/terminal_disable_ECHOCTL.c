/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_disable_ECHOCTL.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:27:20 by aistok            #+#    #+#             */
/*   Updated: 2025/03/06 15:15:01 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include "ft_string.h"

void	terminal_disable_echoctl(bool disable_ECHOCTL)
{
	static struct termios	original_settings;
	static struct termios	current_settings;
	static bool				initialized = false;

	if (!initialized)
		tcgetattr(STDIN_FILENO, &original_settings);
	ft_memcpy(&current_settings, &original_settings,
		sizeof(original_settings));
	if (disable_ECHOCTL)
		current_settings.c_lflag &= ~(ECHOCTL);
	else
		ft_memcpy(&current_settings, &original_settings,
			sizeof(original_settings));
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &current_settings);
}
