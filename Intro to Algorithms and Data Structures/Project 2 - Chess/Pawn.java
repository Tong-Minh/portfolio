//Written by Minh Tong, tong0154

public class Pawn {

    /**
     * Constructor.
     * @param row   The current row of the pawn.
     * @param col   The current column of the pawn.
     * @param isBlack   The color of the pawn.
     */
    public Pawn(int row, int col, boolean isBlack) {
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
        if (board.verifyVertical(this.row, this.col, endRow, endCol) && board.getPiece(endRow, endCol) == null) {
            // Case 1: Forward movement to empty square.
            // Determine if the distance being moved is valid.
            if (this.isBlack) {
                return (endRow == this.row + 1) || ((endRow == this.row + 2) && (this.row == 1));
            } else {
                return (endRow == this.row - 1) || ((endRow == this.row - 2) && (this.row == 6));
            }
        } else if (this.col == endCol+1 || this.col == endCol-1) {
            // Case 2: Capturing a piece.
            if (board.getPiece(endRow, endCol) != null && board.getPiece(endRow, endCol).getIsBlack() != this.isBlack) {
                // There is a piece of the opposite color to be captured.
                if (this.isBlack) {
                    return (endRow == this.row + 1);
                } else {
                    return (endRow == this.row - 1);
                }
            } else {
                return false;
            }
        } else {
            // Case 3: Moving in a non-adjacent column. (illegal move)
            return false;
        }
    }

    // Instance variables
    private int row;
    private int col;
    private boolean isBlack;

}
