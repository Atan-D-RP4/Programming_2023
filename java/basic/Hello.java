import java.util.*;
class Hello
{
   public static void main(String args[])
        {
                float temperature;

                System.out.println("Hello Welcome to Java Programming");

                Scanner in = new  Scanner(System.in);

                System.out.println("Enter te                                                                                                                                                                                                  mperature in Fahrenheit");

                temperature = in.nextInt();
                temperature = ((temperature - 32)*5)/9;
                in.close();

                System.out.println("temperature in Celsius = " + temperature);
        }
}
