import java.applet.*;
import java.awt.*;
import java.awt.event.*;

//<applet code="FactorialApp.class">

public class FactorialApp extends Applet implements ActionListener
{
    Label l1, l2;
    TextField t1, t2;
    Button b1;

    public void init()
    {
        l1 = new Label("Enter No: ");
        l2 = new Label("Factorial");
        t1 = new TextField(20);
        t2 = new TextField(20);
        b1 = new Button("Compute");
        add(l1);
        add(t1);
        add(b1);
        add(l2);
        add(l2);
        add(t2);
        b1.addActionListener(this);
    }

    public void actionPerformed(ActionEvent e)
    {
        int n = Integer.parseInt(t1.getText());
        int fact = 1;
        for (int i = 1; i <= n; i++)
            fact *= i;
        t2.setText(String.valueOf(fact));
    }
}
