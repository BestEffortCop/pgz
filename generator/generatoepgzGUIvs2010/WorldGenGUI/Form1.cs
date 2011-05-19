using System;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Reflection;

namespace WorldGenGUI
{
    public partial class Form1 : Form
    {
        private ComboBoxEx comboSelecChar = new ComboBoxEx();
        private ArrayList toolData = new ArrayList();
        private ArrayList enemyData = new ArrayList();

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
            Tool texample3 = new Tool("I am bigger than you bitch!", false, false);
            Tool texample = new Tool(genName(), false, false);
            Tool texample2 = new Tool(genName(), false, false);
            toolData.Add(texample);
            toolData.Add(texample2);
            toolData.Add(texample3);
            enemyData.Add(texample2);
            enemyData.Add(texample3);
            enemyViewer.DataSource = enemyData;
            toolViewer.DataSource = toolData;
            initDataSets();
        }

        private void butClose_Click_1(object sender, EventArgs e)
        {
            Close();
        }

        private void initDataSets() {
            // Bind ArrayList 
            //enemyViewer.DataSource = toolData;

            Tool.SortingOrder = SortOrder.Ascending;
            toolData.Sort();

            // Create a Custom TableStyle 
            DataGridTableStyle tableStyle = new DataGridTableStyle();
            tableStyle.MappingName = "ArrayList";
            tableStyle.HeaderFont = new Font("Verdana", 9, FontStyle.Bold);
            tableStyle.HeaderForeColor = Color.MidnightBlue;

            int colwidth = (enemyViewer.ClientSize.Width - tableStyle.RowHeaderWidth
                - SystemInformation.VerticalScrollBarWidth) / 7;

            // Create a DataGridColumn, set its header text and other properties
            DataGridTextBoxColumn cs = new DataGridTextBoxColumn();
            cs.MappingName = "toolName";
            cs.HeaderText = "Name";
            cs.Width = colwidth * 2;
            // Add Column to GridColumnStyles
            tableStyle.GridColumnStyles.Add(cs);

            // Create a DataGridColumn, set its header text and other properties
            cs = new DataGridTextBoxColumn();
            cs.MappingName = "toolWant";
            cs.HeaderText = "I Want it!";
            cs.Width = colwidth * 2;
            // Add Column to GridColumnStyles
            tableStyle.GridColumnStyles.Add(cs);

            // Create a DataGridColumn, set its header text and other properties
            cs = new DataGridTextBoxColumn();
            cs.MappingName = "toolNoWant";
            cs.HeaderText = "Don't Want it!";
            cs.Width = colwidth * 2;
            // Add Column to GridColumnStyles
            tableStyle.GridColumnStyles.Add(cs);

            enemyViewer.AllowUserToOrderColumns = false;
            enemyViewer.AllowUserToResizeColumns = false;
            enemyViewer.AutoSize = true;
            enemyViewer.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
            
            
            // Add new table style to the Grid
            //toolViewer.TableStyles.Add(tableStyle);
            
        }

        private void toolViewer_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == 1)
            toolViewer.Rows[e.RowIndex].Cells[1].Style.BackColor = Color.Green;
            else
            toolViewer.Rows[e.RowIndex].Cells[2].Style.BackColor = Color.Red;
        }
    }
}
