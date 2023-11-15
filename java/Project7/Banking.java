class RBI
{
    int minInterestRate, minAllowedBalance, maxWithdrawLimit; 
    RBI (int x, int y, int z)
    {
        minInterestRate = x;
        minAllowedBalance = y;
        maxWithdrawLimit = z;
    }
}

class Customer
{
    String name;
    int CId;

}

class  Account
{
    int AccNo, Balance;
}


class ICICI extends RBI
{

}

class SBI extends RBI
{

}

class PNB extends RBI
{

}

class Banking
{
    public static void main(String args[])
    {

    }
}