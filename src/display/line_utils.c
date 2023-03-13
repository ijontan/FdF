/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:03:37 by itan              #+#    #+#             */
/*   Updated: 2023/03/13 18:03:55 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// swaps two numbers
void	swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

// returns absolute value of number
float	absolute(float x)
{
	if (x < 0)
		return (-x);
	else
		return (x);
}

//returns fractional part of a number
float	frac_num(float x)
{
	if (x > 0)
		return (x - (int)(x));
	else
		return (x - ((int)(x) + 1));
}

//returns 1 - fractional part of number
float	rfrac_num(float x)
{
	return (1 - frac_num(x));
}
