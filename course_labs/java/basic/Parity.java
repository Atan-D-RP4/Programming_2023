class Parity
{
        public static void main(String args[])
        {
                if (args.length != 2)
                {
                        System.out.println("Enter Two Numbers");
                        return ;
                }

                int x = Integer.parseInt(args[0]), y = Integer.parseInt(args[1]);

                if (x > y)
                        System.out.println("Greatest Integer is: " + x);
                else
                        System.out.println("Greatest Integer is: " + y);
        }
}
