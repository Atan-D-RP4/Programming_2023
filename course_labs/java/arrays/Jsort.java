import java.util.Scanner;

class Jsort
{
    public static void main (String args[])
    {
        if (args.length != 1)
        {
            System.out.println("Usage: java Jsort [Array_size](integer)");
            return;
        }

        int size = Integer.parseInt(args[0]);
        int arr[] = new int[size];

        Scanner ip = new Scanner(System.in);
        for (int i = 0; i < size; i++)
        {
            arr[i] = ip.nextInt();
        }

        for (int i = 0; i < size - 1; i++)
        {
            int count = 0;
            for (int j = 0; j < size - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    count++;
                }
            }
            if (count == 0)
                break;
        }

        System.out.println("Sorted Order:");

        for (int i = 0; i < size; i++)
        {
            System.out.print(arr[i] + " ");
        }
        System.out.println();
        return;
    }
}
