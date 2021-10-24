using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace upr_3._1
{
    public partial class Form4 : Form
    {

        static Random random = new Random();
        private int randomNum = random.Next(99) + 1;   // 0 - 100

        public Form4()
        {
            InitializeComponent();
        } 


        private void button1_Click(object sender, EventArgs e)
        {
            int num;
            num = Int16.Parse(textBox1.Text);

            if (randomNum < num)
            {
                label2.Text = "The comps num is smaller!";
            }
            else if (randomNum > num)
            {
                label2.Text = "The comps num is bigger!";
            }
            else if (randomNum == num)
            {
                label2.Text = "CONGRATS!";
                timer1.Stop();
            }
            else
            {
                MessageBox.Show("Oops!");
            }
        }


        private int t;
        private void timer1_Tick(object sender, EventArgs e)
        {
            t++;
            label3.Text = t.ToString();
        }

        private void Form4_Load(object sender, EventArgs e)
        {
            timer1.Start();
        }
    }
}
