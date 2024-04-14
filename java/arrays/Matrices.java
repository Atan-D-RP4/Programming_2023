import java.util.Scanner;

class Matrices
{
    public static void main(String args[])
    {
        if (args.length != 2)
        {
            System.out.println("Usage: java Matrices [Rows(int)] [Columns(int)]");
            return;
        }

        int rows = Integer.parseInt(args[0]), columns = Integer.parseInt(args[1]), sum = 0;
        int matrix[][] = new int[rows][columns];

        Scanner ip = new Scanner(System.in);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                System.out.println("Matrix[" + (i + 1) + "][" + (j + 1) + "]:");
                matrix[i][j] = ip.nextInt();
                if (i == j)
                {
                    sum += matrix[i][j];
                }
            }
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
                System.out.print(matrix[i][j] + " ");
            System.out.println();
        }

        System.out.println("Diagonal Sum: " + sum);

    }
}
