// This Java Class illustrates Method Overloading and 'this' reference for members
// and the passing of Parameters to methods
import java.util.Scanner;

class Student
{
    int roll_no; String name, branch;

    Student()
    {
        System.out.println("Default Constructor is Called");
    }

    Student(int roll, String naame, String braanch)
    {
        roll_no = roll;
        name = naame;
        branch = braanch;
    }

    void accept()
    {
        System.out.println("Enter Details:");
        Scanner ip = new Scanner(System.in);
        System.out.println("Roll No.: "); roll_no = ip.nextInt();
        System.out.println("Name: "); name = ip.nextLine();
        System.out.println("Branch: "); branch = ip.nextLine();
        ip.close();
    }
    void accept(int roll_no, String name, String branch)
    {
        this.roll_no = roll_no;
        this.name = name;           // this reference
        this.branch = branch;
    }
    void display()
    {
        System.out.println("Roll No: " + roll_no + "\nName: " + name + "\nBranch: " + branch);
    }

    static void iSee()
    {
        System.out.println("So this is how static method like main work");
    }
}

class Super extends Student
{
    Super()
    {
        System.out.println("Hello. If you see me, may God Bless You");
    }
}

class Test1
{
    public static void main(String args[])
    {
        Student s1 = new Student();                     // Constructor
        Student s2 = new Student(144, "CSE", "Chaitanya");  // Overloading
        s1.accept(124, "Ramesh", "ECE");    // Method
        s2.accept();                        // Overloading
        s1.display();
        s2.display();
        Student.iSee();
        Super s3 = new Super();
        s3.display();
    }
}
