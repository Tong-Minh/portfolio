/**
 * Written by Tom Gordon 09/15/22
 * for CSCI 1933 Project 2
 * The Fen class was designed to load an object of type
 * Board with any chess board state given a proper
 * Forsyth-Edwards Notation code.
 *
 * Example FEN codes:
 * empty board: "8/8/8/8/8/8/8/8"
 * starting pos: "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"
 * smiley: "8/8/2K2K2/8/2Q2Q2/2Q2Q2/3QQ3/8"
 * "The Immortal Game" ending pos: "r1bk3r/p2pBpNp/n4n2/1p1NP2P/6P1/3P4/P1P1K3/q5b1"
 */
public class Fen {
    /**
     * Method for populating a Board object with chess
     * pieces based on the FEN code passed in.
     *
     * @param fen A FEN code string. Must not include movement commands or erroneous characters
     * @param b A Board object to load with chess position
     */
    public static void load(String fen, Board b) {
        int rank = 0;   // Rank or row of the board
        int square = 0; // Square in 'rank'
        char query;     // Temp holder for current char

        // Iterate over FEN code chars, updating Board object accordingly
        for(int i = 0; i < fen.length(); i++) {
            query = fen.charAt(i);

            // If a '/': move to next row... If a num: move n spaces in... Else add a piece
            if(query == '/') {
                rank++;
                square = 0;
            }
            else if(Character.isDigit(query)) {
                square += Character.getNumericValue(query);
            }
            // Logic to set correct piece... uses ternary operators not covered in class
            else if(query == 'p' || query == 'P') { // Pawn
                b.setPiece(rank, square, query == 'p' ? new Piece('\u265f', rank, square++, true) :
                                                            new Piece('\u2659', rank, square++, false));
            }
            else if(query == 'r' || query == 'R') { // Rook
                b.setPiece(rank, square, query == 'r' ? new Piece('\u265c', rank, square++, true) :
                                                            new Piece('\u2656', rank, square++, false));
            }
            else if(query == 'n' || query == 'N') { // Knight
                b.setPiece(rank, square, query == 'n' ? new Piece('\u265e', rank, square++, true) :
                                                            new Piece('\u2658', rank, square++, false));
            }
            else if(query == 'b' || query == 'B') { // Bishop
                b.setPiece(rank, square, query == 'b' ? new Piece('\u265d', rank, square++, true) :
                                                            new Piece('\u2657', rank, square++, false));
            }
            else if(query == 'q' || query == 'Q') { // Queen
                b.setPiece(rank, square, query == 'q' ? new Piece('\u265b', rank, square++, true) :
                                                            new Piece('\u2655', rank, square++, false));
            }
            else if(query == 'k' || query == 'K') { // King
                b.setPiece(rank, square, query == 'k' ? new Piece('\u265a', rank, square++, true) :
                                                            new Piece('\u2654', rank, square++, false));
            }
        }
    }
}
