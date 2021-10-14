using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Upr2_2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void comboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            double fah, cel;
            try
            {
                if (textBox.Text != " ")
                {
                    if (comboBox.Text == "C")
                    {
                        cel = Double.Parse(textBox.Text);
                        fah = (cel * 9) / 5 + 32;
                        textBox_result.Text = fah.ToString();
                    }
                    else
                    {
                        fah = Double.Parse(textBox.Text);
                        cel = (fah - 32) * 5 / 9;
                        textBox_result.Text = cel.ToString();
                    }
                }
            }
            catch
            {
                MessageBox.Show("Oops!");
            }
        }
    }
}
