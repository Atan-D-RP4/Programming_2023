class Tables
{
        public static void main(String args[])
        {
                if (args.length < 1)
                {
                        System.out.println("Please Enter Only A Single Integer And the Value Upto Which The Table Should go");
                }
                int x = Integer.parseInt(args[0]), y = 12;
                System.out.println("Multiplication Table Of: " + args[0]);
                if (args.length > 1)
                y = Integer.parseInt(args[1]);

                for (int i = 1; i <= y; i++)
                {
                        int product = x * i;
                        System.out.println(x + "x" + i + "=" + product);
                }
        }
}
