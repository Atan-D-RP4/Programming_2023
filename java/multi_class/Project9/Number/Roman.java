package Number;

public class Roman
{

    public String roman;
    public int romanToInteger()
    {
        if (roman == null || roman.length() == 0)
        {
            System.out.println("Invalid Input Error!");
            System.exit(1);
        }
        int result = 0;
        int value = 0;
        for (int i = roman.length() - 1; i >= 0; i--)
        {
            char charNow = roman.charAt(i);
            int numValue = getNumValue(charNow);

            if (numValue  < value)
                result -= numValue;
            else
                result += numValue;
            value = numValue;
        }
        return result;
    }

    public int getNumValue(char r_num)
    {
        switch (r_num)
        {
            case 'I':
                    return 1;
            case 'V':
                    return 5;
            case 'X':
                    return 10;
            case 'L':
                    return 50;
            case 'C':
                    return 100;
            case 'D':
                    return 500;
            case 'M':
                    return 1000;
            default: System.out.println("Invalid Roman Numeral!");
                    System.exit(1);
        }
        return -1;
    }
}
