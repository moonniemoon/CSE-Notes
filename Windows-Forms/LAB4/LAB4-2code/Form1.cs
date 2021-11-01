using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Upr4_2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button_calc_Click(object sender, EventArgs e)
        {
            string s, ss;
            double sum = 0;
            int br = 0;

            ss = "Checked items: \n";
            s = "You ordered: \n";
            
            if (radioButton_small.Checked)
            {
                sum += 9.25;
                s += "Small size \n";
            }
            else if (radioButton_medium.Checked)
            {
                sum += 11.50;
                s += "Medium size \n";
            }
            else if (radioButton_large.Checked)
            {
                sum += 13.75;
                s += "Large size \n";
            }
            else
            {
                MessageBox.Show("Please choose a size!");
            }

            if (radioButton_thin.Checked)
            {
                s += radioButton_thin.Text;
            }
            else if (radioButton_thick.Checked)
            {
                s += radioButton_thick.Text;
            }
            else
            {
                MessageBox.Show("Please choose a crust!");
            }


            if (checkBox1.Checked)
            {
                sum += 1.5;
                s += "\nWith extra cheese\n";
            }

            for (int i = 0; i < checkedListBox1.CheckedItems.Count; i++)
            {
                br++;
                sum += 1;
                ss += "Item " + (i + 1).ToString() + " = " + checkedListBox1.Items[i].ToString() + "\n";
            }

            richTextBox1.Text = s + "\n" + ss + "Total toppings: " + br + "\n Total: $" + sum; 

        }
    }
}
