//Written by Minh Tong, tong0154

import java.util.Scanner;

public class Game {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        Board game = new Board();
        //game.clear();

        System.out.println(game); // initial board
        while (!game.isGameOver()) { // loops until game is over
            if (game.whitesTurn()) { // keeps track of turn with a modulus function
                System.out.println("It is currently white's turn to play.");
            } else {
                System.out.println("It is currently black's turn to play.");
            }

            System.out.println("What is your move? (format: [start row] [start column] [end row] [end column])");
            String input = s.nextLine();
            String[] move = input.split(" ");

            if ((game.getBoard())[Integer.parseInt(move[0])][Integer.parseInt(move[1])] != null) { // checks that the piece being moved isn't null

                if (game.getPiece(Integer.parseInt(move[0]), Integer.parseInt(move[1])).getIsBlack() && !game.whitesTurn()) { // only lets a black piece move on a black turn
                    if (game.getPiece(Integer.parseInt(move[0]), Integer.parseInt(move[1])).isMoveLegal(game, Integer.parseInt(move[2]), Integer.parseInt(move[3]))) {
                        game.movePiece(Integer.parseInt(move[0]), Integer.parseInt(move[1]), Integer.parseInt(move[2]), Integer.parseInt(move[3]));
                        game.turnCounter();
                    } else {
                        System.out.println("Move is invalid.\n");
                    }
                } else if (!(game.getPiece(Integer.parseInt(move[0]), Integer.parseInt(move[1])).getIsBlack()) && game.whitesTurn()) { // only lets a white piece move on a white turn
                    if (game.getPiece(Integer.parseInt(move[0]), Integer.parseInt(move[1])).isMoveLegal(game, Integer.parseInt(move[2]), Integer.parseInt(move[3]))) {
                        game.movePiece(Integer.parseInt(move[0]), Integer.parseInt(move[1]), Integer.parseInt(move[2]), Integer.parseInt(move[3]));
                        game.turnCounter();
                    } else {
                        System.out.println("Move is invalid.\n");
                    }
                } else {
                    System.out.println("It is not your turn.\n");
                }
            } else {
                System.out.println("Move is not valid.\n");
            }

            System.out.println(game);
        }
        if (game.getWinner()) { // Prints the winner at the end
            System.out.println("White has won the game!");
        } else {
            System.out.println("Black has won the game!");
        }
    }
}
