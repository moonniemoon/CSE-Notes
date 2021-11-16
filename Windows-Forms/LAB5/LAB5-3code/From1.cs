using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Text.RegularExpressions;

namespace lab5_3
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            if (!Regex.IsMatch(textBox1.Text, "^[А-Я]{1,}"))
                MessageBox.Show("Write in cyrillic with first letter in uppercase!");
            
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            if (!Regex.IsMatch(textBox2.Text, "^[А-Я]{1,}"))
                MessageBox.Show("Write in cyrillic with first letter in uppercase!");
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            if (!Regex.IsMatch(textBox3.Text, "^[А-Я]{1,}"))
                MessageBox.Show("Write in cyrillic with first letter in uppercase!");
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            if (!Regex.IsMatch(richTextBox1.Text, "^[а-я]{1,}"))
                MessageBox.Show("Write in cyrillic!");

        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {
            if (!Regex.IsMatch(textBox4.Text, "^[0-9]{1,10}"))
                MessageBox.Show("Only numbers! (1 - 10)");

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            toolStripStatusLabel2.Text = System.DateTime.Today.ToLongDateString();
            timer1.Start();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            toolStripStatusLabel3.Text = System.DateTime.Now.ToShortTimeString();
        }

        private void textBox1_MouseHover(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = "Въведи име на кирилица!";
        }

        private void textBox2_MouseHover(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = "Въведи презиме!";
        }

        private void textBox3_MouseHover(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = "Въведи фамилия!";
        }

        private void textBox4_MouseHover(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = "Въведи ЕГН!";
        }

        private void richTextBox1_MouseHover(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = "Въведи Адрес!";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = textBox1.Text + " " + textBox3.Text;
            Form2 form2 = new Form2();
            form2.Show();
        }
    }
}
