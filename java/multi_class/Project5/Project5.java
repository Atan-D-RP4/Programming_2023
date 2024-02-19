package Project5;
import java.util.Scanner;


class Animals
{
        String name, food, home, sound;

        Animals()
        {
                System.out.println("Enter Valid Choice!");
        }

        Animals(String name, String food, String home, String sound)
        {
                this.name = name;
                this.food = food;
                this.home = home;
                this.sound = sound;
        }

        void display()
        {
                System.out.println("Animal Name: " + name + "\nPreferred Food: " + "\nHoused in: " + home + "\nSound: " + sound);
        }

}


class Project5
{
        public static void main(String args[])
        {
                System.out.println("Animal:");
                System.out.print("1. Cow\n2. Pig\n3. Horse\nEnter Choice: [1/2/3]");

                Scanner ip = new Scanner(System.in);
                int choice = ip.nextInt();
                Animals animal;

                switch(choice)
                {
                      case 1:
                        animal = new Animals("Cow", "Grass", "Barns", "Moooo");
                        break;
                      case 2:
                        animal = new Animals("Pig", "Veggie Stuff", "Yard", "Snork" );
                        break;
                      case 3:
                        animal = new Animals("Horse", "Carrots", "Stable", "Neigh");
                        break;

                      default:
                        animal = new Animals();
                }
                animal.display();
                ip.close();
        }
}
