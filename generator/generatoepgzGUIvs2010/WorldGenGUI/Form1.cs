using System;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Reflection;
using System.IO;

namespace WorldGenGUI
{
    public partial class PGZForm : Form
    {
        private ComboBoxEx comboSelecChar = new ComboBoxEx();
        private ArrayList toolData = new ArrayList();
        private ArrayList enemyData = new ArrayList();
        private ArrayList playerData = new ArrayList();
        private ArrayList themeData = new ArrayList();

        public PGZForm()
        {
            InitializeComponent();
        }

        private void PGZForm_Load(object sender, EventArgs e)
        {
            /*if (System.IO.Directory.Exists("bin/data"))
                System.IO.Directory.Delete("bin/data", true);*/
            System.Environment.CurrentDirectory =  @".\bin\";
            System.Diagnostics.Process cmd = new System.Diagnostics.Process();
            cmd.StartInfo.UseShellExecute = false;
            /*cmd_gen.StartInfo.Arguments = numericMiniBoss.Value + " " + numericChambers.Value +
                " " + (comboBDifficulty.SelectedIndex+1);*/
            cmd.StartInfo.FileName = "DataBaseContent.exe";
            cmd.Start();

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
            if (tBoxName.TextLength == 0)
                tBoxName.Text = genName();
            loadDBData("dbdata");
            enemyViewer.DataSource = enemyData;
            toolViewer.DataSource = toolData;
            initDataSets();

            if (!System.IO.File.Exists("generatorpgz.exe"))
            {
                MessageBox.Show("You need to have generatorpgz.exe in /bin folder!",
                "Generator.exe not found!",
                MessageBoxButtons.OK,
                MessageBoxIcon.Exclamation,
                MessageBoxDefaultButton.Button1);
                //Close();
            }
            if (!System.IO.File.Exists("projectpgz-vs2010.exe"))
            {
                MessageBox.Show("You need to have projectpgz-vs2010.exe in /bin folder!",
                "Generator.exe not found!",
                MessageBoxButtons.OK,
                MessageBoxIcon.Exclamation,
                MessageBoxDefaultButton.Button1);
                //Close();
            }

            System.Diagnostics.Process cmd = new System.Diagnostics.Process();
            cmd.StartInfo.UseShellExecute = false;
            cmd.StartInfo.FileName = "generatorpgz.exe";
            
            //cmd.Start();
            //cmd.WaitForExit();

            saveDecidatorData();

        }

        private void butClose_Click_1(object sender, EventArgs e)
        {
            Close();
        }

        private void loadDBData(string filename) 
        {
            StreamReader sr;
            string line;
            string[] data, values;
            sr = File.OpenText(filename);
            // Players
            line = sr.ReadLine();
            data = line.Split(';');
            for (int i = 0; i < data.Length-1; i++)
            {
                values = data[i].Split(',');
                playerData.Add(new Player(Convert.ToInt32(values[0]), values[1]));
            }
            // Enemies
            line = sr.ReadLine();
            data = line.Split(';');
            for (int i = 0; i < data.Length - 1; i++)
            {
                values = data[i].Split(',');
                enemyData.Add(new Enemy(Convert.ToInt32(values[0]), values[1], false, false));
            }
            // Themes
            line = sr.ReadLine();
            data = line.Split(';');
            for (int i = 0; i < data.Length - 1; i++)
            {
                values = data[i].Split(',');
                themeData.Add(new Theme(Convert.ToInt32(values[0]), values[1]));
            }
            // Tools
            line = sr.ReadLine();
            data = line.Split(';');
            for (int i = 0; i < data.Length - 1; i++)
            {
                values = data[i].Split(',');
                toolData.Add(new Tool(Convert.ToInt32(values[0]), values[1], false, false));
            }
            sr.Close();
        }

        private void initDataSets() {

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

            DataGridViewCellStyle style;
            style = new DataGridViewCellStyle();
            style.Alignment = System.Windows.Forms.DataGridViewContentAlignment.BottomCenter;
            style.BackColor = System.Drawing.Color.Navy;
            style.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            style.ForeColor = System.Drawing.Color.White;
            style.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            style.SelectionForeColor = System.Drawing.Color.Navy;
            style.WrapMode = System.Windows.Forms.DataGridViewTriState.True;

            enemyViewer.EnableHeadersVisualStyles = false;
            foreach (DataGridViewColumn col in enemyViewer.Columns)
                col.HeaderCell.Style = style;
            enemyViewer.Columns[0].HeaderText = "Enemy Name";

            toolViewer.AllowUserToOrderColumns = false;
            toolViewer.AllowUserToResizeColumns = false;
            toolViewer.AutoSize = true;
            toolViewer.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
            
            
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

        private void saveDecidatorData() 
        {
            StreamWriter sw = new StreamWriter("decidatorData");
            foreach (DataGridViewRow row in enemyViewer.Rows)
                sw.Write(row.Cells[1].FormattedValue);
            sw.Close();
        }

    }
}
