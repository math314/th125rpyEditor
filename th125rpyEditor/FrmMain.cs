using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace th125rpyEditor
{
    public partial class FrmMain : Form
    {

        public FrmMain()
        {
            InitializeComponent();
        }

        private void txtExePass_DragOver(object sender, DragEventArgs e)
        {
            e.Effect = DragDropEffects.All;
        }

        private void txtExePass_DragDrop(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop)) {
                txtExePass.Text = ((string[])e.Data.GetData(DataFormats.FileDrop))[0];
            }
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            try {
                var th125_path = System.IO.Path.Combine(
                    System.Reflection.Assembly.GetExecutingAssembly().Location,
                    "..\\th125.dll");

                th125_dll.InitServer(th125_path, txtExePass.Text);
            }
            catch (Exception ex) {
                ShowInfomationMesBox(ex.Message, "rpyEditor");
                return;
            }

            DrawStatusLabelString("成功しました。");
            //Close();
        }

        private void ShowInfomationMesBox(string text,string caption)
        {
            MessageBox.Show(text, caption, MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void btnGetExePass_Click(object sender, EventArgs e)
        {
            openFileDialog.ShowDialog();
            txtExePass.Text = openFileDialog.FileName;
        }

        private void DrawStatusLabelString(string s)
        {
            toolStripStatusLabel.Text = s;
        }

        private void btnEnd_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
