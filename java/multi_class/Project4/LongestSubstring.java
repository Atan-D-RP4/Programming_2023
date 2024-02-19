import java.util.Scanner;

class LongestSubstring
{
    public static void main(String args[])
    {
        Scanner ip = new Scanner(System.in);
        String given = ip.nextLine();
        ip.close();
        int n = given.length();
        int maxLength = 0;
        int start = 0;
        int longestSubstringStart = 0;
        int charIndex[] = new int[256];

        for (int i = 0; i < n; i++)
        {
            start = Math.max(charIndex[given.charAt(i)], start);

            if (i - start + 1 > maxLength) {
                maxLength = i - start + 1;
                longestSubstringStart = start;
            }

            charIndex[given.charAt(i)] = i + 1; // Update the index of the character
        }

        String longestSubstring = given.substring(longestSubstringStart, longestSubstringStart + maxLength);
        System.out.println("Longest Substring: " + longestSubstring);
        System.out.println("Length of Longest Substring: " + maxLength);
    }
}
