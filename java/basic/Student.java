import java.util.Scanner;

class Student
{
        public static void main(String args[])
        {
                System.out.println("Enter Marks: ");
                Scanner s = new Scanner(System.in);
                int n = s.nextInt(), m = s.nextInt(), l = s.nextInt();
                int sum = n + m + l, average = sum / 3;
                s.close();

                System.out.println("Length: " + args.length);
                System.out.println("Your Details are: \nName\tRno\tBranch\tCGPA");
                for (int i = 0; i < args.length; i++)
                {
                        System.out.print(args[i] + "\t");
                }
                System.out.print("\n");

                System.out.println("Marks\tMarks\tMarks");
                System.out.println(n + "\t" + m + "\t" + l);
                System.out.println("Sum: " + sum + " \tAverage : " + average);
        }
}
