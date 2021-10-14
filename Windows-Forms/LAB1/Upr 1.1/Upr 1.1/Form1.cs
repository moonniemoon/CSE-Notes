using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Upr_1._1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.BackColor = Color.Black;
            label1.Text = "Hello!";
            label1.Font = new Font("Arial", 14);
            label1.ForeColor = Color.White;
        }

        private void ChangeFontColor(object sender, EventArgs e)
        {
            if (sender is Button)
            {
                this.BackColor = (sender as Button).BackColor;
            }
        }

        private void button_red_Click(object sender, EventArgs e)
        {
            // this.BackColor = Color.Red;
            ChangeFontColor(sender, e);
        }

        private void button_blue_Click(object sender, EventArgs e)
        {
            // this.BackColor = Color.Blue;
            ChangeFontColor(sender, e);
        }

        private void button_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Hello there! You have pressed BUTTON!");
            button.Text = "My name changed!";
        }
    }
}
