using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WorldGenGUI
{
    public partial class Form1 : Form
    {
        private ComboBoxEx comboSelecChar = new ComboBoxEx();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            comboSelecChar.ImageList = charImgList;
            comboSelecChar.DropDownStyle = ComboBoxStyle.DropDownList;
            // just pass these in instead of strings, class included below
            // specify a valid imageIndex
            comboSelecChar.Items.Add(new ComboBoxExItem("Indi Faker", 0));
            comboSelecChar.Items.Add(new ComboBoxExItem("Skull Man", 1));
            comboSelecChar.Location = new Point(225, 40);
            tabPage1.Controls.Add(comboSelecChar);
            comboSelecChar.Height = charImgList.ImageSize.Height * charImgList.Images.Count;
            comboSelecChar.ItemHeight = charImgList.ImageSize.Height;

            chkListBoxTools.SetItemChecked(3, true);
        }

        private String genName(){
            Random rand = new Random();
            string name = "";
            int namelen = rand.Next(4, 10);

            string[] letters = new string[2] { "bcdfghjklmnpqrstvwxyz", "aeiou" };
            int[] letterlen = new int[2] { letters[0].Length, letters[1].Length };

            for (int i = 0; i < namelen; i++)
                name += letters[i % 2][rand.Next() % letterlen[i % 2]];

            string capitalName = "";
            capitalName += char.ToUpper(name[0]);
            capitalName += name.Substring(1);
            return capitalName;
        }

        private void butGenerate_Click_1(object sender, EventArgs e)
        {
            tBoxName.Text = genName();
        }

        private void butClose_Click_1(object sender, EventArgs e)
        {
            Close();
        }
    }
}
