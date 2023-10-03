import java.awt.Color;

public class Rectangle {
    private double xposition;
    private double yposition;
    private Color colorinput;
    private double width;
    private double height;

    public Rectangle(double xpos, double ypos, double width, double height){
        xposition = xpos;
        yposition = ypos;
        this.width = width;
        this.height = height;
    }

    public double calculatePerimeter() {
        return (width * 2 + height * 2);
    }

    public double calculateArea() {
        return (width * height);
    }

    public void setColor(Color colorinput) {
        this.colorinput = colorinput;
    }

    public void setPos(double xpos, double ypos) {
        xposition = xpos;
        yposition = ypos;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    public void setWidth(double width) {
        this.width = width;
    }

    public Color getColor() {
        return colorinput;
    }

    public double getXPos() {
        return xposition;
    }

    public double getYPos() {
        return yposition;
    }

    public double getHeight() {
        return height;
    }

    public double getWidth() {
        return width;
    }
}


