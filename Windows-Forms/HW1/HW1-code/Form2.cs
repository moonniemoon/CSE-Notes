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
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            this.BackColor = Color.Cornsilk;

            textBox1.Text = Form1.user.ToString();
            textBox2.Text = Form1.consumed.ToString() + "  кВтч";
            textBox3.Text = Form1.result.ToString() + " лв";
        }
    }
}
