//Written by Minh Tong, tong0154

public class Board {

    // Instance variables
    private Piece[][] board;
    private int turn = 2;

    //TODO:
    // Construct an object of type Board using given arguments.
    public Board() {
        this.board = new Piece[8][8]; //setting board to an array with 8 rows and columns

        //implementing a bunch of new objects line by line because its less complicated than using the whole of fen class to add in the pieces to the board
        //Top row of special pieces
        board[0][0] = new Piece('\u265c', 0, 0, true); //rook
        board[0][1] = new Piece('\u265e', 0, 1, true); //knight
        board[0][2] = new Piece('\u265d', 0, 2, true); //bishop
        board[0][3] = new Piece('\u265b', 0, 3, true); //queen
        board[0][4] = new Piece('\u265a', 0, 4, true); //king
        board[0][5] = new Piece('\u265d', 0, 5, true); //bishop
        board[0][6] = new Piece('\u265e', 0, 6, true); //knight
        board[0][7] = new Piece('\u265c', 0, 7, true); //rook

        //Top row of pawns
        board[1][0] = new Piece('\u265f', 1, 0, true);
        board[1][1] = new Piece('\u265f', 1, 1, true);
        board[1][2] = new Piece('\u265f', 1, 2, true);
        board[1][3] = new Piece('\u265f', 1, 3, true);
        board[1][4] = new Piece('\u265f', 1, 4, true);
        board[1][5] = new Piece('\u265f', 1, 5, true);
        board[1][6] = new Piece('\u265f', 1, 6, true);
        board[1][7] = new Piece('\u265f', 1, 7, true);

        //Bottom row of pawns
        board[6][0] = new Piece('\u2659', 6, 0, false);
        board[6][1] = new Piece('\u2659', 6, 1, false);
        board[6][2] = new Piece('\u2659', 6, 2, false);
        board[6][3] = new Piece('\u2659', 6, 3, false);
        board[6][4] = new Piece('\u2659', 6, 4, false);
        board[6][5] = new Piece('\u2659', 6, 5, false);
        board[6][6] = new Piece('\u2659', 6, 6, false);
        board[6][7] = new Piece('\u2659', 6, 7, false);

        //Bottom row of special pieces
        board[7][0] = new Piece('\u2656', 7, 0, false); //rook
        board[7][1] = new Piece('\u2658', 7, 1, false); //knight
        board[7][2] = new Piece('\u2657', 7, 2, false); //bishop
        board[7][3] = new Piece('\u2655', 7, 3, false); //queen
        board[7][4] = new Piece('\u2654', 7, 4, false); //king
        board[7][5] = new Piece('\u2657', 7, 5, false); //bishop
        board[7][6] = new Piece('\u2658', 7, 6, false); //knight
        board[7][7] = new Piece('\u2656', 7, 7, false); //rook
    }

    // Accessor Methods
    public Piece[][] getBoard() { // returns the board so I can use it to more easily get certain indexes in game.java
        return this.board;
    }

    public boolean getWinner(){ // returns true or false depending on white or black winning
        char king1 = '\u2654';
        char king2 = '\u265a';
        boolean winner = false;
        for (int row = 0; row<board.length; row++){
            for (int col = 0; col<board.length; col++) {
                if (board[row][col] != null && getPiece(row, col).getCharacter() == king1) {
                    winner = true;
                } else if (board[row][col] != null && getPiece(row, col).getCharacter() == king2) {
                    winner = false;
                }
            }
        }

        return winner;
    }

    public boolean whitesTurn(){ // returns true if it is whites turn
        if (turn % 2 == 0) {
            return true;
        }
        return false;
    }

    //TODO:
    // Return the Piece object stored at a given row and column
    public Piece getPiece(int row, int col) {
        Piece getPiece = this.board[row][col];
        return getPiece;
    }

    //TODO:
    // Update a single cell of the board to the new piece.
    public void setPiece(int row, int col, Piece piece) {
        this.board[row][col] = piece;
    }

    // Game functionality methods
    public void turnCounter(){ //increments the turn if it was a valid turn, called in the main
        this.turn++;
    }

    //TODO:
    // Moves a Piece object from one cell in the board to another, provided that
    // this movement is legal. Returns a boolean to signify success or failure.
    public boolean movePiece(int startRow, int startCol, int endRow, int endCol) {
        if(getPiece(startRow, startCol).isMoveLegal(this, endRow, endCol)) {
            getPiece(startRow, startCol).setPosition(endRow, endCol);
            setPiece(endRow, endCol, getPiece(startRow, startCol));
            setPiece(startRow, startCol, null);
            return true;
        }
        return false;
    }

    //TODO:
    // Determines whether the game has been ended, i.e., if one player's King
    // has been captured.
    public boolean isGameOver() { // iterates through board and counts kings, only returning false if there are still two
        char king1 = '\u265a';
        char king2 = '\u2654';
        int kingCount = 0;

        for (int row = 0; row<board.length; row++){
            for (int col = 0; col<board.length; col++) {
                if (board[row][col] != null && getPiece(row, col).getCharacter() == king1) {
                    kingCount++;
                } else if (board[row][col] != null && getPiece(row, col).getCharacter() == king2) {
                    kingCount++;
                }
            }
        }
        if (kingCount == 2) {
            return false;
        }
        return true;
    }

    //TODO:
    // Construct a String that represents the Board object's 2D array. Return
    // the fully constructed String.
    public String toString() {
        String visual = "  ";

        for (int col = 0; col<board.length; col++) { // first row of numbers
            visual = visual + col + " ";
        }
        visual = visual + "\n";

        for (int row = 0; row<board.length; row++) { // every subsequent row of numbers + a loop for the pieces and null spaces
            visual = visual + row + "|"; // initial | and space
            for (int col = 0; col<board.length; col++) {
                if (board[row][col] == null) { // null spaces
                    visual = visual + " |";
                } else {
                    visual = visual + board[row][col] + "|"; // chess pieces
                }
            }
            visual = visual + "\n";
        }
        return visual;
    }

    //TODO:
    // Sets every cell of the array to null. For debugging and grading purposes.
    public void clear() {
        for (int row = 0; row<board.length; row++){
            for (int col = 0; col<board.length; col++) {
                board[row][col] = null;
            }
        }
    }

    // Movement helper functions
    public boolean verifyKnight(int startRow, int startCol, int endRow, int endCol) { //will check if knight is making an L movement
        //Case 1: up then right or left
        if (startRow - endRow == 2 && (endCol - startCol == 1 || endCol - startCol == -1)) {
            return true;
        }
        //Case 2: down then right or left
        else if (startRow - endRow == -2 && (endCol - startCol == 1 || endCol - startCol == -1)) {
            return true;
        }
        //Case 3: right then up or down
        else if (startCol - endCol == -2 && (endRow - startRow == 1 || endRow - startRow == -1)) {
            return true;
        }
        //Case 4: left then up or down
        else if (startCol - endCol == 2 && (endRow - startRow == 1 || endRow - startRow == -1)) {
            return true;
        }
        //Case 5: nothing
        else if (startRow == endRow && startRow == endCol) {
            return true;
        }
        else {
            return false;
        }
    }

    //TODO:
    // Ensure that the player's chosen move is even remotely legal.
    // Returns a boolean to signify whether:
    // - 'start' and 'end' fall within the array's bounds.
    // - 'start' contains a Piece object, i.e., not null.
    // - Player's color and color of 'start' Piece match.
    // - 'end' contains either no Piece or a Piece of the opposite color.
    public boolean verifySourceAndDestination(int startRow, int startCol, int endRow, int endCol, boolean isBlack) {
        if ((startRow > -1 && startRow < 8) && (startCol > -1 && startCol < 8) && (endRow > -1 && endRow < 8) && (endCol > -1 && endCol < 8)) {
            if (getPiece(startRow, startCol) != null) {
                return getPiece(endRow, endCol) == null || isBlack != getPiece(endRow, endCol).getIsBlack();
            }
        }
        return false;
    }

    //TODO:
    // Check whether the 'start' position and 'end' position are adjacent to each other
    public boolean verifyAdjacent(int startRow, int startCol, int endRow, int endCol) {
        //Case 1: Diagonal
        if ((startRow - 1 == endRow || startRow + 1 == endRow) && (startCol - 1 == endCol || startCol + 1 == endCol)) {
            return true;
        }
        //Case 2: Horizontal
        else if (startRow == endRow && (startCol-endCol == 1 || startCol-endCol == -1)) {
            return true;
        }
        //Case 3: Vertical
        else if (startCol == endCol && (startRow-endRow == 1 || startRow-endRow == -1)) {
            return true;
        }
        return false;
    }

    //TODO:
    // Checks whether a given 'start' and 'end' position are a valid horizontal move.
    // Returns a boolean to signify whether:
    // - The entire move takes place on one row.
    // - All spaces directly between 'start' and 'end' are empty, i.e., null.
    public boolean verifyHorizontal(int startRow, int startCol, int endRow, int endCol) {
        int colDiff = startCol - endCol;
        boolean clearPath = false;
        int count = 0;

        if(colDiff > 0){ //moving left on the board
            for (int i = startCol - 1; i > endCol; i--) {
                if (board[startRow][i] == null) {
                    count++;
                }
            }
            if (count == colDiff-1) {
                clearPath = true;
            }

        } else if (colDiff < 0) { // moving right on the board
            for (int i = startCol + 1; i < endCol; i++) {
                if (board[startRow][i] == null) {
                    count++;
                }
            }
            if (count == (-1 * colDiff) - 1) {
                clearPath = true;
            }

        } else { // if setDiff == 0
            clearPath = true;
        }

        if ((startRow == endRow) && clearPath) { //final check
            return true;
        }

        return false;
    }

    //TODO:
    // Checks whether a given 'start' and 'end' position are a valid vertical move.
    // Returns a boolean to signify whether:
    // - The entire move takes place on one column.
    // - All spaces directly between 'start' and 'end' are empty, i.e., null.
    public boolean verifyVertical(int startRow, int startCol, int endRow, int endCol) {
        int rowDiff = startRow - endRow;
        boolean clearPath = false;
        int count = 0;

        if(rowDiff > 0){ //moving up the board
            for (int i = startRow - 1; i > endRow; i--) { // checks in between and sets boolean
                if (board[i][startCol] == null) {
                    count++;
                }
            }
            if (count == rowDiff-1) {
                clearPath = true;
            }

        } else if (rowDiff < 0) { // moving down the board
            for (int i = startRow + 1; i < endRow; i++) { // checks in between and sets boolean
                if (board[i][startCol] == null) {
                    count++;
                }
            }
            if (count == (-1 * rowDiff) - 1) {
                clearPath = true;
            }

        } else { // if setDiff == 0
            clearPath = true;
        }

        if ((startCol == endCol) && clearPath) { //final check
            return true;
        }

        return false;
    }

    //TODO:
    // Checks whether a given 'start' and 'end' position are a valid diagonal move.
    // Returns a boolean to signify whether:
    // - The path from 'start' to 'end' is diagonal... change in row and col.
    // - All spaces directly between 'start' and 'end' are empty, i.e., null.
    public boolean verifyDiagonal(int startRow, int startCol, int endRow, int endCol) {
        boolean isClear = false;
        boolean isDiagonal = false;
        int count = 0;
        int rowTracker = startRow;
        int colTracker = startCol;
        int difference = startRow - endRow;


        if ((startRow - endRow == startCol - endCol) || (startRow - endRow == -(startCol - endCol))) { // checks if it's actually a diagonal
            isDiagonal = true;
        }

        //Case 1: Moving Up/Right
        if (startRow > endRow && startCol < endCol && isDiagonal) {
            rowTracker--; // sets these to 1 over so it checks the next diagonal
            colTracker++;
            while (rowTracker > endRow && colTracker < endCol) { // loops and keeps track of the count of null spaces, stopping when it reaches the end values
                if (board[rowTracker][colTracker] == null) {
                    count++;
                }
                rowTracker--; // next iteration
                colTracker++;
            }

            if (count == (difference)-1 || count == (-difference)-1) {
                isClear = true;
            }
        }

        //Case 2: Moving Up/Left
        else if (startRow > endRow && startCol > endCol && isDiagonal) {
            rowTracker--; // sets these to 1 over so it checks the next diagonal
            colTracker--;
            while (rowTracker > endRow && colTracker > endCol) { // loops and keeps track of the count of null spaces, stopping when it reaches the end values
                if (board[rowTracker][colTracker] == null) {
                    count++;
                }
                rowTracker--; // next iteration
                colTracker--;
            }

            if (count == (difference)-1 || count == (-difference)-1) {
                isClear = true;
            }
        }

        //Case 3: Moving Down/Right
        else if (startRow < endRow && startCol < endCol && isDiagonal) {
            rowTracker++; // sets these to 1 over so it checks the next diagonal
            colTracker++;
            while (rowTracker < endRow && colTracker < endCol) { // loops and keeps track of the count of null spaces, stopping when it reaches the end values
                if (board[rowTracker][colTracker] == null) {
                    count++;
                }
                rowTracker++; // next iteration
                colTracker++;
            }

            if (count == (difference)-1 || count == (-difference)-1) {
                isClear = true;
            }
        }

        //Case 4: Moving Down/Left
        else if (startRow < endRow && startCol > endCol && isDiagonal) {
            rowTracker++; // sets these to 1 over so it checks the next diagonal
            colTracker--;
            while (rowTracker < endRow && colTracker > endCol) { // loops and keeps track of the count of null spaces, stopping when it reaches the end values
                if (board[rowTracker][colTracker] == null) {
                    count++;
                }
                rowTracker++; // next iteration
                colTracker--;
            }

            if (count == (difference)-1 || count == (-difference)-1) {
                isClear = true;
            }
        }

        //Case 5: Stays Still
        else if (startRow == endRow && startRow == endCol) {
            isClear = true;
        }

        if (isDiagonal && isClear) { // final check
            return true;
        }

        return false;
    }
}
