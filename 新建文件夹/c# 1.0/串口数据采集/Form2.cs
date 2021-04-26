using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;
using System.IO;//用于文件存取 
using System.Drawing.Text;//提供画GDI+图形的高级功能 
using System.Drawing.Drawing2D;//提供画高级二维，矢量图形功能 
using System.Drawing.Imaging;
using System.Data.SqlClient;
using System.Data.OleDb;
using System.Net;
using System.Net.Sockets;
using System.Diagnostics;
using System.Threading;
using System.IO.Ports;
using 串口轨迹;

namespace WindowsFormsApplication1
{
    public partial class Form2 : Form
    {

        SerialPort CommPort;    //串口操作对象

        int axis_max = 100;

        string str_con = "server=local;database=sjcj;uid=sa;pwd=boshi1987";

        myDataBase gDataBase = new myDataBase();

        public Form2()
        {
            InitializeComponent();
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            chart1.ChartAreas[0].AxisX.MajorGrid.Interval = 1;
            chart1.ChartAreas[0].AxisX.MajorGrid.Enabled = false;
            chart1.ChartAreas[0].AxisX.Minimum = 0;
            chart1.ChartAreas[0].AxisX.Maximum = axis_max;


            chart1.ChartAreas[0].AxisY.Minimum = 0;
            chart1.ChartAreas[0].AxisY.Maximum = 100;
             
            chart1.Series[0].BorderWidth = 2;
            chart1.Series[1].BorderWidth = 2;

            /*获取串口*/
            string[] portsArray = SerialPort.GetPortNames();
            foreach (string portnumber in portsArray)
            {
                cbxPortName.Items.Add(portnumber);
                cbxPortName.SelectedIndex = 0;
            }
            gDataBase.myDataBaseConnect("127.0.0.1", "Test", "sa", "boshi1987");
            gDataBase.myDataBaseRead("Table1");
            return;

        }
        private void Form2_FormClosing(object sender, FormClosingEventArgs e)
        {                                                    
            Process[] processes = Process.GetProcessesByName("串口数据采集");
            foreach (Process p in processes)
            {
                if (p.ProcessName == "串口数据采集")
                {
                    p.Kill();
                    p.Close();
                }
            }
        }

        int flag_tmp = 0;//0 不动作 1 温度过低 2 温度过高

        int flag_hum = 0;//0 不动作 1 湿度过低 3 湿度过高

        int x = 0;

        /// <summary>
        /// 串口接收数据处理
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CommDataRecv(object sender, SerialDataReceivedEventArgs e)
        {
            string str = "";
            try
            {
                str = CommPort.ReadLine();//从串口中读取一行数据
            }
            catch (Exception ex)
            {
 
            }

            if (str == "")                  //判断数据是否位空
            {
                return;
            }
            string[] sub = str.Split(',');//用数据将字符串进行分割

            if (sub.Length != 6)
            {
                return;
            }


            this.Invoke(new Action(() =>
            {

                Single tmp = Convert.ToSingle(sub[0]);//实时温度
                Single hum = Convert.ToSingle(sub[1]);//实时湿度

                textBoxMinTmp.Text = sub[2];//温度最小值
                textBoxMaxTmp.Text = sub[3];//温度最大值
                textBoxMinHum.Text = sub[4];//湿度最小值
                textBoxMaxHum.Text = sub[5];//湿度最大值

                gDataBase.myDataBaseInsert("Table1", sub);
                dataGridView1.Rows.Add();
                int i = 0;
                int row_index = dataGridView1.Rows.Count - 1;

                dataGridView1.Rows[row_index].Cells[0].Value = row_index;
                dataGridView1.Rows[row_index].Cells[1].Value = sub[0];
                dataGridView1.Rows[row_index].Cells[2].Value = sub[1];
                

                if (tmp < Convert.ToSingle(textBoxMinTmp.Text))
                {
                    flag_tmp = 1;
                    this.pictureBox1.Image = global::串口数据采集.Properties.Resources.danger2;
                    dataGridView1.Rows[row_index].Cells[1].Style.ForeColor = Color.Blue;
                }
                else if (tmp > Convert.ToSingle(textBoxMaxTmp.Text))
                {
                    flag_tmp = 2;
                    this.pictureBox1.Image = global::串口数据采集.Properties.Resources.danger;
                    dataGridView1.Rows[row_index].Cells[1].Style.ForeColor = Color.Red;
                }
                else 
                {
                   this.pictureBox1.Image = global::串口数据采集.Properties.Resources.normal;
                    flag_tmp = 0;
                    dataGridView1.Rows[row_index].Cells[1].Style.ForeColor = Color.Black;
                    
                }

                if (hum < Convert.ToSingle(textBoxMinHum.Text))
                {
                    flag_hum = 1;
                    this.pictureBox2.Image = global::串口数据采集.Properties.Resources.danger2;
                    dataGridView1.Rows[row_index].Cells[2].Style.ForeColor = Color.Blue;
                }
                else if (hum > Convert.ToSingle(textBoxMaxHum.Text))
                {
                    flag_hum = 2;
                    this.pictureBox2.Image = global::串口数据采集.Properties.Resources.danger;
                    dataGridView1.Rows[row_index].Cells[2].Style.ForeColor = Color.Red;
                    
                }
                else
                {
                     this.pictureBox2.Image = global::串口数据采集.Properties.Resources.normal;
                     flag_hum = 0;
                    dataGridView1.Rows[row_index].Cells[2].Style.ForeColor = Color.Black;
                }


                dataGridView1.Rows[row_index].Cells[3].Value = sub[2];
                dataGridView1.Rows[row_index].Cells[4].Value = sub[3];
                dataGridView1.Rows[row_index].Cells[5].Value = sub[4];
                dataGridView1.Rows[row_index].Cells[6].Value = sub[5];


                if (flag_tmp != 0 || flag_hum != 0)
                {
                    dataGridView1.Rows[row_index].Cells[7].Value = "true";
                    dataGridView1.Rows[row_index].Cells[7].Style.ForeColor = Color.Red;
                }
                else
                {
                    dataGridView1.Rows[row_index].Cells[7].Value = "false";
                }


                dataGridView1.Rows[row_index].Cells[8].Value = System.DateTime.Now.ToString();

               

                this.dataGridView1.FirstDisplayedScrollingRowIndex = this.dataGridView1.Rows.Count - 1;

                /*将数据增加到曲线上去*/
                if (chart1.Series[0].Points.Count < axis_max)
                {
                    /*将数据增加到曲线上去*/
                    chart1.Series[0].Points.AddXY(x, Convert.ToSingle(sub[0]));//温度数据
                    chart1.Series[1].Points.AddXY(x, Convert.ToSingle(sub[1]));//湿度数据
                }
                else
                {
                    chart1.Series[0].Points.AddXY(x, Convert.ToSingle(sub[0]));//温度数据
                    chart1.Series[1].Points.AddXY(x, Convert.ToSingle(sub[1]));//湿度数据

                    chart1.Series[0].Points.RemoveAt(0);
                    chart1.Series[1].Points.RemoveAt(0);
                    chart1.ChartAreas[0].AxisX.Minimum = chart1.ChartAreas[0].AxisX.Minimum + 1;
                    chart1.ChartAreas[0].AxisX.Maximum = chart1.ChartAreas[0].AxisX.Maximum + 1;
                }
                x++;
            }));
        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            if (btnOpen.Text == "打开串口")
            {
                btnOpen.Text = "关闭串口";
                CommPort = new SerialPort();
                CommPort.DataReceived += new SerialDataReceivedEventHandler(CommDataRecv);//注册接收串口事件
                CommPort.PortName = this.cbxPortName.Text;
                CommPort.BaudRate = Convert.ToInt32(this.cbxPortBaud.Text);
                CommPort.Parity = (Parity)(comboBoxCheck.SelectedIndex);
                CommPort.DataBits = Convert.ToInt32(comboBoxBits.Text);
                CommPort.StopBits = StopBits.One;
                CommPort.ReadTimeout = 1000;
                CommPort.ReadBufferSize = 50*1024;
                CommPort.ReceivedBytesThreshold = 19;
                CommPort.NewLine = "\r\n";
                try
                {
                    CommPort.Open();
                }
                catch (Exception err)
                {
                    MessageBox.Show(this, err.Message);
                    return;
                }
                toolStripStatusLabel1.Text = "PortName:" + CommPort.PortName.ToString() + " Opened" +
                                    " BaudRate:" + CommPort.BaudRate.ToString() +
                                    " DataBits:" + CommPort.DataBits.ToString() +
                                    " StopBits:" + CommPort.StopBits.ToString() +
                                    " Parity:" + CommPort.Parity.ToString();
               
            }
            else
            {
                btnOpen.Text = "打开串口";
                CommPort.DataReceived -= new SerialDataReceivedEventHandler(CommDataRecv);//卸载接收串口事件
                if (CommPort.IsOpen == true)
                {
                    try
                    {
                        CommPort.Close();
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine("错误：" + ex.Message);
                    }

                    try
                    {
                        CommPort.Dispose();
                    }
                    catch (Exception er)
                    {
                        Console.WriteLine("错误：" + er.Message);
                    }
                    this.btnOpen.Enabled = true;

                }
                toolStripStatusLabel1.Text = "PortName:" + CommPort.PortName + " Closed";
                
            }
        }


        private void btnRead_Click(object sender, EventArgs e)
        {
            gDataBase.myDataBaseRead("Table1");
            if (gDataBase.ds.Tables[0].Rows.Count == 0)
            {
                MessageBox.Show("数据库中无数据");
                return;
            }
            dataGridView1.Rows.Clear();
            chart1.Series[0].Points.Clear();
            chart1.Series[1].Points.Clear();
            x = 0;
 
           foreach (DataRow dr in gDataBase.ds.Tables[0].Rows)
           {

               dataGridView1.Rows.Add();
               int i = 0;
               int row_index = dataGridView1.Rows.Count - 1;
               dataGridView1.Rows[row_index].Cells[0].Value = dr[0].ToString().Trim();//序号

               dataGridView1.Rows[row_index].Cells[1].Value = dr[1].ToString().Trim();//温度
               dataGridView1.Rows[row_index].Cells[2].Value = dr[2].ToString().Trim();//湿度

               dataGridView1.Rows[row_index].Cells[3].Value = dr[3].ToString().Trim();//温度最小
               dataGridView1.Rows[row_index].Cells[4].Value = dr[4].ToString().Trim();//温度最大
               dataGridView1.Rows[row_index].Cells[5].Value = dr[5].ToString().Trim();//湿度最小
               dataGridView1.Rows[row_index].Cells[6].Value = dr[6].ToString().Trim();//湿度最大

               dataGridView1.Rows[row_index].Cells[8].Value = dr[7].ToString().Trim();//时间
              
               this.dataGridView1.FirstDisplayedScrollingRowIndex = this.dataGridView1.Rows.Count - 1;

               textBoxMinTmp.Text = dr[3].ToString();
               textBoxMaxTmp.Text = dr[4].ToString();
               textBoxMinHum.Text = dr[5].ToString();
               textBoxMaxTmp.Text = dr[6].ToString();


               float tmp = Convert.ToSingle(dr[1]);
               float hum = Convert.ToSingle(dr[2]);

               bool flag = false;

               if (tmp < Convert.ToSingle(textBoxMinTmp.Text))
               {
                   dataGridView1.Rows[row_index].Cells[1].Style.ForeColor = Color.Blue;
                   flag = true;
               }
               else if (tmp > Convert.ToSingle(textBoxMaxTmp.Text))
               {
                  
                   dataGridView1.Rows[row_index].Cells[1].Style.ForeColor = Color.Red;
                   flag = true;
               }
               else
               {
                  
                   dataGridView1.Rows[row_index].Cells[1].Style.ForeColor = Color.Black;

               }

               if (hum < Convert.ToSingle(textBoxMinHum.Text))
               {
                   
                   dataGridView1.Rows[row_index].Cells[2].Style.ForeColor = Color.Blue;
                   flag = true;
               }
               else if (hum > Convert.ToSingle(textBoxMaxHum.Text))
               {
                   
                   dataGridView1.Rows[row_index].Cells[2].Style.ForeColor = Color.Red;
                   flag = true;

               }
               else
               {
                   
                   dataGridView1.Rows[row_index].Cells[2].Style.ForeColor = Color.Black;
               }



               if (flag)
               {
                   dataGridView1.Rows[row_index].Cells[7].Value = "true";
                   dataGridView1.Rows[row_index].Cells[7].Style.ForeColor = Color.Red;
               }
               else
               {
                   dataGridView1.Rows[row_index].Cells[7].Value = "false";
                  
               }







               /*将数据增加到曲线上去*/
               if (chart1.Series[0].Points.Count < axis_max)
               {
                   /*将数据增加到曲线上去*/
                   chart1.Series[0].Points.AddXY(x, Convert.ToSingle( dr[1]));//温度数据
                   chart1.Series[1].Points.AddXY(x, Convert.ToSingle( dr[2]));//湿度数据
               }
               else
               {
                   chart1.Series[0].Points.AddXY(x, Convert.ToSingle(dr[1]));//温度数据
                   chart1.Series[1].Points.AddXY(x, Convert.ToSingle(dr[2]));//湿度数据

                   chart1.Series[0].Points.RemoveAt(0);
                   chart1.Series[1].Points.RemoveAt(0);
                   chart1.ChartAreas[0].AxisX.Minimum = chart1.ChartAreas[0].AxisX.Minimum + 1;
                   chart1.ChartAreas[0].AxisX.Maximum = chart1.ChartAreas[0].AxisX.Maximum + 1;
               }
               x++;
           }
        }
        Random Random1 = new Random();//产生0到1000的随机数int i1=Random1.Next(0,1001);//产
        private void btnInsert_Click(object sender, EventArgs e)
        {
            /**界面数据显示*/

            dataGridView1.Rows.Add();
            int i = 0;
            int row_index = dataGridView1.Rows.Count - 1;
            dataGridView1.Rows[row_index].Cells[0].Value = row_index;

            dataGridView1.Rows[row_index].Cells[1].Value = Random1.Next(0, 100).ToString();

            dataGridView1.Rows[row_index].Cells[2].Value = Random1.Next(0, 100).ToString();

            dataGridView1.Rows[row_index].Cells[4].Value =System.DateTime.Now.ToString();

            this.dataGridView1.FirstDisplayedScrollingRowIndex = this.dataGridView1.Rows.Count - 1;

            string[] sub = new string[6];


            /*插入数据库*/
            Single tmp = Convert.ToSingle(sub[0]);//实时温度
            Single hum = Convert.ToSingle(sub[1]);//实时湿度

            sub[0] = dataGridView1.Rows[row_index].Cells[1].Value.ToString();
            sub[1] = dataGridView1.Rows[row_index].Cells[2].Value.ToString();
            sub[2] =  textBoxMinTmp.Text ;//温度最小值
            sub[3]  = textBoxMaxTmp.Text ;//温度最大值
            sub[4]  = textBoxMinHum.Text ;//湿度最小值
            sub[5]  = textBoxMaxHum.Text ;//湿度最大值
            gDataBase.myDataBaseInsert("Table1", sub);

            /*将数据增加到曲线上去*/
            if (chart1.Series[0].Points.Count < axis_max)
            {
                /*将数据增加到曲线上去*/
                chart1.Series[0].Points.AddXY(x, Convert.ToSingle(dataGridView1.Rows[row_index].Cells[1].Value.ToString()));//温度数据
                chart1.Series[1].Points.AddXY(x, Convert.ToSingle(dataGridView1.Rows[row_index].Cells[2].Value.ToString()));//湿度数据
            }
            else
            {
                chart1.Series[0].Points.AddXY(x, Convert.ToSingle(dataGridView1.Rows[row_index].Cells[1].Value.ToString()));//温度数据
                chart1.Series[1].Points.AddXY(x, Convert.ToSingle(dataGridView1.Rows[row_index].Cells[2].Value.ToString()));//湿度数据

                chart1.Series[0].Points.RemoveAt(0);
                chart1.Series[1].Points.RemoveAt(0);
                chart1.ChartAreas[0].AxisX.Minimum = chart1.ChartAreas[0].AxisX.Minimum + 1;
                chart1.ChartAreas[0].AxisX.Maximum = chart1.ChartAreas[0].AxisX.Maximum + 1;
            }
            x++;
        }

        private void btnDeleteAll_Click(object sender, EventArgs e)
        {
            gDataBase.myDataBaseDeleteALL("Table1");
            dataGridView1.Rows.Clear();
            chart1.Series[0].Points.Clear();
            chart1.Series[1].Points.Clear();
            x = 0;
        }

    }
}
