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
using Microsoft.VisualBasic;

namespace lab6_1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }


        public static Boolean IsNumeric(string strToTest)
        {
            int result;

            if (int.TryParse(strToTest, out result))    // try-parse proverqva dali moje da se parse-ne promenlivata, i da q vkara kato rezultat 
                                                        // v promenlivata result
                return true;
            else return false;                          // ako ne uspee, znache ne e integer
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "" && textBox2.Text == "")
            {
                errorProvider1.SetError(textBox1, "Fields must be filled!");
                errorProvider1.SetError(textBox2, "Fields must be filled!");
            }
            else
            {
                errorProvider1.Clear();

                if (IsNumeric(textBox1.Text))
                {
                    errorProvider1.SetError(textBox1, "Input must be string!");
                }
                else
                {
                    errorProvider1.SetError(textBox1, "");
                }


                if (IsNumeric(textBox2.Text))
                {
                    errorProvider1.SetError(textBox1, "");
                }
                else
                {
                    errorProvider1.SetError(textBox1, "Input must be number!");
                }

            }
        }



        int invalidInput1 = 0;
        int invalidInput2 = 0;
        int invalidInput3 = 0;

        private void textBox5_KeyPress(object sender, KeyPressEventArgs e)
        {
            Regex rgx;
            rgx = new Regex(@"\S+@\S+\.\S");  // s = vsichko ot klaviaturata bez prazno mqsto

            if (rgx.IsMatch(textBox5.Text))
            {
                errorProvider1.SetError(textBox5, "");
                invalidInput3 = 0;
            }
            else
            {
                errorProvider1.SetError(textBox5, "Not a valid email!");
                invalidInput3 = 1;
            }    
        }


        private void textBox3_Validating(object sender, CancelEventArgs e) // shte proverqva samo dali sa prazni ili ne texttovite poleta
        {
            if (textBox3.Text == "")
            {
                errorProvider1.SetError(textBox3, "You must enter a first name!");
                invalidInput1 = 1;

            }
            else
            {
                errorProvider1.SetError(textBox3, "");
                invalidInput1 = 0;
            }
        }

        private void textBox4_Validating(object sender, CancelEventArgs e)
        {
            if (textBox4.Text == "")
            {
                errorProvider1.SetError(textBox4, "You must enter a first name!");
                invalidInput2 = 1;
            }
            else
            {
                errorProvider1.SetError(textBox4, "");
                invalidInput2 = 0;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (invalidInput1 == 1 && invalidInput2 == 1 && invalidInput3 == 1)
            {
                Application.Exit();
            }
            else
            {
                MessageBox.Show(invalidInput1 + " " + invalidInput2 + " " + invalidInput3);
            }
        }



        private void textBox6_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != '-' && e.KeyChar != ',')
            {
                e.Handled = true;
                textBox6.Focus();
            }

            if (e.KeyChar == ',' && (sender as TextBox).Text.IndexOf(',') > -1)
            {
                e.Handled = true;
            }

            if (e.KeyChar == '-' && textBox6.Text.Length > 1)
            {
                e.Handled = true;
            }
        }

        private void textBox7_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsDigit(e.KeyChar) && !char.IsControl(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        private void textBox8_KeyPress(object sender, KeyPressEventArgs e)
        {
            for (int i = 58; i <= 127; i++)
            {
                if (e.KeyChar == i)
                {
                    e.Handled = true;
                }
            }

            for (int i = 32; i <= 47; i++)
            {
                if (e.KeyChar == i)
                {
                    e.Handled = true;
                }
            }
        }




        private void textBox9_TextChanged(object sender, EventArgs e)
        {
            if (Regex.IsMatch(textBox9.Text, "[^0-9]"))  // ako se pishe vs drugo no ne i chislata, syobshtenie 
            {
                MessageBox.Show("Please enter only numbers!");
                textBox9.Text = textBox9.Text.Remove(textBox9.Text.Length - 1);   // mahame posledniq vuveden simvol 
                
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string expression = "^[0-9a-zA-Z]([-\\.\\w]*[0-9a-zA-Z])*@([0-9a-zA-Z][-\\w]*[0-9a-zA-Z]\\.)+[a-zA-Z]{2,9}$";  
            
            if (Regex.IsMatch(textBox10.Text, expression))
            {
                MessageBox.Show("Valid email!");
            }
            else
                MessageBox.Show("Not a valid email!");
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (Information.IsDate(textBox11.Text))
            {
                MessageBox.Show(textBox11.Text + " is a valid date " + Information.IsDate(textBox11.Text));
            }
            else
                MessageBox.Show(textBox11.Text + " is not a valid date " + Information.IsDate(textBox11.Text));
        }
    }
}
