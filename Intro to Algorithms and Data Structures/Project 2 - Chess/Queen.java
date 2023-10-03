//Written by Minh Tong, tong0154

public class Queen {

    /**
     * Constructor.
     * @param row   The current row of the pawn.
     * @param col   The current column of the pawn.
     * @param isBlack   The color of the pawn.
     */
    public Queen(int row, int col, boolean isBlack) {
        this.row = row;
        this.col = col;
        this.isBlack = isBlack;
    }

    /**
     * Checks if a move to a destination square is legal.
     * @param board     The game board.
     * @param endRow    The row of the destination square.
     * @param endCol    The column of the destination square.
     * @return True if the move to the destination square is legal, false otherwise.
     */
    public boolean isMoveLegal(Board board, int endRow, int endCol) {
        if (board.verifySourceAndDestination(row, col, endRow, endCol, isBlack)) {
            if (endRow == row) { // destination right/left
                return board.verifyHorizontal(row, col, endRow, endCol);
            }
            else if (endCol == col) { // destination up/down
                return board.verifyVertical(row, col, endRow, endCol);
            }
            else {
                return board.verifyDiagonal(row, col, endRow, endCol);
            }
        }
        return false;
    }

    // Instance variables
    private int row;
    private int col;
    private boolean isBlack;

}
