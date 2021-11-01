using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Upr4_1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        public static string ReverseString(string s)
        {
            char[] arr = s.ToCharArray();    // arr -> masiv ot symboli

            Array.Reverse(arr);              // obrushtane na masiva

            return new string(arr);          // preobrazuva se masiva v string

        }

        private void button_palindrome_Click(object sender, EventArgs e)
        {
            string s1, s2;

            s1 = s2 = textBox1.Text;
            s1 = s1.ToLower();
            s2 = s2.ToLower();
            s1 = ReverseString(s1);

            if (s1 == s2)
            {
                MessageBox.Show("The text IS a palindrome!");
            }
            else
            {
                MessageBox.Show("The text is NOT a palindrome!");
            }
        }

        private void button_ascii_Click(object sender, EventArgs e)
        {
            string s1;
            int letter;

            s1 = textBox1.Text;

            foreach(var i in s1)   // for (int i = 0; i < s1.Length; i++)
            {
                letter = i;        // letter = s1[i];
                listBox1.Items.Add(letter);
            }
        }
    }
}
