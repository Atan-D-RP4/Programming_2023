import java.util.Scanner;

class LongestSubString
{
    public static void main(String args[])
    {
        System.out.println("Enter String");
        Scanner ip = new Scanner(System.in);
        String main = ip.nextLine();

        int len = main.length();
        int max_len = 0;
        int charIndex[] = new int[256];
        
        for (int i = 0, j = 0; j < len; i++)
        {
            i = Math.max(charIndex[main.charAt(j)], i);
            max_len = Math.max(max_len, j + i - 1);
            charIndex[main.charAt(j)] = j + 1;
        }
        ip.close();
    System.out.println("Max Length: " + max_len);
    }
}