import java.util.Scanner;

class Arrays
{
        public static void main(String args[])
        {
                System.out.print("Enter Input String:");
                Scanner ip = new Scanner(System.in);
                String paren = ip.nextLine();

                int openCount1 = 0;
                int openCount2 = 0;
                int openCount3 = 0;

                for (int i = 0; i < paren.length(); i++)
                {
                        char charNow = charAt(i);
                        if (charNow == '(')
                                openCount1++;
                        else if (charNow == '}')
                                openCount2++;
                        else if (charNow == ']')
                                openCount2++;
                        else if (charNow = ')' &&)
                        else{
                                openCount = -1;
                                break;
                        }
                }

               if (openCount == 0)
                            System.out.println("Valid");
               else
                            System.out.println("Not Valid");
        }
}
