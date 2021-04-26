using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;

using System.Data.SqlClient;
using System.Windows.Forms;

namespace 串口轨迹
{
    class myDataBase
    {

        public DataSet     ds =null;                                     //临时存储
        public SqlConnection con = null;                                 //数据库链接
        public SqlDataAdapter sda = null;
        public myDataBase()
        {
                 ds = new DataSet();                                     //临时存储
                 con = new SqlConnection();                             //数据库链接
        }
        public bool myDataBaseConnect(string dbAddr, string dbName, string dbID, string pwd)
        {
            con.ConnectionString = "server="+ dbAddr+
                                   ";database="+ dbName+
                                   "; uid="+dbID+
                                   "; pwd="+pwd;                         //链接字符串
            try
            {
                con.Open();                                              //打开数据库
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.ToString());
                return false;
            }
            
            return true;   
        }

        public void myDataBaseClose()
        {
            sda.Dispose();                                               //关闭执行
            con.Close();                                                //关闭数据库
        }

        public void myDataBaseRead(string tabelName)
        {
            sda = new SqlDataAdapter("select * from " + tabelName, con);  //申明一个桥接器用于数据库读写查询操作
            ds.Clear();
            sda.Fill(ds);                                               //将数据填充到临时存储表格中
        }

        public void myDataBaseInsert(string tabelName, string[] data)
        {
            sda = new SqlDataAdapter("select * from " + tabelName, con);//申明一个桥接器用于数据库读写查询操作
            DataSet tmpds = new DataSet();
            sda.Fill(tmpds);                                               //将数据填充到临时存储表格中                               
            SqlCommandBuilder scb = new SqlCommandBuilder(sda);
            sda.UpdateCommand = scb.GetUpdateCommand();
            tmpds.Tables[0].Rows.Add();
            Console.WriteLine(tmpds.Tables[0].Rows.Count);
            int offset = tmpds.Tables[0].Rows.Count - 1;
            tmpds.Tables[0].Rows[offset][0] = tmpds.Tables[0].Rows.Count;
            tmpds.Tables[0].Rows[offset][1] = data[0];//实时
            tmpds.Tables[0].Rows[offset][2] = data[1];//实时
            tmpds.Tables[0].Rows[offset][3] = data[2];
            tmpds.Tables[0].Rows[offset][4] = data[3];
            tmpds.Tables[0].Rows[offset][5] = data[4];
            tmpds.Tables[0].Rows[offset][6] = data[5];
            tmpds.Tables[0].Rows[offset][7] = System.DateTime.Now.ToString();
            sda.Update(tmpds);                                      //更新到数据库
        }

        public void myDataBaseDelete(string tabelName)
        {
            sda = new SqlDataAdapter("select * from " + tabelName, con);//申明一个桥接器用于数据库读写查询操作
            DataSet tmpds = new DataSet();
            sda.Fill(tmpds);                                               //将数据填充到临时存储表格中                               
            SqlCommandBuilder scb = new SqlCommandBuilder(sda);
            sda.UpdateCommand = scb.GetUpdateCommand();
            sda.DeleteCommand = scb.GetDeleteCommand();
            if (tmpds.Tables[0].Rows.Count > 0)
            {
                tmpds.Tables[0].Rows[tmpds.Tables[0].Rows.Count - 1].Delete();
            } 
            sda.Update(tmpds);                                      //更新到数据库
        }

        public void myDataBaseDeleteALL(string tabelName)
        {
            sda = new SqlDataAdapter("select * from " + tabelName, con);//申明一个桥接器用于数据库读写查询操作
            DataSet tmpds = new DataSet();
            sda.Fill(tmpds);                                               //将数据填充到临时存储表格中                               
            SqlCommandBuilder scb = new SqlCommandBuilder(sda);
            sda.UpdateCommand = scb.GetUpdateCommand();
            sda.DeleteCommand = scb.GetDeleteCommand();

            int cout = tmpds.Tables[0].Rows.Count;
            for (int i = 0; i < cout; i++)
            {
                tmpds.Tables[0].Rows[0].Delete();
                sda.Update(tmpds); //更新数据
            }
        }

    }
}
