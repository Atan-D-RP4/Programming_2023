import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.event.ActionListener;
import javax.swing.*;

public class Details extends Applet implements ActionListener
{
        JLabel l1, l2, l3, l4, l5;
        JTextField t1, t2, t3; JTextArea t4;
        JList lst; Scrollbar sb;
        JCheckbox cb1, cb2, cb3; JCheckboxGroup cbg;
        JButton b1;
        
        public void init()
        {
                l1 = new JLabel("Enter Your Name: ");
                l2 = new JLabel("Branch: ");
                l3 = new JLabel("Phone No.: ");
                l4 = new JLabel("Interested Subjects: ");
                l5 = new JLabel("Details: ");
                t1 = new JTextField(20);
                t2 = new JTextField(20);
                t3 = new JTextField(20);
                t4 = new JTextArea(4, 20);
                lst = new JList(5); 
                sb = new JScrollbar(); 
                cbg = new JCheckboxGroup();
                cb1 = new JCheckbox("C++", cbg, false); 
                cb2 = new JCheckbox("C#", cbg, false); 
                cb3 = new JCheckbox("C", cbg, false);
                lst.add("C"); 
                lst.add("C++"); 
                lst.add("C#"); 
                lst.add("Python"); 
                lst.add("Java");
                b1 = new JButton("Submit");
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
