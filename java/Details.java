package java;
import java.applet.*;
import java.awt.*;
import java.awt.event.*;

public class Details extends Applet implements ActionListener
{
        Label l1, l2, l3, l4, l5;
        TextField t1, t2, t3; TextArea t4;
        List lst; Scrollbar sb;
        Checkbox cb1, cb2, cb3; CheckboxGroup cbg;
        Button b1;
        
        public void init()
        {
                l1 = new Label("Enter Your Name: ");
                l2 = new Label("Branch: ");
                l3 = new Label("Phone No.: ");
                l4 = new Label("Interested Subjects: ");
                l5 = new Label("Details: ");
                t1 = new TextField(20);
                t2 = new TextField(20);
                t3 = new TextField(20);
                t4 = new TextArea(4, 20);
                lst = new List(5); 
                sb = new Scrollbar(); 
                cbg = new CheckboxGroup();
                cb1 = new Checkbox("C++", cbg, false); 
                cb2 = new Checkbox("C#", cbg, false); 
                cb3 = new Checkbox("C", cbg, false);
                lst.add("C"); 
                lst.add("C++"); 
                lst.add("C#"); 
                lst.add("Python"); 
                lst.add("ava");
                b1 = new Button("Submit");
                add(l1); add(t1);
                add(l2); add(t2);
                add(l3); add(t3);
                add(l4); add(lst);
                add(sb);
                add(cb1);
                add(cb2);
                add(cb3);
                add(l5); add(t4);
                add(b1); b1.addActionListener(this);
        }
        
        public void actionPerformed(ActionEvent e)
        {
                String profile = "Profile: ";
                profile = profile + "\nUsername: " + t1.getText();
                profile = profile + "\nBranch: " + t2.getText();
                profile = profile + "\nPhone No.: " + t3.getText();
                profile = profile + "\nFavorite Subject: " + cbg.getSelectedCheckbox().getLabel();
                t4.setText(profile);
        }
}
