using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace lab5_2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            string[] lines = System.IO.File.ReadAllLines("C:\\Users\\skaya\\Desktop\\CSE Stuff\\3rd Year\\СТ\\Програми\\Names.txt");
            
            foreach (string str in lines)
            {
                listBox1.Items.Add(str);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            listBox1.Items.Add(textBox1.Text);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            listBox1.Items.Remove(listBox1.SelectedItem);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            StreamWriter f = File.CreateText("C:\\Users\\skaya\\Desktop\\CSE Stuff\\3rd Year\\СТ\\Програми\\Names.txt");

            for (int i = 0; i < listBox1.Items.Count; i++)
            {
                f.WriteLine("{0}", listBox1.Items[i]);           // {0} e da izkara na vseki red po edin element
            }
            f.Close();
        }
    }
}
