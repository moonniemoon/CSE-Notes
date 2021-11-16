using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Homework1
{
    public partial class Form1 : Form
    { 
        // For Form2:
        public static int user, consumed; 
        public static double result; 

        public Form1()
        {
            InitializeComponent();
        }


        private void Form1_Load(object sender, EventArgs e)
        {
            this.BackColor = Color.Cornsilk;
        }


        private void groupBox1_Enter(object sender, EventArgs e)
        {
            int current, previous;

            if (textBox_user.Text != "" && textBox_new.Text != "" && textBox_old.Text != "")
            {
                user = Int32.Parse(textBox_user.Text);   // int32 max value = 2147483647 vs int16 max value = 32767
                current = Int32.Parse(textBox_new.Text);
                previous = Int32.Parse(textBox_old.Text);

                consumed = (current - previous);

                textBox_consumed.Text = consumed.ToString();
            }
            else
            {
                MessageBox.Show("There's an empty textbox!");
            }

        }


        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            result = consumed * 0.2 * 1.2;
            textBox_result.Text = result + " лв";
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            result = consumed * 0.5 * 1.2;
            textBox_result.Text = result + " лв";
        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            result = consumed * 0.75 * 1.2;
            textBox_result.Text = result + " лв";
        } 
        


        private void only_digits(object sender, KeyPressEventArgs e)
        {
            if (!Char.IsDigit(e.KeyChar) && e.KeyChar != (char)Keys.Back)
            {
                e.Handled = true;
                // ((TextBox)sender).Focus(); or (sender as TextBox).Focus();
            }
        }

        private void textBox_user_KeyPress(object sender, KeyPressEventArgs e) // i think the username is a number too. 
        {
            only_digits(sender, e);
        }

        private void textBox_new_KeyPress(object sender, KeyPressEventArgs e)
        {
            only_digits(sender, e);
        }

        private void textBox_old_KeyPress(object sender, KeyPressEventArgs e)
        {
            only_digits(sender, e);
        }


        private void потребенаЕлектроенергияToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form2 form2 = new Form2();
            form2.Show();
        }
        

        private void изходToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DialogResult result = MessageBox.Show("Do you really want to Exit?", "Hey!", MessageBoxButtons.YesNo);
            if (result == DialogResult.Yes)
                this.Close();
        }

    }
}
