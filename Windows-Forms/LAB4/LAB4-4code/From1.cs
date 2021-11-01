using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Upr4_4
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int month, year;
            DateTime dd = new DateTime();
            dd = DateTime.Parse(dateTimePicker1.Text);

            // month = Int16.Parse(textBox1.Text);
            // year = Int16.Parse(textBox2.Text);

            month = dd.Month;
            year = dd.Year;

            if (year > 1900 && month <= 12)
            {
                string Message = "Month: " + month + " Year: " + year;
                string Message1 = "30 days ";
                string Message2 = "31 days ";
                string Message3 = "29 days ";
                string Message4 = "28 days ";

                switch (month)
                {
                    case 1: MessageBox.Show(Message + "\n" + Message2); break;
                    case 5: MessageBox.Show(Message + "\n" + Message2); break;
                    case 7: MessageBox.Show(Message + "\n" + Message2); break;
                    case 8: MessageBox.Show(Message + "\n" + Message2); break;
                    case 10: MessageBox.Show(Message + "\n" + Message2); break;
                    case 12: MessageBox.Show(Message + "\n" + Message2); break;

                    case 4: MessageBox.Show(Message + "\n" + Message1); break;
                    case 6: MessageBox.Show(Message + "\n" + Message1); break;
                    case 9: MessageBox.Show(Message + "\n" + Message1); break;
                    case 11: MessageBox.Show(Message + "\n" + Message1); break;

                    case 2:
                        if (DateTime.IsLeapYear(year))
                            MessageBox.Show("Leap year!" + "\n" + Message4);                        
                        else                      
                            MessageBox.Show("NOT a leap year!" + "\n" + Message3);
                        break;
                }
            }
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!Char.IsDigit(e.KeyChar) && e.KeyChar != (char)Keys.Back)
            {
                e.Handled = true;
                textBox1.Focus();
            }
        }

        private void textBox2_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!Char.IsDigit(e.KeyChar) && e.KeyChar != (char)Keys.Back)
            {
                e.Handled = true;
                textBox2.Focus();
            }
        }
    }
}
