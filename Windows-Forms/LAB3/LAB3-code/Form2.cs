using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace upr_3._1
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void button_calc_Click(object sender, EventArgs e)
        {
            double a, b, result;
            try
            {
                a = Double.Parse(textBox_a.Text);
                b = Double.Parse(textBox_n.Text);

                result = Math.Pow(a, b);
                textBox_result.Text = result.ToString();
            }
            catch
            {
                MessageBox.Show("Oops!");
            }
        }

        private void button_clean_Click(object sender, EventArgs e)
        {
            textBox_a.Clear();
            textBox_n.Clear();
            textBox_result.Clear();
        }

        private void button_menu_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
