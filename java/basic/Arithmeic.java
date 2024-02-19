import java.util.Scanner;

class Arithmetic
{
        public static void main(String args[])
        {
                if (args.length != 1)
                {
                        System.out.println("Choose An Arithmetic Operation: +, - , /, *, %");
                }

                char operator = args[0].charAt(0); int result, first, second;
                System.out.println("Enter Two Numbers: ");
                Scanner ip = new Scanner(System.in);
                first = ip.nextInt(); second = ip.nextInt();

                switch (operator)
                {
                        case '+':
                                result = first + second;
                                System.out.println("Sum Of " + first + " and " + second + " is " + result);
                                break;
                        case '-':
                                result = first - second;
                                System.out.println("Difference Between " + first + " and " + second + " is " + result);
                                break;
                        case '/':
                                result = first / second;
                                System.out.println("Quotient Of " + first + "/" + second + " is " + result);
                                break;
                        case '*':
                                result = first * second;
                                System.out.println("Product Of " + first + " and " + second + " is " + result);
                                break;
                        case '%':
                                result = first % second;
                                System.out.println("Remainder Of " + first + "/" + second + " is " + result);
                                break;
                        default:
                                System.out.println("Invalid Operator. Select Operator: +, - , /, *, %");
                                break;
                }
        }
}

