package java;
public class CommandLineDetails
{
    public static void main(String args[])
    {
        if (args.length >= 4)
        {
            String name = args[0];
            int age = Integer.parseInt(args[1]);
            String country = args[2];
            String god = args[3];
            System.out.println("Name: " + name); 
            System.out.println("Age: " + age); 
            System.out.println("Country: " + country); 
            System.out.println("God: " + god); 
        }
        else
            System.out.println("Enter Details");
    }
}