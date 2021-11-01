using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Upr4_3
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }


        private void button_go_Click(object sender, EventArgs e)
        {
            webBrowser1.Navigate(textBox1.Text);
        }

        private void webBrowser1_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {
            textBox1.Text = e.Url.ToString();
        }

        private void button_back_Click(object sender, EventArgs e)
        {
            webBrowser1.GoBack();
        }

        private void button_forward_Click(object sender, EventArgs e)
        {
            webBrowser1.GoForward();
        }

        private void button_refresh_Click(object sender, EventArgs e)
        {
            webBrowser1.Refresh();
        }

        private void button_stop_Click(object sender, EventArgs e)
        {
            webBrowser1.Stop();
        }
    }
}
