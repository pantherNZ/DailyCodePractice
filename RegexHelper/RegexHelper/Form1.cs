using System;
using System.Windows.Forms;
using System.Text.RegularExpressions;
using System.Text;

namespace RegexHelper
{
    public partial class mainForm : Form
    {
        private int selectedIndex = 0;
        private int modifying = 0;
        private MatchCollection matches;

        public mainForm()
        {
            InitializeComponent();
        }

        private void rawText_TextChanged_1( object sender, EventArgs e ) { Process(); }
        private void regexText_TextChanged( object sender, EventArgs e ) { Process(); }
        private void caseSensitive_CheckedChanged( object sender, EventArgs e ) { Process(); }
        private void replaceText_TextChanged( object sender, EventArgs e ) { Process(); }

        private void Process()
        {
            if( modifying > 0 )
                return;

            rawText.HideSelection = true;
            var regexStr = regexText.Text;

            if( regexStr.Length == 0 )
            {
                UnhighlightText();
                errorLabel.Visible = false;
                return;
            }

            try
            {
                Regex regex = new Regex( regexStr, RegexOptions.Compiled | ( !caseSensitive.Checked ? RegexOptions.IgnoreCase : 0 ) );

                matches = regex.Matches( rawText.Text );
                errorLabel.Visible = false;
                StringBuilder text = new StringBuilder();

                text.AppendFormat( "{0} matches found:", matches.Count );
                text.AppendLine();

                foreach( Match match in matches )
                {
                    text.AppendLine( match.Value );
                }

                if( matches.Count > 0 )
                {
                    selectedIndex = 0;
                    HighlightText();
                }

                outputText.Text = regex.Replace( rawText.Text, replaceText.Text.Replace( "\\n", Environment.NewLine ) );
            }
            catch( ArgumentException ex )
            {
                UnhighlightText();
                errorLabel.Visible = true;
                errorLabel.Text = "Invalid Regex: " + ex.Message;
            }
        }

        private void HighlightText()
        {
            ++modifying;
            UnhighlightText();
            rawText.SelectionStart = matches[selectedIndex].Index;
            rawText.SelectionLength = matches[selectedIndex].Length;
           // rawText.SelectionColor = System.Drawing.Color.LawnGreen;
            rawText.SelectionColor = System.Drawing.Color.Black;
            rawText.SelectionBackColor = System.Drawing.Color.Yellow;
            --modifying;
        }

        private void UnhighlightText()
        {
            ++modifying;
            outputText.Clear();
            var prevStart = rawText.SelectionStart;
            var prevLen = rawText.SelectionLength;
            rawText.SelectionStart = 0;
            rawText.SelectionLength = rawText.Text.Length;
            rawText.SelectionColor = rawText.ForeColor;
            rawText.SelectionBackColor = rawText.BackColor;
            rawText.SelectionStart = prevStart;
            rawText.SelectionLength = prevLen;
            --modifying;
        }

        private int Mod( int a, int b )
        {
            return ( ( a %= b ) < 0 ) ? a + b : a;
        }

        private void findPrev_Click( object sender, EventArgs e )
        {
            if( matches.Count == 0 )
                return;

            selectedIndex = Mod( selectedIndex - 1, matches.Count );
            HighlightText();
        }

        private void findNext_Click( object sender, EventArgs e )
        {
            if( matches.Count == 0 )
                return;

            selectedIndex = Mod( selectedIndex + 1, matches.Count );
            HighlightText();
        }
    }
}
