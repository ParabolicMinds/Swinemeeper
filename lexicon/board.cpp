#include "board.hpp"

using namespace lexicon;

board_t lexicon::board_create(dimn_t dimn, dim_t const * dims) {
	board_t board;
	board.dimn = dimn;
	board.dims = reinterpret_cast<dim_t *>(malloc(dimn * sizeof(dim_t)));
	memcpy(board.dims, dims, dimn * sizeof(dim_t));
	board.cell_len = dims[0];
	for (dimn_t d = 1; d < dimn; d++) {
		board.cell_len *= dims[d];
	}
	board.cells = reinterpret_cast<cell_t *>(calloc(board.cell_len, sizeof(cell_t)));
}

void lexicon::board_destroy(board_t & board) {
	free(board.dims);
	free(board.dims);
}

cell_t const & lexicon::board_cell_for_coord(board_t const & board, dim_t const * coords) {
	celllen_t index = 0;
	celllen_t span = 1;
	for (dimn_t d = 0; d < board.dimn; d++) {
		index += coords[span * d];
		span *= board.dims[d];
	}
	return board.cells[index];
}
