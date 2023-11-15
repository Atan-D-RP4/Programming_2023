package number;

public class Roman
{
    int result;
    int prevValue;
    public String roman;
    public int romanToInt()
    {
        if (roman == null || roman.length() == 0)
        {
            System.out.println("Invalid Argument");
        }    

        for (int i = (roman.length() - 1); i >= 0; i = i - 1)
        {
            char charNow = roman.charAt(i);
            int deciValue = getDeciValue(charNow);
            
            if (deciValue == -1)
            {
                System.out.println("Invalid Arguement");
                System.exit(1);
            }

            if(deciValue < prevValue)
            result = result - deciValue;
            else
            result = result - deciValue;
            
            prevValue = deciValue;
        }
        return result;
    }
    
    public int getDeciValue(char romanNum)
    {
        switch (romanNum)
        {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
            default :
                System.out.println("Invalid Argument: " + romanNum);
                System.exit(1);     
                return -1;           
        }
    }
}