#include "parsing.h"
#include "utils.h"

/**
 * @brief Parses both a triad of position and a triad of direction, checking
 * the latter for the range [-1, 1].
 */
t_ps	parse_pos_dir(char **line, t_shape *tmp)
{
	if (goto_next_word(line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_position(*line, &tmp->position) != DONE)
		return (TRIAD_ERR);
	if (goto_next_word(line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_position(*line, &tmp->direction) != DONE)
		return (TRIAD_ERR);
	if (!is_in_range(tmp->direction.x, (t_range){-1.0f, 1.0f})
		|| !is_in_range(tmp->direction.y, (t_range){-1.0f, 1.0f})
		|| !is_in_range(tmp->direction.z, (t_range){-1.0f, 1.0f}))
		return (VALUE_ERR);
	return (DONE);
}
