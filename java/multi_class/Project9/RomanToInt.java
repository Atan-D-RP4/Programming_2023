import Number.*;

import java.util.Scanner;

class RomanToInt
{
    public static void main(String args[])
    {
        System.out.print("Enter Roman Numeral: ");
        Scanner ip = new Scanner(System.in);
        Roman numeral = new Roman();
        numeral.roman = ip.nextLine();
        ip.close();
        int num_int = numeral.romanToInteger();
        System.out.println("Integer Value of " + numeral.roman + " is " + num_int);
    }

}
