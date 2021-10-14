
namespace Upr_1._1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.button_red = new System.Windows.Forms.Button();
            this.button_blue = new System.Windows.Forms.Button();
            this.button = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(356, 34);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(86, 29);
            this.label1.TabIndex = 0;
            this.label1.Text = "LABEL";
            // 
            // button_red
            // 
            this.button_red.BackColor = System.Drawing.Color.Firebrick;
            this.button_red.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button_red.ForeColor = System.Drawing.Color.White;
            this.button_red.Location = new System.Drawing.Point(84, 82);
            this.button_red.Name = "button_red";
            this.button_red.Size = new System.Drawing.Size(163, 282);
            this.button_red.TabIndex = 1;
            this.button_red.Text = "RED";
            this.button_red.UseVisualStyleBackColor = false;
            this.button_red.Click += new System.EventHandler(this.button_red_Click);
            // 
            // button_blue
            // 
            this.button_blue.BackColor = System.Drawing.Color.SkyBlue;
            this.button_blue.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button_blue.ForeColor = System.Drawing.Color.White;
            this.button_blue.Location = new System.Drawing.Point(547, 82);
            this.button_blue.Name = "button_blue";
            this.button_blue.Size = new System.Drawing.Size(163, 282);
            this.button_blue.TabIndex = 2;
            this.button_blue.Text = "BLUE";
            this.button_blue.UseVisualStyleBackColor = false;
            this.button_blue.Click += new System.EventHandler(this.button_blue_Click);
            // 
            // button
            // 
            this.button.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button.Location = new System.Drawing.Point(313, 152);
            this.button.Name = "button";
            this.button.Size = new System.Drawing.Size(163, 143);
            this.button.TabIndex = 3;
            this.button.Text = "BUTTON";
            this.button.UseVisualStyleBackColor = true;
            this.button.Click += new System.EventHandler(this.button_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.button);
            this.Controls.Add(this.button_blue);
            this.Controls.Add(this.button_red);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button_red;
        private System.Windows.Forms.Button button_blue;
        private System.Windows.Forms.Button button;
    }
}

