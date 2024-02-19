class Sum
{
        public static void main(String args[])
        {
                int sum = 0;
                if (args.length < 2)
                {
                        System.out.println("Insufficent Command Line Arguements. Give more than 1");
                }
                for (int i = 0; i < args.length; sum += Integer.parseInt(args[i]));
                System.out.println("Sum: " + sum);
        }
}
