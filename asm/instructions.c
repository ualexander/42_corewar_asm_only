/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 17:07:53 by vsanta            #+#    #+#             */
/*   Updated: 2019/11/10 17:17:36 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"

int get_arg_size(unsigned char args_codes, t_arg arg, t_op *op)
{
	if (((args_codes >> arg.bit_move) & IND_CODE) == IND_CODE)
		return (A_IND_SIZE);
	else if (((args_codes >> arg.bit_move) & REG_CODE) == REG_CODE)
		return (A_REG_SIZE);
	else if (((args_codes >> arg.bit_move) & DIR_CODE) == DIR_CODE)
		return (op->t_dir_size);
	return (0);
}

void set_instruction_size(t_asm *asemb, t_lst *inst)
{
	int arg_i;
	unsigned int cur_bit_pos;

	cur_bit_pos = 0;
	while (inst)
	{
		arg_i = 0;
		INST(inst)->bit_pos = cur_bit_pos;
		INST(inst)->bit_size = INST(inst)->op->args_types_code ?
			A_REG_SIZE + A_ARGS_SIZE : A_REG_SIZE;
		while (arg_i < INST(inst)->op->args_num)
		{
			INST(inst)->bit_size +=
				get_arg_size(INST(inst)->args_codes,
					INST(inst)->args[arg_i], INST(inst)->op);
			arg_i++;
		}
		cur_bit_pos += INST(inst)->bit_size;
		if (inst->next == NULL)
			asemb->exec_code_size = cur_bit_pos;
		inst = inst->next;
	}
}

t_label *find_label(t_lst *labels, char *name)
{
	while (labels)
	{
		if (ft_strcmp(LABEL(labels)->name, name) == 0)
			return (LABEL(labels));
		labels = labels->next;
	}
	return (NULL);
}

void convert_labels_to_args(t_asm *asemb, t_lst *inst)
{
	int arg_i;

	t_label *label;
	while (inst)
	{
		arg_i = 0;
		while (arg_i < INST(inst)->op->args_num)
		{
			if (INST(inst)->args[arg_i].larg)
			{
				label =
					find_label(asemb->labels, INST(inst)->args[arg_i].larg);
				if (label == NULL)
					put_error(asemb); // label not find
				INST(inst)->args[arg_i].arg =
					label->inst->bit_pos - INST(inst)->bit_pos;
			}
			arg_i++;
		}
		inst = inst->next;
	}
}