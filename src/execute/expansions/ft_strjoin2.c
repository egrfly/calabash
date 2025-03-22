/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:10:31 by aistok            #+#    #+#             */
/*   Updated: 2025/03/22 16:33:07 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"

static size_t	ft_strlen2(const char *str)
{
	if (!str)
		return (0);
	return (ft_strlen(str));
}

char	*ft_strjoin2(
			const char *str1,
			const char *str2,
			const char *separator)
{
	size_t	str1_len;
	size_t	str2_len;
	size_t	separator_len;
	size_t	new_str_len;
	char	*new_str;

	str1_len = ft_strlen2(str1);
	str2_len = ft_strlen2(str2);
	separator_len = ft_strlen2(separator);
	new_str_len = str1_len + str2_len + separator_len;
	new_str = ft_calloc(new_str_len + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	if (str1)
		ft_strcat(new_str, str1);
	if (separator)
		ft_strcat(new_str, separator);
	if (str2)
		ft_strcat(new_str, str2);
	return (new_str);
}
