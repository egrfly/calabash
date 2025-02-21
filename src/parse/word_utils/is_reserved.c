/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_reserved.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 04:35:52 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 06:02:23 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_string.h"

static const
	char
	*g_reserved_words[] = {
	"function",
	"!",
	"time",
	"coproc",
	"{",
	"}",
	"[[",
	"]]",
	"if",
	"then",
	"elif",
	"else",
	"fi",
	"while",
	"until",
	"select",
	"for",
	"in",
	"do",
	"done",
	"continue",
	"break",
	"case",
	"esac",
};

bool	is_reserved(char *word)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_reserved_words) / sizeof(char *))
	{
		if (!ft_strcmp(word, g_reserved_words[i]))
			return (true);
		i++;
	}
	return (false);
}
