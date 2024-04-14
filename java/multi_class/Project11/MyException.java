/*
Exception Handling
Input a mobile number and check the given number is valid mobile number or not.
● A valid mobile number is a combination of (0-9) digits of length exactly 10.

● If the given Number Exceeds length of 10 raise Invalid Mobile Number-
ArrayIndexOutofBounds Exception

● If the given Number less than the length of 10 raise Invalid Mobile Number –
LengthNotSufficientException
● If the given Number contain any character other than digit raise Invalid Mobile
Number –NumberFormatException
 */


import java.util.Scanner;

class InvalidMobileNumberException extends Exception {
    public InvalidMobileNumberException(String message) {
        super(message);
    }
}

public class MyException {

    public static void main(String[] args)
    {
        Scanner ip = new Scanner(System.in);

        System.out.println("Enter a mobile number:");
        String mobileNumber = ip.nextLine();

        try
        {
            validateMobileNumber(mobileNumber);
            System.out.println("The entered mobile number is valid.");
        }
        catch (InvalidMobileNumberException e)
        {
            System.out.println("Invalid Mobile Number: " + e.getMessage());
        }
        ip.close();
    }

    private static void validateMobileNumber(String mobileNumber) throws InvalidMobileNumberException {
        // Check for digits
        try {
            Long.parseLong(mobileNumber); // Try to parse the string as a long
        } catch (NumberFormatException e) {
            throw new InvalidMobileNumberException("NumberFormatException");
        }

        // Check for length
        if (mobileNumber.length() > 10) {
            throw new InvalidMobileNumberException("ArrayIndexOutOfBounds");
        } else if (mobileNumber.length() < 10) {
            throw new InvalidMobileNumberException("LengthNotSufficientException");
        }
        else
            return
    }
}
