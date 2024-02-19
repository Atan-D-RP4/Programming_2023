// Define an interface
interface Shape {
    double calculateArea(); // Abstract method
    void display(); // Abstract method
}

// Define an abstract class implementing the Shape interface
abstract class AbstractShape implements Shape {
    String name;

    // Constructor
    public AbstractShape(String name) {
        this.name = name;
    }

    // Concrete method in the abstract class
    void printName() {
        System.out.println("Shape: " + name);
    }
}

// Implement the Shape interface with a concrete class
class Circle extends AbstractShape {
    double radius;

    // Constructor
    public Circle(String name, double radius) {
        super(name);
        this.radius = radius;
    }

    // Implement abstract method from the Shape interface
    @Override
    public double calculateArea() {
        return Math.PI * radius * radius;
    }

    // Implement abstract method from the Shape interface
    @Override
    public void display() {
        System.out.println("Circle Display: Radius = " + radius);
    }
}

// Implement the Shape interface with another concrete class
class Rectangle extends AbstractShape {
    double length;
    double width;

    // Constructor
    public Rectangle(String name, double length, double width) {
        super(name);
        this.length = length;
        this.width = width;
    }

    // Implement abstract method from the Shape interface
    @Override
    public double calculateArea() {
        return length * width;
    }

    // Implement abstract method from the Shape interface
    @Override
    public void display() {
        System.out.println("Rectangle Display: Length = " + length + ", Width = " + width);
    }
}

public class ShapeExample {
    public static void main(String[] args) {
        // Create instances of concrete classes
        Circle circle = new Circle("Circle", 5.0);
        Rectangle rectangle = new Rectangle("Rectangle", 4.0, 6.0);

        // Call methods on instances
        circle.printName();
        circle.display();
        System.out.println("Circle Area: " + circle.calculateArea());

        System.out.println();

        rectangle.printName();
        rectangle.display();
        System.out.println("Rectangle Area: " + rectangle.calculateArea());
    }
}
