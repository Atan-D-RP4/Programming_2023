import java.io.*;


class FileIO
{
    public static void main(String args[]) throws FileNotFoundException
    {
        int pe = 0, pi = 0;
        File sample = new File("sample.txt");
        FileInputStream fis = new FileInputStream(sample);
        byte byteArray[] = new byte[(int)sample.length()];

        try
        {
            fis.read(byteArray);
        }
        catch(IOException e)
        {
            System.out.println("File Excpetion");
        }

        String s = new String(byteArray);
        String data[] = s.split(" ");
        for (int i = 0; i < data.length; i++)
        {
            String sp = data[i];
            for (int j = 1; j < sp.length(); j++)
            {
                if (sp.substring(j - 1, j + 1).equals("pe") || sp.substring(j - 1, j + 1).equals("Pe"))
                {
                    pe++;
                    continue;
                }
                if (sp.substring(j - 1, j + 1).equals("pi") || sp.substring(j - 1, j + 1).equals("Pi"))
                {
                    pi++;
                    continue;
                }
            }
        }

        System.out.println("pe - no.of occurrences - " + pe);
        System.out.println("pi - no.of occurrences - " + pi);

        try
        {
            fis.close();
        }
        catch(IOException e)
        {
            System.out.println("File Excpetion");
        }

    }
}
