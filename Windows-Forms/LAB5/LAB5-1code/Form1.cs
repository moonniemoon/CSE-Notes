using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.VisualBasic;

namespace lab5_1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }


        int cLeft = 1;

        public void AddNewTextBox()
        {
            TextBox txt = new TextBox();    // Za da suzdadem nov buton, trqbva da suzdadem obekt ot textbox
            this.Controls.Add(txt);         // dobavqme textboxa kum kontrolite na formata

            // mqstoto kudeto se namira
            txt.Top = cLeft * 25;
            txt.Left = 60;
            txt.Text = "TextBox " + cLeft;
            cLeft++;
        }


        private void button1_Click(object sender, EventArgs e)
        {
            AddNewTextBox();
        }


        ListBox listbox1 = new ListBox();
        ListBox listbox2 = new ListBox();
        Button button2 = new Button(); 
        Button button3 = new Button();

        public void CreateButton()
        {
            this.Controls.Add(button2);
            button2.Size = new System.Drawing.Size(120, 30);
            button2.Location = new System.Drawing.Point(250, 10);
            button2.Text = "Create ListBox";
            button2.Click += new EventHandler(this.button2_Click);

            this.Controls.Add(button3);
            button3.Size = new System.Drawing.Size(120, 30);
            button3.Location = new System.Drawing.Point(250, 60);
            button3.Text = "Enter salary";
            button3.Click += new EventHandler(this.button3_Click);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            CreateButton();
        }

        public void CreateListBox()
        {
            this.Controls.Add(listbox1);
            listbox1.Size = new System.Drawing.Size(100, 100);
            listbox1.Location = new System.Drawing.Point(10, 10);
            listbox1.MultiColumn = true;
            listbox1.SelectionMode = SelectionMode.MultiExtended;

            this.Controls.Add(listbox2);
            listbox2.Size = new System.Drawing.Size(100, 100);
            listbox2.Location = new System.Drawing.Point(450, 10);
            listbox2.MultiColumn = true;
            listbox2.SelectionMode = SelectionMode.MultiExtended;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            CreateListBox();

            string[] lines = System.IO.File.ReadAllLines("C:\\Users\\skaya\\Desktop\\CSE Stuff\\3rd Year\\СТ\\Програми\\Names.txt");

            foreach (string str in lines)
            {
                listbox1.Items.Add(str);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            double salary = Double.Parse(Interaction.InputBox("Enter salary"));
            listbox2.Items.Add(salary);
        }
    }
}
