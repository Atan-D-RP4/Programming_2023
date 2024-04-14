import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Enumeration;

public class Details extends JFrame implements ActionListener {
    private JLabel l1, l2, l3, l4, l5;
    private JTextField t1, t2, t3;
    private JTextArea t4;
    private JList<String> lst;
    private JCheckBox cb1, cb2, cb3;
    private ButtonGroup cbg;
    private JButton b1;

    public Details() {
        setTitle("Swing Application Example");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        l1 = new JLabel("Enter Your Name: ");
        l2 = new JLabel("Branch: ");
        l3 = new JLabel("Phone No.: ");
        l4 = new JLabel("Interested Subjects: ");
        l5 = new JLabel("Details: ");

        t1 = new JTextField(20);
        t2 = new JTextField(20);
        t3 = new JTextField(20);
        t4 = new JTextArea(4, 20);
        lst = new JList<>(new String[]{"C", "C++", "C#", "Python", "Java"});
        JScrollPane scrollPane = new JScrollPane(lst);

        cbg = new ButtonGroup();
        cb1 = new JCheckBox("C++");
        cb2 = new JCheckBox("C#");
        cb3 = new JCheckBox("C");

        cbg.add(cb1);
        cbg.add(cb2);
        cbg.add(cb3);

        b1 = new JButton("Submit");
        b1.addActionListener(this);

        setLayout(new GridLayout(8, 2));
        add(l1);
        add(t1);
        add(l2);
        add(t2);
        add(l3);
        add(t3);
        add(l4);
        add(scrollPane);
        add(new JLabel()); // Empty space
        add(cb1);
        add(cb2);
        add(cb3);
        add(l5);
        add(t4);
        add(b1);

        pack();
        setLocationRelativeTo(null);
        setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        String profile = "Profile: ";
        profile += "\nUsername: " + t1.getText();
        profile += "\nBranch: " + t2.getText();
        profile += "\nPhone No.: " + t3.getText();
        profile += "\nFavorite Subject: " + getSelectedCheckboxLabel();
        t4.setText(profile);
    }

    private String getSelectedCheckboxLabel() {
        Enumeration<AbstractButton> elements = cbg.getElements();
        while (elements.hasMoreElements()) {
            AbstractButton button = elements.nextElement();
            if (button.isSelected()) {
                return button.getText();
            }
        }
        return "";
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Details());
    }
}
