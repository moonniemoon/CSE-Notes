using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Upr1_2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button_plus_Click(object sender, EventArgs e)
        {
            double a, b;
            try
            {
                a = Double.Parse(textBox_a.Text);
                b = Double.Parse(textBox_b.Text);
                textBox_result.Text = (a + b).ToString();
            }
            catch
            {
                MessageBox.Show("Oops!");
                textBox_a.Clear();
                textBox_b.Clear();
            }
        }

        private void button_minus_Click(object sender, EventArgs e)
        {
            double a, b;
            try
            {
                a = Double.Parse(textBox_a.Text);
                b = Double.Parse(textBox_b.Text);
                textBox_result.Text = (a - b).ToString();
            }
            catch
            {
                MessageBox.Show("Oops!");
                textBox_a.Clear();
                textBox_b.Clear();
            }
        }

        private void button_multiply_Click(object sender, EventArgs e)
        {
            double a, b;
            try
            {
                a = Double.Parse(textBox_a.Text);
                b = Double.Parse(textBox_b.Text);
                textBox_result.Text = (a * b).ToString();
            }
            catch
            {
                MessageBox.Show("Oops!");
                textBox_a.Clear();
                textBox_b.Clear();
            }
        }

        private void button_divide_Click(object sender, EventArgs e)
        {
            double a, b;
            try
            {
                a = Double.Parse(textBox_a.Text);
                b = Double.Parse(textBox_b.Text);
                textBox_result.Text = (a / b).ToString();
            }
            catch
            {
                MessageBox.Show("Oops!");
                textBox_a.Clear();
                textBox_b.Clear();
            }
        }
    }
}
