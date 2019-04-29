namespace RegexHelper
{
    partial class mainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose( bool disposing )
        {
            if( disposing && ( components != null ) )
            {
                components.Dispose();
            }
            base.Dispose( disposing );
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.findNext = new System.Windows.Forms.Button();
            this.findPrev = new System.Windows.Forms.Button();
            this.regexText = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.errorLabel = new System.Windows.Forms.Label();
            this.caseSensitive = new System.Windows.Forms.CheckBox();
            this.rawText = new System.Windows.Forms.RichTextBox();
            this.outputText = new System.Windows.Forms.RichTextBox();
            this.replaceText = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // findNext
            // 
            this.findNext.ForeColor = System.Drawing.Color.Black;
            this.findNext.Location = new System.Drawing.Point(620, 462);
            this.findNext.Name = "findNext";
            this.findNext.Size = new System.Drawing.Size(75, 23);
            this.findNext.TabIndex = 6;
            this.findNext.Text = "Find Next";
            this.findNext.UseVisualStyleBackColor = true;
            this.findNext.Click += new System.EventHandler(this.findNext_Click);
            // 
            // findPrev
            // 
            this.findPrev.ForeColor = System.Drawing.Color.Black;
            this.findPrev.Location = new System.Drawing.Point(539, 462);
            this.findPrev.Name = "findPrev";
            this.findPrev.Size = new System.Drawing.Size(75, 23);
            this.findPrev.TabIndex = 5;
            this.findPrev.Text = "Find Prev";
            this.findPrev.UseVisualStyleBackColor = true;
            this.findPrev.Click += new System.EventHandler(this.findPrev_Click);
            // 
            // regexText
            // 
            this.regexText.BackColor = System.Drawing.Color.White;
            this.regexText.ForeColor = System.Drawing.Color.Black;
            this.regexText.Location = new System.Drawing.Point(57, 463);
            this.regexText.Name = "regexText";
            this.regexText.Size = new System.Drawing.Size(476, 20);
            this.regexText.TabIndex = 2;
            this.regexText.TextChanged += new System.EventHandler(this.regexText_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(14, 466);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(38, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Regex";
            // 
            // errorLabel
            // 
            this.errorLabel.AutoSize = true;
            this.errorLabel.ForeColor = System.Drawing.Color.Red;
            this.errorLabel.Location = new System.Drawing.Point(159, 519);
            this.errorLabel.Name = "errorLabel";
            this.errorLabel.Size = new System.Drawing.Size(72, 13);
            this.errorLabel.TabIndex = 6;
            this.errorLabel.Text = "Invalid Regex";
            this.errorLabel.Visible = false;
            // 
            // caseSensitive
            // 
            this.caseSensitive.AutoSize = true;
            this.caseSensitive.Checked = true;
            this.caseSensitive.CheckState = System.Windows.Forms.CheckState.Checked;
            this.caseSensitive.ForeColor = System.Drawing.SystemColors.Window;
            this.caseSensitive.Location = new System.Drawing.Point(57, 518);
            this.caseSensitive.Name = "caseSensitive";
            this.caseSensitive.Size = new System.Drawing.Size(96, 17);
            this.caseSensitive.TabIndex = 4;
            this.caseSensitive.Text = "Case Sensitive";
            this.caseSensitive.UseVisualStyleBackColor = true;
            this.caseSensitive.CheckedChanged += new System.EventHandler(this.caseSensitive_CheckedChanged);
            // 
            // rawText
            // 
            this.rawText.BackColor = System.Drawing.Color.Black;
            this.rawText.ForeColor = System.Drawing.Color.White;
            this.rawText.Location = new System.Drawing.Point(13, 13);
            this.rawText.Name = "rawText";
            this.rawText.Size = new System.Drawing.Size(601, 436);
            this.rawText.TabIndex = 0;
            this.rawText.Text = "";
            this.rawText.TextChanged += new System.EventHandler(this.rawText_TextChanged_1);
            // 
            // outputText
            // 
            this.outputText.BackColor = System.Drawing.Color.Black;
            this.outputText.ForeColor = System.Drawing.Color.White;
            this.outputText.Location = new System.Drawing.Point(620, 13);
            this.outputText.Name = "outputText";
            this.outputText.ReadOnly = true;
            this.outputText.Size = new System.Drawing.Size(601, 436);
            this.outputText.TabIndex = 1;
            this.outputText.Text = "";
            // 
            // replaceText
            // 
            this.replaceText.BackColor = System.Drawing.Color.White;
            this.replaceText.ForeColor = System.Drawing.Color.Black;
            this.replaceText.Location = new System.Drawing.Point(57, 489);
            this.replaceText.Name = "replaceText";
            this.replaceText.Size = new System.Drawing.Size(476, 20);
            this.replaceText.TabIndex = 3;
            this.replaceText.TextChanged += new System.EventHandler(this.replaceText_TextChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.ForeColor = System.Drawing.Color.White;
            this.label2.Location = new System.Drawing.Point(5, 492);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(47, 13);
            this.label2.TabIndex = 11;
            this.label2.Text = "Replace";
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Black;
            this.ClientSize = new System.Drawing.Size(1235, 546);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.replaceText);
            this.Controls.Add(this.outputText);
            this.Controls.Add(this.rawText);
            this.Controls.Add(this.caseSensitive);
            this.Controls.Add(this.errorLabel);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.regexText);
            this.Controls.Add(this.findPrev);
            this.Controls.Add(this.findNext);
            this.ForeColor = System.Drawing.Color.White;
            this.Name = "mainForm";
            this.Text = "Regex Helper";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button findNext;
        private System.Windows.Forms.Button findPrev;
        private System.Windows.Forms.TextBox regexText;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label errorLabel;
        private System.Windows.Forms.CheckBox caseSensitive;
        private System.Windows.Forms.RichTextBox rawText;
        private System.Windows.Forms.RichTextBox outputText;
        private System.Windows.Forms.TextBox replaceText;
        private System.Windows.Forms.Label label2;
    }
}

