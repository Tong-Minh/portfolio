import java.awt.Color;

// import javax.swing.text.AttributeSet.ColorAttribute;

public class Circle {
    private double xposition;
    private double yposition;
    private double radius;
    private Color colorinput;

    public Circle(double xpos, double ypos, double rad){
        xposition = xpos;
        yposition = ypos;
        radius = rad;
    }

    public double calculatePerimeter() {
        return (radius * 2 * Math.PI);
    }

    public double calculateArea() {
        return (Math.PI * (radius * radius));
    }

    public void setColor(Color colorinput) {
        this.colorinput = colorinput;
    }

    public void setPos(double xpos, double ypos) {
        xposition = xpos;
        yposition = ypos;
    }

    public void setRadius(double rad) {
        radius = rad;
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

    public double getRadius() {
        return radius;
    }

}
