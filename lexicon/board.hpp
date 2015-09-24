#ifndef LEXICON_BOARD_HPP
#define LEXICON_BOARD_HPP

#include "common.hpp"

namespace lexicon {

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

	board_t board_create(dimn_t dimn, dim_t const * dims);
	void board_destroy(board_t &);
	cell_t const & board_cell_for_coord(board_t const &, dim_t const * coords);
}

#endif //LEXICON_BOARD_HPP
