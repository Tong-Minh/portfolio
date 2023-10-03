// FractalDrawer class draws a fractal of a shape indicated by user input
import java.awt.Color; //for the color of the fractals
import java.util.Scanner; //for user input
import java.util.Random; //for randomization of fractal colors


public class FractalDrawer {
    private double totalArea=0;  // member variable for tracking the total area

    public FractalDrawer() {}  // contructor


    //TODO:
    // drawFractal creates a new Canvas object
    // and determines which shapes to draw a fractal by calling appropriate helper function
    // drawFractal returns the area of the fractal
    public double drawFractal(String type) { 
        boolean condition = true;
        boolean condition2 = true;
        Scanner myScanner = new Scanner(System.in);
        System.out.println("How many times will the pattern repeat? [Answer must be an integer greater than or equal to 0]"); //asks the user how many levels they want to recursively draw the fractal and assigns to n
        int n = myScanner.nextInt();

        while(condition2) { //checks if the user entered in a valid whole number >= 0
            if (n >= 0) {
                condition2 = false;
            } else {
                System.out.println("Invalid option for n, enter: How many times will the pattern repeat? [Must be an integer greater than or equal to 0]");
                n = myScanner.nextInt();
            }
        }

        while(condition) { //calls the draw fractal methods for each shape depending on user input and also checks if it was a valid input
            if (type.equalsIgnoreCase("Circle")) {
                condition = false;
                Canvas drawing = new Canvas(800,800);
                drawCircleFractal(100, 400, 400, Color.BLACK, drawing, n);
            } else if (type.equalsIgnoreCase("Triangle")) {
                condition = false;
                Canvas drawing = new Canvas(800,800);
                drawTriangleFractal(200, 200, 300, 500, Color.BLACK, drawing, n);
            } else if (type.equalsIgnoreCase("Rectangle")) {
                condition = false;
                Canvas drawing = new Canvas(800,800);
                drawRectangleFractal(200, 200, 300, 300, Color.BLACK, drawing, n);
            } else if (type.equalsIgnoreCase("Quit")) {
                condition = false;
            } else {
                System.out.println("Invalid option for shape, enter: [Circle], [Triangle], [Rectangle], or [Quit]");
                type = myScanner.nextLine();
            }
        }

        if (type.equalsIgnoreCase("Circle")) { //does the math for the circle's area
            totalArea = Math.round(n * 62831.85307);
            System.out.println("The total area drawn by the program for this fractal was: " + totalArea);
        } else if (type.equalsIgnoreCase("Triangle")) { //does the math for the triangle's area through a model I created
            double base = 0;
            totalArea = 0;
    
            for (int i = 0; i < n; i++) {
                base = Math.round(35000 + (base / (1.3333333333)));
            }
            totalArea = base;
            System.out.println("The total area drawn by the program for this fractal was: " + totalArea);
        } else if (type.equalsIgnoreCase("Rectangle")) { //does the math for the rectangle's area, mine is just a square
            totalArea = n * 20000;
            System.out.println("The total area drawn by the program for this fractal was: " + totalArea);
        }
        return 0.0;
    }


    //TODO:
    // drawTriangleFractal draws a triangle fractal using recursive techniques
    public String drawTriangleFractal(double width, double height, double x, double y, Color c, Canvas can, int level){        
        if (level <= 0) {
            return "";
        } else {
            Random rnd = new Random(); //Random color generator for each level of fractal
            Color randomColor = new Color(rnd.nextFloat(), rnd.nextFloat(), rnd.nextFloat());
            c = randomColor;

            Triangle mainTriangle  = new Triangle(x, y, width, height); // main triangle, each point of origin is at the bottom left of the triangle, every smaller version of the triangle is half the width/height and has its coordinites adjusted based off the origin
            mainTriangle.setColor(c);
            can.drawShape(mainTriangle);

            Triangle topTriangle  = new Triangle(x + (width / 4), y - height, width / 2, height / 2); 
            topTriangle.setColor(c);
            can.drawShape(topTriangle);

            Triangle rightTriangle  = new Triangle(x + width, y, width / 2, height / 2); 
            rightTriangle.setColor(c);
            can.drawShape(rightTriangle);

            Triangle leftTriangle  = new Triangle(x - (width / 2), y, width / 2, height / 2); 
            leftTriangle.setColor(c);
            can.drawShape(leftTriangle);
            
            //recursively branching out in each direction and drawing more fractals, subtracting a level until it reaches the base case of 0 each time
            return drawTriangleFractal(width / 2, height / 2, x + (width / 4), y - height, c, can, level - 1) + drawTriangleFractal(width / 2, height / 2, x + width, y, c, can, level - 1) + drawTriangleFractal(width / 2, height / 2, x - (width / 2), y, c, can, level - 1);
        }   
    }


    // TODO:
    // drawCircleFractal draws a circle fractal using recursive techniques
    public String drawCircleFractal(double radius, double x, double y, Color c, Canvas can, int level) { 
        if (level <= 0) {
            return "";
        } else {
            Random rnd = new Random(); //Random color generator for each level of fractal
            Color randomColor = new Color(rnd.nextFloat(), rnd.nextFloat(), rnd.nextFloat());
            c = randomColor;

            Circle mainCircle = new Circle(x, y, radius); // main circle, each point of origin is at the center of the circle, every smaller version of the circle is half the radius and has its coordinites adjusted based off the origin
            mainCircle.setColor(c);
            can.drawShape(mainCircle); 

            Circle rightCircle = new Circle((x + (1.5 * radius)), y, radius / 2);
            rightCircle.setColor(c);
            can.drawShape(rightCircle);

            Circle leftCircle = new Circle((x - (1.5 * radius)), y, radius / 2);
            leftCircle.setColor(c);
            can.drawShape(leftCircle);

            Circle topCircle = new Circle(x, (y + (1.5 * radius)), radius / 2);
            topCircle.setColor(c);
            can.drawShape(topCircle);

            Circle bottomCircle = new Circle(x, (y - (1.5 * radius)), radius / 2);
            bottomCircle.setColor(c);
            can.drawShape(bottomCircle);
            
            //recursively branching out in each direction and drawing more fractals, subtracting a level until it reaches the base case of 0 each time
            return drawCircleFractal(radius/2, (x + (1.5 * radius)), y, c, can, level - 1) + drawCircleFractal(radius/2, (x - (1.5 * radius)), y, c, can, level - 1) + drawCircleFractal(radius/2, x, (y + (1.5 * radius)), c, can, level - 1) + drawCircleFractal(radius/2, x, (y - (1.5 * radius)), c, can, level - 1);
        }   
    }


    //TODO:
    // drawRectangleFractal draws a rectangle fractal using recursive techniques
    public String drawRectangleFractal(double width, double height, double x, double y, Color c, Canvas can, int level) {
        if (level <= 0) {
            return "";
        } else {
            Random rnd = new Random(); //Random color generator for each level of fractal
            Color randomColor = new Color(rnd.nextFloat(), rnd.nextFloat(), rnd.nextFloat());
            c = randomColor;

            Rectangle mainRectangle = new Rectangle(x, y, width, height); // main rectangle (i made mine a square), each point of origin is at the top left of the rectangle, every smaller version of the rectangle is half the width/height and has its coordinites adjusted based off the origin
            mainRectangle.setColor(c);
            can.drawShape(mainRectangle);

            Rectangle topRightRectangle = new Rectangle(x + width, y - (width / 2), width / 2, height / 2);
            topRightRectangle.setColor(c);
            can.drawShape(topRightRectangle);

            Rectangle topLeftRectangle = new Rectangle(x - (width / 2), y - (width / 2), width / 2, height / 2);
            topLeftRectangle.setColor(c);
            can.drawShape(topLeftRectangle);

            Rectangle bottomRightRectangle = new Rectangle(x + width, y + width, width / 2, height / 2);
            bottomRightRectangle.setColor(c);
            can.drawShape(bottomRightRectangle);

            Rectangle bottomLeftRectangle = new Rectangle(x - (width / 2), y + width, width / 2, height / 2);
            bottomLeftRectangle.setColor(c);
            can.drawShape(bottomLeftRectangle);
            
            //recursively branching out in each direction and drawing more fractals, subtracting a level until it reaches the base case of 0 each time
            return drawRectangleFractal(width / 2, height / 2, x + width, y - (width / 2), c, can, level - 1) + drawRectangleFractal(width / 2, height / 2, x - (width / 2), y - (width / 2), c, can, level - 1) + drawRectangleFractal(width / 2, height / 2, x + width, y + width, c, can, level - 1) + drawRectangleFractal(width / 2, height / 2, x - (width / 2), y + width, c, can, level - 1);
        }   
    }

    
    //TODO:
    // main should ask user for shape input, and then draw the corresponding fractal.
    // should print area of fractal
    public static void main(String[] args){
        FractalDrawer fractal = new FractalDrawer();
        Scanner myScanner = new Scanner(System.in);
        System.out.println("What fractal would you like to draw? [Circle] [Triangle] [Rectangle] [Quit]"); // asking what they want to draw
        String action = myScanner.nextLine();
        
        if (action.equalsIgnoreCase("Quit")) { //In case the user wants to quit the program
            return;
        }

        fractal.drawFractal(action); //draws corresponding fractal and prints area all within the drawFractal Method
    }
}