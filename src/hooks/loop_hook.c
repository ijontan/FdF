/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 04:56:54 by itan              #+#    #+#             */
/*   Updated: 2023/03/10 17:49:13 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	loop_hook(t_vars *vars)
{
	t_slerp_var	*slerp_var;

	if (vars->fdf->cycle_count < vars->fdf->cycle_per_frame)
		vars->fdf->cycle_count += 1;
	else
		vars->fdf->cycle_count = 0;
	if (vars->fdf->slerp_var.t < 1 && !vars->fdf->cycle_count)
	{
		slerp_var = &(vars->fdf->slerp_var);
		if (!quaternion_equal(&(slerp_var->start_o), &(slerp_var->end_o)))
			quaternion_slerp(&(slerp_var->start_o), &(slerp_var->end_o),
					slerp_var->t, &(slerp_var->out_o));
		quaternion_normalize(&(slerp_var->out_o), &(slerp_var->out_o));
		slerp_var->t += 0.05;
		if (slerp_var->sign == 1 && vars->fdf->focal_len < 209715200)
			vars->fdf->focal_len = (vars->fdf->focal_len - 130) * 2;
		else if (vars->fdf->focal_len > 130)
			vars->fdf->focal_len = vars->fdf->focal_len / 2 + 130;
		display(vars);
	}
	if (vars->fdf->slerp_var.t <= 1.05 && vars->fdf->slerp_var.t >= 1.0
		&& !vars->fdf->cycle_count)
	{
		slerp_var = &(vars->fdf->slerp_var);
		vars->fdf->orientation = slerp_var->end_o;
		slerp_var->t += 0.05;
		display(vars);
	}
	return (0);
}
