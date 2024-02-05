import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class SwingApplication extends JFrame {

    public SwingApplication()
    {
        super("Swing Application");

        // Create components
        JButton button = new JButton("Click Me");
        JTextField textField = new JTextField(20);
        JCheckBox checkBox = new JCheckBox("Check Me");
        JRadioButton radioButton = new JRadioButton("Radio Me");
        JComboBox<String> comboBox = new JComboBox<>(new String[] {"Option 1", "Option 2", "Option 3"});
        DefaultListModel<String> listModel = new DefaultListModel<>();
        System.out.println("Running");
        listModel.addElement("Item 1");
        listModel.addElement("Item 2");
        listModel.addElement("Item 3");
        JList<String> list = new JList<>(listModel);
        JSlider slider = new JSlider(JSlider.HORIZONTAL, 0, 100, 50);
        JTextArea textArea = new JTextArea(5, 20);

        // Set layout
        setLayout(new FlowLayout());

        // Add components to the frame
        add(button);
        add(textField);
        add(checkBox);
        add(radioButton);
        add(comboBox);
        add(new JScrollPane(list));
        add(slider);
        add(new JScrollPane(textArea));

        // Add ActionListener to the button
        button.addActionListener(new ActionListener() {
            @Override public void actionPerformed(ActionEvent e)
            {
                JOptionPane.showMessageDialog(SwingApplication.this, "Button Clicked!");
            }
        });

        // Set frame properties
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(400, 300);
        setLocationRelativeTo(null); // Center the frame
        setVisible(true);
        System.out.println("Running");

    }

    public static void main(String[] args)
    {
        SwingUtilities.invokeLater(new Runnable() {
            @Override public void run()
            {
                new SwingApplication();
            }
        });
    }
}
