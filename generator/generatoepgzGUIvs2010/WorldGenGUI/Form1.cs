using System;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Reflection;
using System.IO;
using System.Diagnostics;

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
            comboSelecChar.ImageList = charImgList;
            comboSelecChar.DropDownStyle = ComboBoxStyle.DropDownList;
            comboSelecChar.Items.Add(new ComboBoxExItem("Indi", 0));
            comboSelecChar.Items.Add(new ComboBoxExItem("Skull Man", 1));
            comboSelecChar.Location = new Point(225, 40);
            tabPage1.Controls.Add(comboSelecChar);
            comboSelecChar.Height = charImgList.ImageSize.Height * charImgList.Images.Count;
            comboSelecChar.ItemHeight = charImgList.ImageSize.Height;
            comboSelecChar.SelectedIndex = 0;
            statusProgress.Visible = false;
            
            comboDiff.SelectedIndex = 2;
            comboSize.SelectedIndex = 2;
            comboTheme.SelectedIndex = 0;

            
            System.Environment.CurrentDirectory = @".\bin\";

            if (!System.IO.File.Exists("generatorpgz.exe"))
            {
                MessageBox.Show("You need to have an updated dbdata in /bin folder!",
                "Dbdata not found!",
                MessageBoxButtons.OK,
                MessageBoxIcon.Exclamation,
                MessageBoxDefaultButton.Button1);
                Close();
            }

            System.Diagnostics.Process cmd = new System.Diagnostics.Process();
            cmd.StartInfo.UseShellExecute = false;
            cmd.StartInfo.FileName = "DataBaseContent.exe";

            // Loading Database content...

            cmd.Start();

            loadDBData("dbdata");
            enemyViewer.DataSource = enemyData;
            toolViewer.DataSource = toolData;
            initDataSets();
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

        void RunWithRedirect(string cmdPath)
        {
            var proc = new Process();
            proc.StartInfo.FileName = cmdPath;
            proc.StartInfo.UseShellExecute = false;

            // set up output redirection
            proc.StartInfo.RedirectStandardOutput = true;
            proc.StartInfo.RedirectStandardError = true;
            proc.EnableRaisingEvents = true;
            proc.StartInfo.CreateNoWindow = true;
            // see below for output handler
            proc.ErrorDataReceived += proc_DataReceived;
            proc.OutputDataReceived += proc_DataReceived;

            proc.Exited += new EventHandler(proc_Exited);

            proc.Start();

            proc.BeginErrorReadLine();
            proc.BeginOutputReadLine();
            
            //proc.WaitForExit();
        }

        void proc_DataReceived(object sender, DataReceivedEventArgs e)
        {
            // output will be in string e.Data
            statusText.Text = e.Data;
        }

        private void proc_Exited(object sender, System.EventArgs e)
        {
            Process proc = (Process)sender;
            // Wait a short while to allow all console output to be processed and appended
            // before appending the success/fail message.
            System.Threading.Thread.Sleep(40);
            proc.Close();
        }

        private void butGenerate_Click_1(object sender, EventArgs e)
        {
            bool allGood = true;
            if (tBoxName.TextLength == 0)
                tBoxName.Text = genName();
            
            if (!System.IO.File.Exists("generatorpgz.exe"))
            {
                MessageBox.Show("You need to have generatorpgz.exe in /bin folder!",
                "Generator.exe not found!",
                MessageBoxButtons.OK,
                MessageBoxIcon.Exclamation,
                MessageBoxDefaultButton.Button1);
                allGood = false;
            }
            if (!System.IO.File.Exists("projectpgz-vs2010.exe"))
            {
                MessageBox.Show("You need to have projectpgz-vs2010.exe in /bin folder!",
                "Projectpgz.exe not found!",
                MessageBoxButtons.OK,
                MessageBoxIcon.Exclamation,
                MessageBoxDefaultButton.Button1);
                allGood = false;
            }

            if (allGood)
            {
                statusProgress.Visible = true;
                RunWithRedirect("generatorpgz.exe");
                Process cmd = new Process();
                cmd.StartInfo.UseShellExecute = false;
                saveDecidatorData();
                saveHistoriator();
                //saveInputData();
                cmd.StartInfo.FileName = "projectpgz-vs2010.exe";
                cmd.Start();
                cmd.WaitForExit();
            }
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

            Enemy.SortingOrder = SortOrder.Ascending;
            enemyData.Sort();

            DataGridViewCellStyle style;
            style = new DataGridViewCellStyle();
            style.Alignment = System.Windows.Forms.DataGridViewContentAlignment.BottomCenter;
            style.BackColor = System.Drawing.Color.MidnightBlue;
            style.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            style.ForeColor = System.Drawing.Color.White;
            style.WrapMode = System.Windows.Forms.DataGridViewTriState.True;

            toolViewer.EnableHeadersVisualStyles = false;
            foreach (DataGridViewColumn col in toolViewer.Columns)
                col.HeaderCell.Style = style;
            toolViewer.Columns[0].HeaderText = "Tool Name";
            toolViewer.Columns[1].HeaderText = "I Want it!";
            toolViewer.Columns[2].HeaderText = "Don't Want it!";

            toolViewer.AllowUserToOrderColumns = false;
            toolViewer.AllowUserToResizeColumns = false;
            toolViewer.AllowUserToResizeRows = false;
            toolViewer.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.ColumnHeader;

            enemyViewer.EnableHeadersVisualStyles = false;
            foreach (DataGridViewColumn col in enemyViewer.Columns)
                col.HeaderCell.Style = style;
            enemyViewer.Columns[0].HeaderText = "Enemy Name";
            enemyViewer.Columns[1].HeaderText = "I Want it!";
            enemyViewer.Columns[2].HeaderText = "Don't Want it!";

            enemyViewer.AllowUserToOrderColumns = false;
            enemyViewer.AllowUserToResizeColumns = false;
            enemyViewer.AllowUserToResizeRows = false;
            enemyViewer.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.ColumnHeader;
            
        }

        private void toolViewer_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0 && e.ColumnIndex >= 0)
            {
                if (e.ColumnIndex == 1)
                    if ((bool)toolViewer[e.ColumnIndex, e.RowIndex].Value)
                    {
                        toolViewer[e.ColumnIndex + 1, e.RowIndex].Value = false;
                        toolViewer[e.ColumnIndex, e.RowIndex].Style.BackColor = Color.Green;
                    }
                    else
                        toolViewer[e.ColumnIndex, e.RowIndex].Style.BackColor = Color.White;
                else
                    if ((bool)toolViewer[e.ColumnIndex, e.RowIndex].Value)
                    {
                        toolViewer[e.ColumnIndex - 1, e.RowIndex].Value = false;
                        toolViewer[e.ColumnIndex, e.RowIndex].Style.BackColor = Color.Red;
                    }
                    else
                        toolViewer[e.ColumnIndex, e.RowIndex].Style.BackColor = Color.White;
            }
        }

        private void saveDecidatorData() 
        {
            StreamWriter sw = new StreamWriter("decidatorData");
            int i = 0;
            foreach (DataGridViewRow row in enemyViewer.Rows)
            {
                sw.Write(enemyViewer["Name", i].Value + " ");
                if ((bool)enemyViewer["Want", i].Value)
                    sw.Write(1 + " ");
                else sw.Write(0 + " ");
                if ((bool)enemyViewer["NoWant", i].Value)
                    sw.WriteLine(1);
                else
                    sw.WriteLine(0);
                i++;
            }
            sw.Close();
        }

        private void saveInputData()
        {
            StreamWriter sw = new StreamWriter("input.dat");
            sw.Write("playerName=" + tBoxName.Text);
            sw.Write("player=" + comboSelecChar.SelectedIndex);
            sw.Write("thematic=" + comboTheme.SelectedText);
            sw.Write("difficulty=" + comboDiff.SelectedIndex);
            sw.Write("worldSize=" + 10);
            sw.Write("numZones=" + numZones.Value);
            sw.Write("ratio=" + barRatio.Value);
            int i = 0;
            foreach (DataGridViewRow row in enemyViewer.Rows)
            {
                sw.Write(enemyViewer["Name", i].Value + " ");
                if ((bool)enemyViewer["Want", i].Value)
                    sw.Write(1 + " ");
                else sw.Write(0 + " ");
                if ((bool)enemyViewer["NoWant", i].Value)
                    sw.WriteLine(1);
                else
                    sw.WriteLine(0);
                i++;
            }
            sw.Close();
        }

        private void saveHistoriator()
        {
            StreamWriter sw = new StreamWriter("historiator.data");
            sw.WriteLine(prologFormat("playerName", tBoxName.Text));
            sw.WriteLine(prologFormat("thematic", comboTheme.SelectedText));
            sw.WriteLine(prologFormat("worldSize", comboSize.SelectedText));
            sw.Close();
        }

        private string prologFormat(string name, string value) 
        {
            return name + "('" + value + "')."; 
        }

        private void enemyViewer_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0 && e.ColumnIndex >= 0)
            {
                if (e.ColumnIndex == 1)
                    if ((bool)enemyViewer[e.ColumnIndex, e.RowIndex].Value)
                    {
                        enemyViewer[e.ColumnIndex + 1, e.RowIndex].Value = false;
                        enemyViewer[e.ColumnIndex, e.RowIndex].Style.BackColor = Color.Green;
                    }
                    else
                        enemyViewer[e.ColumnIndex, e.RowIndex].Style.BackColor = Color.White;
                else
                    if ((bool)enemyViewer[e.ColumnIndex, e.RowIndex].Value)
                    {
                        enemyViewer[e.ColumnIndex - 1, e.RowIndex].Value = false;
                        enemyViewer[e.ColumnIndex, e.RowIndex].Style.BackColor = Color.Red;
                    }
                    else
                        enemyViewer[e.ColumnIndex, e.RowIndex].Style.BackColor = Color.White;
            }
        }

    }
}
