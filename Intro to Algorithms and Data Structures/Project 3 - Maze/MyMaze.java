// Names: Minh Tong, Jenna Khalili
// x500s: tong0154, khali261

import java.util.Random;
import java.util.Scanner;

public class MyMaze{
    Cell[][] maze;
    int startRow;
    int endRow;

    public MyMaze(int rows, int cols, int startRow, int endRow) {
        // Setting every cell as a cell and setting start and end row
        this.startRow = startRow;
        this.endRow = endRow;
        this.maze = new Cell[rows][cols];

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                maze[i][j] = new Cell();
            }
        }
    }

    /* TODO: Create a new maze using the algorithm found in the writeup. */
    public static MyMaze makeMaze() {
        //Instantiation of Maze object: uses a scanner to get the dimensions of the maze from the user, similar to the chess project input
        Scanner sc = new Scanner(System.in);
        System.out.println("How big will the maze be? (Format: [Rows: 5-40] [Columns: 5-40])");
        String input = sc.nextLine();
        String[] size = input.split(" ");
        int rows = Integer.parseInt(size[0]);
        int cols = Integer.parseInt(size[1]);

        // redo for invalid inputs
        while (!(rows >= 5 && rows <= 40) || !(cols >= 5 && cols <= 40)) {
            System.out.println("-Invalid Dimensions-\nHow big will the maze be? (Format: [Rows: 5-20] [Columns: 5-20])");
            input = sc.nextLine();
            size = input.split(" ");
            rows = Integer.parseInt(size[0]);
            cols = Integer.parseInt(size[1]);
        }

        //instance of random class
        Random rand = new Random();
        int startRow = rand.nextInt(rows);
        int endRow = rand.nextInt(rows);
        MyMaze newMaze = new MyMaze(rows, cols, startRow, endRow);

        //Generation of maze
        int currRow = startRow;
        int currCol = 0;
        Stack1Gen<int[]> mazeStack = new Stack1Gen<>();
        mazeStack.push(new int[]{currRow, currCol});
        newMaze.maze[mazeStack.top()[0]][mazeStack.top()[1]].setVisited(true);

        while (!mazeStack.isEmpty()) {
            currRow = mazeStack.top()[0];
            currCol = mazeStack.top()[1];
            int paths = 0;
            int direction = rand.nextInt(4);

            //seeing if there are ways to go
            if (currRow > 0) { //up
                if (!newMaze.maze[currRow - 1][currCol].getVisited()) {
                    paths++;
                }
            }
            if (currCol < newMaze.maze[0].length - 1) { //right
                if (!newMaze.maze[currRow][currCol + 1].getVisited()) {
                    paths++;
                }
            }
            if (currRow < newMaze.maze.length - 1) {//down
                if (!newMaze.maze[currRow + 1][currCol].getVisited()) {
                    paths++;
                }
            }
            if (currCol > 0) { //left
                if (!newMaze.maze[currRow][currCol - 1].getVisited()) {
                    paths++;
                }
            }

            //putting new values in the stack, only will run if there is a path to go
            if (paths != 0) { //up
                if (direction == 0 && currRow > 0) { //up
                    if (!newMaze.maze[currRow - 1][currCol].getVisited()) {
                        mazeStack.push(new int[]{currRow - 1, currCol});
                        newMaze.maze[mazeStack.top()[0]][mazeStack.top()[1]].setVisited(true);
                        newMaze.maze[mazeStack.top()[0]][mazeStack.top()[1]].setBottom(false);
                    }
                } else if (direction == 1 && currCol < newMaze.maze[0].length - 1) { //right
                    if (!newMaze.maze[currRow][currCol + 1].getVisited()) {
                        mazeStack.push(new int[]{currRow, currCol + 1});
                        newMaze.maze[mazeStack.top()[0]][mazeStack.top()[1]].setVisited(true);
                        newMaze.maze[mazeStack.top()[0]][mazeStack.top()[1] - 1].setRight(false);
                    }
                } else if (direction == 2 && currRow < newMaze.maze.length - 1) {//down
                    if (!newMaze.maze[currRow + 1][currCol].getVisited()) {
                        mazeStack.push(new int[]{currRow + 1, currCol});
                        newMaze.maze[mazeStack.top()[0]][mazeStack.top()[1]].setVisited(true);
                        newMaze.maze[mazeStack.top()[0] - 1][mazeStack.top()[1]].setBottom(false);
                    }
                } else if (direction == 3 && currCol > 0) { //left
                    if (!newMaze.maze[currRow][currCol - 1].getVisited()) {
                        mazeStack.push(new int[]{currRow, currCol - 1});
                        newMaze.maze[mazeStack.top()[0]][mazeStack.top()[1]].setVisited(true);
                        newMaze.maze[mazeStack.top()[0]][mazeStack.top()[1]].setRight(false);
                    }
                }
            }

            //in the event there are no ways to go
            if (paths == 0) {mazeStack.pop();}
        }

        //setting every visited to false
        for (int i = 0; i < newMaze.maze.length; i++) {
            for (int j = 0; j < newMaze.maze[0].length; j++) {
                newMaze.maze[i][j].setVisited(false);
            }
        }

        return newMaze;
    }

    /* TODO: Print a representation of the maze to the terminal */
    public void printMaze() {
        //printing the top line
        String topLine = "|";
        for (int i = 0; i < this.maze[0].length; i++) {
            topLine = topLine + "---|";
        }
        System.out.println(topLine);

        //printing all rows besides the last
        int rowCounter = 0;
        while (rowCounter < maze.length) {
            //special case lines appended by the for loop, then printed out
            String startLine = " ";
            String endLine = "|";
            String bothLine = " ";
            String nextLine = "|";
            String borderLine = "|";

            //checks for stars and right/bottom borders
            String starOrNot;
            String rightOrNot;
            String bottomOrNot;

            //building the middle --- or *
            for (int i = 0; i < this.maze[0].length; i++) {
                if (maze[rowCounter][i].getVisited()) {
                    starOrNot = "*";
                } else {
                    starOrNot = " ";
                }
                if (maze[rowCounter][i].getRight()) {
                    rightOrNot = "|";
                } else {
                    rightOrNot = " ";
                }
                if (maze[rowCounter][i].getBottom()) {
                    bottomOrNot = "---";
                } else {
                    bottomOrNot = "   ";
                }

                //Building the strings if it's the start row or any other row
                if (rowCounter == this.startRow && i == 0) {
                    startLine = startLine + " " + starOrNot + " " + rightOrNot;
                } else if (rowCounter == this.startRow) {
                    startLine = startLine + " " + starOrNot + " " + rightOrNot;
                } else {
                    nextLine = nextLine + " " + starOrNot + " " + rightOrNot;
                }

                //building the end string and the case where the start and end are the same
                if (rowCounter == this.endRow && i == this.maze[0].length - 1) {
                    endLine = endLine + " " + starOrNot + "  ";
                } else if (rowCounter == this.endRow)  {
                    endLine = endLine + " " + starOrNot + " " + rightOrNot;
                }

                if (rowCounter == this.endRow && i == this.maze[0].length - 1) {
                    bothLine = bothLine + " " + starOrNot + "  ";
                } else if (rowCounter == this.endRow)  {
                    bothLine = bothLine + " " + starOrNot + " " + rightOrNot;
                }

                //Building the bottom lines of the string
                borderLine = borderLine + bottomOrNot + "|";
            }

            //printing everything
            if (rowCounter == this.startRow && rowCounter == this.endRow) {System.out.println(bothLine);}
            else if(rowCounter == this.startRow) {System.out.println(startLine);}
            else if (rowCounter == this.endRow){System.out.println(endLine);}
            else {System.out.println(nextLine);}
            System.out.println(borderLine);
            rowCounter++;
        }
    }

    /* TODO: Solve the maze using the algorithm found in the writeup. */
    public void solveMaze() {
        Q1Gen<int[]> queue = new Q1Gen();
        queue.add(new int[] {startRow, 0});

        //utilizing a queue to test all possible paths until the maze is solved
        while(queue.length() != 0) {
            int[] currCell = queue.remove();
            int currRow = currCell[0];
            int currCol = currCell[1];
            this.maze[currRow][currCol].setVisited(true);

            if(currRow == endRow && currCol == this.maze[0].length - 1) {
                break;
            }

            if((currRow - 1) >= 0 && !this.maze[currRow - 1][currCol].getVisited() && !this.maze[currRow - 1][currCol].getBottom()) { // checks above current cell
                queue.add(new int[] {currRow - 1, currCol});
            }

            if((currCol + 1) < this.maze[0].length && !this.maze[currRow][currCol + 1].getVisited() && !this.maze[currRow][currCol].getRight()) { // checks right of current cell
                queue.add(new int[]{currRow, currCol + 1});
            }

            if((currRow + 1) < this.maze.length && !this.maze[currRow + 1][currCol].getVisited() && !this.maze[currRow][currCol].getBottom()) { // checks below current cell
                queue.add(new int[]{currRow + 1, currCol});
            }

            if((currCol - 1) >= 0 && !this.maze[currRow][currCol - 1].getVisited() && !this.maze[currRow][currCol - 1].getRight()) { // checks left of current cell
                queue.add(new int[]{currRow, currCol - 1});
            }
        }
        this.printMaze();
    }

    public static void main(String[] args) {
        MyMaze finishedMaze = makeMaze();
        finishedMaze.printMaze();
        finishedMaze.solveMaze();
    }
}
