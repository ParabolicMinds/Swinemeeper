#ifndef LEXICON_BOARD_H
#define LEXICON_BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

typedef unsigned char	mine_t;
typedef unsigned short	adj_t;
typedef unsigned char	dimn_t;
typedef unsigned short	dim_t;
typedef unsigned long	celllen_t;

typedef struct cell_s {
	mine_t		mine;
	adj_t		adj;
} cell_t;

typedef struct board_s {
	dimn_t		dimn;
	dim_t *		dims;
	celllen_t	cell_len;
	cell_t *	cells;
} board_t;

void board_create(board_t *, dimn_t, dim_t const *);
void board_destroy(board_t *);
cell_t * board_cell_for_coord(board_t const *, dim_t const *);

#ifdef __cplusplus
}
#endif

#endif //LEXICON_BOARD_HPP
