import java.util.Scanner;
import number.Roman;

class RomanToInt
{
    public static void main(String args[])
    {
        System.out.println("Enter Roman Numeral: ");
        Roman string = new Roman();
        Scanner ip = new Scanner(System.in);
        string.roman = ip.nextLine();
        int romanValue = string.romanToInt();
        System.out.println("Decimal Value: " + romanValue);
        ip.close();
    }
}