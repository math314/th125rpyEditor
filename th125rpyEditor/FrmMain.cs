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

        private void LoadInitData()
        {
        }

        //private bool GetInitData(out Initalize init,out string sExePass, out string sErrorStr)
        //{
        //    dllInjection.GetInitData(out init);
        //    sErrorStr = "";
        //    sExePass = txtExePass.Text;
        //    //入力
        //    if (sExePass == "") {
        //        sErrorStr = "実行ファイルのパスが入力されていません。";
        //        txtExePass.Focus();
        //        return false;
        //    }
        //    init.bCreateDebugStringFile = (chkCreateDebugFile.Checked) ? (byte)1 : (byte)0;    //true or false
        //    if (!GetFPSvalue("1番", txtFPS1.Text, out init.fFPS1, out sErrorStr)) { DrawStatusLabelString(sErrorStr); txtFPS1.Focus(); return false; }
        //    if (!GetFPSvalue("2番", txtFPS2.Text, out init.fFPS2, out sErrorStr)) { DrawStatusLabelString(sErrorStr); txtFPS2.Focus(); return false; }
        //    if (!GetFPSvalue("3番", txtFPS3.Text, out init.fFPS3, out sErrorStr)) { DrawStatusLabelString(sErrorStr); txtFPS3.Focus(); return false; }
        //    if (!GetFPSvalue("4番", txtFPS4.Text, out init.fFPS4, out sErrorStr)) { DrawStatusLabelString(sErrorStr); txtFPS4.Focus(); return false; }
        //    if (!GetFPSvalue("5番", txtFPS5.Text, out init.fFPS5, out sErrorStr)) { DrawStatusLabelString(sErrorStr); txtFPS5.Focus(); return false; }
        //    if (!GetFPSvalue("6番", txtFPS6.Text, out init.fFPS6, out sErrorStr)) { DrawStatusLabelString(sErrorStr); txtFPS6.Focus(); return false; }
        //    if (!GetFPSvalue("7番", txtFPS7.Text, out init.fFPS7, out sErrorStr)) { DrawStatusLabelString(sErrorStr); txtFPS7.Focus(); return false; }
        //    if (!GetFPSvalue("8番", txtFPS8.Text, out init.fFPS8, out sErrorStr)) { DrawStatusLabelString(sErrorStr); txtFPS8.Focus(); return false; }
        //    if (!GetFPSvalue("9番", txtFPS9.Text, out init.fFPS9, out sErrorStr)) { DrawStatusLabelString(sErrorStr); txtFPS9.Focus(); return false; }
        //    if (!GetFPSvalue("0番", txtFPS0.Text, out init.fFPS0, out sErrorStr)) { DrawStatusLabelString(sErrorStr); txtFPS0.Focus(); return false; }

        //    if (rdbSaveFixedIndex.Checked) {
        //        if (txtSaveRpyIndex.Text == "") {
        //            sErrorStr = ("保存先のリプレイ番号が入力されていません。");
        //            txtSaveRpyIndex.Focus(); 
        //            return false;
        //        }
        //        if (!int.TryParse(txtSaveRpyIndex.Text, out init.iSaveReplayIndex)) {
        //            sErrorStr = ("保存先リプレイ番号が数値として認識できませんでした。");
        //            txtSaveRpyIndex.Focus();
        //             return false;
        //        }
        //        if (init.iSaveReplayIndex <= 0 || init.iSaveReplayIndex >= 10000) {
        //            sErrorStr = ("保存先リプレイ番号に、" + init.iSaveReplayIndex.ToString() + "番は使用できません。");
        //            txtSaveRpyIndex.Focus();
        //             return false;
        //        }
        //        init.ReplayIndex_Max = 9999;
        //    }
        //    else {
        //        init.iSaveReplayIndex = -1;
        //        if (txtMaxRpyIndex.Text == "") {
        //            sErrorStr = ("保存するリプレイ番号の上限が入力されていません。");
        //            txtSaveRpyIndex.Focus();
        //             return false;
        //        }
        //        if (!int.TryParse(txtSaveRpyIndex.Text, out init.iSaveReplayIndex)) {
        //            sErrorStr = ("保存するリプレイ番号の上限が、数値として認識できませんでした。");
        //            txtSaveRpyIndex.Focus();
        //             return false;
        //        }
        //        if (init.iSaveReplayIndex <= 0 || init.iSaveReplayIndex >= 10000) {
        //            sErrorStr = ("保存するリプレイ番号の上限に、" + init.iSaveReplayIndex.ToString() + "番は使用できません。");
        //            txtSaveRpyIndex.Focus();
        //             return false;
        //        }
        //    }
        //    int a, r, g, b;
        //    //a
        //    if(txtColorA.Text == ""){
        //        sErrorStr = "デバッグ文字列の透過度(α)が入力されていません。";
        //        txtColorA.Focus();
        //        return false;
        //    }
        //    if (!int.TryParse(txtColorA.Text, out a)) {
        //        sErrorStr = ("デバッグ文字列の透過度(α)が、数値として認識できませんでした。");
        //        txtColorA.Focus();
        //        return false;
        //    }
        //    if (a < 0 || a > 255) {
        //        sErrorStr = ("デバッグ文字列の透過度(α)は0~255です。");
        //        txtColorA.Focus();
        //        return false;
        //    }
        //    //r
        //    if (txtColorR.Text == "") {
        //        sErrorStr = "デバッグ文字列のR(赤)が入力されていません。";
        //        txtColorR.Focus();
        //        return false;
        //    }
        //    if (!int.TryParse(txtColorR.Text, out r)) {
        //        sErrorStr = ("デバッグ文字列のR(赤)が、数値として認識できませんでした。");
        //        txtColorR.Focus();
        //        return false;
        //    }
        //    if (r < 0 || r > 255) {
        //        sErrorStr = ("デバッグ文字列のR(赤)は0~255です。");
        //        txtColorR.Focus();
        //        return false;
        //    }
        //    //g
        //    if (txtColorG.Text == "") {
        //        sErrorStr = "デバッグ文字列のG(緑)が入力されていません。";
        //        txtColorG.Focus();
        //        return false;
        //    }
        //    if (!int.TryParse(txtColorG.Text, out g)) {
        //        sErrorStr = ("デバッグ文字列のG(緑)が、数値として認識できませんでした。");
        //        txtColorG.Focus();
        //        return false;
        //    }
        //    if (g < 0 || g > 255) {
        //        sErrorStr = ("デバッグ文字列のG(緑)は0~255です。");
        //        txtColorG.Focus();
        //        return false;
        //    }
        //    //b
        //    if (txtColorB.Text == "") {
        //        sErrorStr = "デバッグ文字列のB(青)が入力されていません。";
        //        txtColorB.Focus();
        //        return false;
        //    }
        //    if (!int.TryParse(txtColorB.Text, out b)) {
        //        sErrorStr = ("デバッグ文字列のB(青)が、数値として認識できませんでした。");
        //        txtColorB.Focus();
        //        return false;
        //    }
        //    if (b < 0 || b > 255) {
        //        sErrorStr = ("デバッグ文字列のB(青)は0~255です。");
        //        txtColorB.Focus();
        //        return false;
        //    }
        //    init.stringColor = (uint)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff));  // = D3DCOLOR_AGRB(128,128,128,128);
        //    return true;
        //}

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
        private bool GetFPSvalue(string sName, string sValue, out float ans,out string sErrorString)
        {
            sErrorString = "";
            ans = 0.0f;
            if (sValue == "") {
                sErrorString = sName + "にFPSの値が入力されていません。";
                return false;
            }
            if (!float.TryParse(sValue, out ans)) {
                sErrorString = sName + "のFPSが数値として認識できませんでした。";
                return false;
            }
            if (ans < 3.0) {
                sErrorString = sName + "のFPSが3未満です。";
                return false;
            }
            if (ans > 600.0) {
                sErrorString = sName + "のFPSが600より大きいです。";
                return false;
            }

            return true;
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

        private void btnChoiceColor_Click(object sender, EventArgs e)
        {
            DialogResult ret =  colorDialog.ShowDialog();
            if (ret == DialogResult.Cancel) {
                return;
            }

            Color cr = colorDialog.Color;
            txtColorR.Text = cr.R.ToString();
            txtColorG.Text = cr.G.ToString();
            txtColorB.Text = cr.B.ToString();

        }

        private void rdbSaveFixedIndex_CheckedChanged(object sender, EventArgs e)
        {
            if (rdbSaveFixedIndex.Checked) {
                txtSaveRpyIndex.Enabled = true;
                txtMaxRpyIndex.Enabled = false;
            }
            else {
                txtSaveRpyIndex.Enabled = false;
                txtMaxRpyIndex.Enabled = true;
            }
        }

        private void picColor_Paint(object sender, PaintEventArgs e)
        {
            int a, r, g, b;
            if (!int.TryParse(txtColorA.Text, out a)) { return; }
            if (a > 255 || a < 0) { return; }
            if (!int.TryParse(txtColorR.Text, out r)) { return; }
            if (r > 255 || r < 0) { return; }
            if (!int.TryParse(txtColorG.Text, out g)) { return; }
            if (g > 255 || g < 0) { return; }
            if (!int.TryParse(txtColorB.Text, out b)) { return; }
            if (b > 255 || b < 0) { return; }

            Color cr = Color.FromArgb(a, r, g, b);
            SolidBrush br = new SolidBrush(cr);
            e.Graphics.FillRectangle(br, e.ClipRectangle);
        }

        private void txtColor_TextChanged(object sender, EventArgs e)
        {
            picColor.Invalidate();
        }


    }
}
