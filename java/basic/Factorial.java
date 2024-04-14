import java.util.Scanner;

class Factorial
{
        public static void main(String args[])
        {
                System.out.println("Enter Number: ");
                Scanner s = new Scanner(System.in);
                int n = s.nextInt(), fact = 1;

                for (int i = 1; i <= n; i++)
                {
                        fact *= i;
                }

                System.out.println("Factorial of " + n + " is: " + fact);

        }
}
