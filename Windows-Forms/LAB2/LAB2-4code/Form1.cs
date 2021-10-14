using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Upr2_4
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void calc()
        {
            double w, h, s;
            w = hScrollBar1.Value;
            h = vScrollBar1.Value;
            s = h * w;

            textBox1.Text = w.ToString();
            textBox2.Text = h.ToString();
            textBox3.Text = s.ToString();
        }

        private void vScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            calc();
        }

        private void hScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            calc();
        }
    }
}
