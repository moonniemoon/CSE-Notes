using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Upr2_1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button_calc_Click(object sender, EventArgs e)
        {
            double a, b, c, x1, x2, d;
            try
            {
                a = Double.Parse(textBox_a.Text);
                b = Double.Parse(textBox_b.Text);
                c = Double.Parse(textBox_c.Text);

                d = Math.Pow(b, 2) - 4 * a * c;

                if (d >= 0)
                {
                    x1 = (-b + Math.Sqrt(d)) / (2 * a);
                    x2 = (-b - Math.Sqrt(d)) / (2 * a);
                    textBox_x1.Text = x1.ToString();
                    textBox_x2.Text = x2.ToString();
                }
                else
                {
                    MessageBox.Show("Oops! There are no real number solutions!");
                }
            }
            catch
            {
                MessageBox.Show("Oops! Something went wrong, try again!");
                textBox_a.Clear();
                textBox_b.Clear();
                textBox_c.Clear();
            }
        }
    }
}
