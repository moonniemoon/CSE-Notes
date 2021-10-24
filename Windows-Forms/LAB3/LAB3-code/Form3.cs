using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace upr_3._1
{
    public partial class Form3 : Form
    {
        public Form3()
        {
            InitializeComponent();
        }

        private void button_Calc_Click(object sender, EventArgs e)
        {
            double a, b, result;
            try
            {
                a = Double.Parse(textBox_A.Text);
                b = Double.Parse(textBox_B.Text);

                if (radioButton1.Checked)
                {
                    result = Math.Pow((a + b), 2);
                    textBox_result.Text = result.ToString();
                }
                else if (radioButton2.Checked)
                {
                    result = Math.Pow((a - b), 2);
                    textBox_result.Text = result.ToString();
                }
                else if (radioButton3.Checked)
                {
                    result = (a + b) * (a - b);
                    textBox_result.Text = result.ToString();
                }
                else if (radioButton4.Checked)
                {
                    result = Math.Pow((a + b), 3);
                    textBox_result.Text = result.ToString();
                }
                else if (radioButton5.Checked)
                {
                    result = Math.Pow(a, 3) + Math.Pow(b, 3);
                    textBox_result.Text = result.ToString();
                }
                else if (radioButton5.Checked)
                {
                    result = Math.Pow(a, 3) - Math.Pow(b, 3);
                    textBox_result.Text = result.ToString();
                }
                else
                {
                    MessageBox.Show("You have not checked a radio button!");
                }

            }
            catch
            {
                MessageBox.Show("Oops!");
            }
        }

        private void button_clear_Click(object sender, EventArgs e)
        {
            textBox_A.Clear();
            textBox_B.Clear();
            textBox_result.Clear();
        }

        private void button_menu_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    
    }
}
