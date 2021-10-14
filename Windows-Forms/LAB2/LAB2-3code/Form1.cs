using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Upr2_3
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void calc()
        {
            double a;
            double[,] matrix;

            matrix = new double[,]
            {
                {1, 0.333, 12, 0.0001893},
                {3, 1, 36, 0.0005682},
                {0.8341, 0.0278, 1, 1.57828E-5},
                {5280, 1760, 63360, 1}
            };
            
            if (textBox1.Text != "")
            {
                a = double.Parse(textBox1.Text);
                textBox_result.Text = (a * (matrix[comboBox_from.SelectedIndex, comboBox_to.SelectedIndex])).ToString();
            }
        
        }

        private void button_calc_Click(object sender, EventArgs e)
        {
            calc();
        }

        private void button_close_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button_refresh_Click(object sender, EventArgs e)
        {
            textBox1.Clear();
            textBox_result.Clear();
        }

        private void comboBox_from_SelectedIndexChanged(object sender, EventArgs e)
        {
            calc();
        }

        private void comboBox_to_SelectedIndexChanged(object sender, EventArgs e)
        {
            calc();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            comboBox_from.SelectedIndex = 0;
            comboBox_to.SelectedIndex = 0;
        }
    }
}
