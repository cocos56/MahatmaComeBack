using System;
using System.Collections.Generic;
using System.Data;
using System.Windows.Forms;
using SuperWebSocket;
using Newtonsoft.Json.Linq;

public partial class Form1 : Form
{
    public Form1()
    {
        InitializeComponent();
    }

    private void groupBox1_Enter(object sender, EventArgs e)
    {

    }

    // 服务器
    WebSocketServer server;
    Dictionary<WebSocketSession, string> dic = new Dictionary<WebSocketSession, string>();

    /// <summary>
    /// 开始监听按钮按下的时候
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    private void listenerButton_Click(object sender, EventArgs e)
    {
        server = new WebSocketServer();
        if (!server.Setup(ipText.Text, Convert.ToInt16(portText.Text)))
        {
            //绑定IP地址失败的时候
            return;
        }
        if (!server.Start())
        {
            //监听失败
            return;
        }

        //添加事件侦听
        server.NewSessionConnected += ws_NewSessionConnected;//有新会话握手并连接成功
        server.SessionClosed += ws_SessionClosed;//有会话被关闭 可能是服务端关闭 也可能是客户端关闭
        server.NewMessageReceived += ws_NewMessageReceived;//有客户端发送新的消息

        MessageBox.Show("监听成功");
        showLog("服务器监听成功");
        listenerButton.Enabled = false;
        stopListenerButton.Enabled = true;
    }
    /// <summary>
    ///有新用户连接的时候 
    /// </summary>
    /// <param name="session"></param>
    void ws_NewSessionConnected(WebSocketSession session)
    {
        showLog("客户端" + session.RemoteEndPoint.ToString() + ":连接成功");
    }

    /// <summary>
    ///由用户断开连接的时候 
    /// </summary>
    /// <param name="session"></param>
    /// <param name="value"></param>
    void ws_SessionClosed(WebSocketSession session, SuperSocket.SocketBase.CloseReason value)
    {
        showLog("客户端" + session.RemoteEndPoint.ToString() + ":断开成功");
        try
        {
            var secretKey = dic[session];
            DbConnectionMySQL.ExecuteNonQuery(DbConnectionMySQL.Conn, CommandType.Text, "update game set Online='否' where secretKey='" + secretKey + "'", null);
            SendToAllPosition(secretKey, 0.0f, 0.0f, 0, "remove");
        }
        catch(System.Collections.Generic.KeyNotFoundException)
        {
            dic.Remove(session);
            showData();
        }
    }

    /// <summary>
    /// 接收到客户端发送的消息的时候
    /// </summary>
    /// <param name="session"></param>
    /// <param name="value"></param>
    void ws_NewMessageReceived(WebSocketSession session, string value)
    {
        var json = JObject.Parse(value);
        var type = json["type"].ToString();
        manipulationData(type, json, session);

        //打印客户端发送的消息
        //  showLog("客户端"+session.RemoteEndPoint.ToString() + ":" + value);
    }

    /// <summary>
    /// 服务器向所有客户端发送数据
    /// </summary>
    void SendToMessage(string secretKey, string name,string message)
    {
        //广播所有客户端
        foreach (var sendSession in server.GetAllSessions())
        {
            var key = dic[sendSession];
            if (key != secretKey)
            {
                JObject js = new JObject();
                js.Add("type", "message");
                js.Add("playerName", name);
                js.Add("message", message);

                sendSession.Send(js.ToString());
            }
        }

    }
    /// <summary>
    /// 输出日志
    /// </summary>
    /// <param name="str"></param>
    private void showLog(string str)
    {
        logText.AppendText(DateTime.Now.ToLongTimeString().ToString() + ":" + str + "\n");
    }

    /// <summary>
    /// 界面开始加载的时候
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    private void Form1_Load(object sender, EventArgs e)
    {
        Control.CheckForIllegalCrossThreadCalls = false;
    }

    /// <summary>
    /// 链接数据库按钮按下的时候
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    private void connectMysqlButton_Click(object sender, EventArgs e)
    {
        dataGridView1.DataSource = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game", null).Tables[0].DefaultView;
        MessageBox.Show("链接数据库成功");
        showLog("链接数据库成功");
        connectMysqlButton.Enabled = false;
    }
    /// <summary>
    /// 停止监听服务器
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    private void stopListenerButton_Click(object sender, EventArgs e)
    {
        server.Stop();
        MessageBox.Show("服务器断开连接");
        showLog("服务器断开连接");
        listenerButton.Enabled = true;
        stopListenerButton.Enabled = false;
    }

    /// <summary>
    /// 处理从客户端收到的消息
    /// </summary>
    /// <param name="type">收到的消息类型</param>
    /// <param name="json">收到的json文件</param>
    /// <param name="client">对应的客户端连接</param>
    private void manipulationData(string type, JObject json, WebSocketSession client)
    {
        if (type == "register")
        {
            var account = json["account"].ToString();
            var password = json["password"].ToString();

            //首先判断账号是否已经存在
            if (DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where account='" + account + "'", null).Tables[0].Rows.Count == 0)
            {
                DbConnectionMySQL.ExecuteNonQuery(DbConnectionMySQL.Conn, CommandType.Text, "insert into game(account,password) values('"+ account+"','"+password+"')", null);
                //不存的情况
                JObject js = new JObject();
                js.Add("type", "registerResult");
                js.Add("reason", "true");
                client.Send(js.ToString());
            }
            else
            {
                //账号已经存在的情况
                JObject js = new JObject();
                js.Add("type", "registerResult");
                js.Add("reason", "false");
                client.Send(js.ToString());
            }
        }
        else if (type == "login")
        {
            var account = json["account"].ToString();
            var password = json["password"].ToString();

            var pas = selectMysqlPassword(account);
            if (pas == "")
            {
                //账号不存在
                showLog("客户端" + client.RemoteEndPoint + ":账号不存在");

                JObject js = new JObject();
                js.Add("type", "loginResult");
                js.Add("ifloginSuccess", "false");
                js.Add("reason", "NoAccount");

                client.Send(js.ToString());
            }
            else if (pas == password)
            {
                //登陆成功
                showLog("客户端" + client.RemoteEndPoint + ":登陆成功");
                //将密码和时间组合起来，通过秘钥进行加密
                pas = LoginEncryption.encryptionPassword(pas + DateTime.Now.ToLongTimeString().ToString(), "thisisapassword");

                var playername=DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where account=" + account, null).Tables[0].Rows[0]["playerName"].ToString();
                var playerType= DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where account=" + account, null).Tables[0].Rows[0]["PlayerType"].ToString();
                JObject js = new JObject();
                js.Add("type", "loginResult");
                js.Add("ifloginSuccess", "true");
                js.Add("privatePassword", pas);
                js.Add("playerName", playername);
                if (playername != "")
                {
                    js.Add("playerType", playerType);
                }
                client.Send(js.ToString());
                dic.Add(client, pas);
                DbConnectionMySQL.ExecuteNonQuery(DbConnectionMySQL.Conn, CommandType.Text, "update game set secretkey='" + pas + "' where account=" + account, null);
                showData();
            }
            else
            {
                //密码错误
                showLog("客户端" + client.RemoteEndPoint + ":密码错误");
                JObject js = new JObject();
                js.Add("type", "loginResult");
                js.Add("ifloginSuccess", "false");
                js.Add("reason", "PasswordError");
                client.Send(js.ToString());
            }
        }
        else if(type=="createPlayer")
        {
            var secretKey = json["secretKey"].ToString();
            var name = json["playerName"].ToString();
            var playerType = json["playerType"].ToString();

            //先判断是和数据库中否有重名的情况
            if(DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where playerName='" + name+"'", null).Tables[0].Rows.Count == 0)
            {
                //创建成功
                showLog("客户端" + client.RemoteEndPoint + ":创建角色成功，角色名："+name);
                DbConnectionMySQL.ExecuteNonQuery(DbConnectionMySQL.Conn, CommandType.Text, "update game set playerName='"+name+"',playerType='"+ playerType + "',XPoint=300.0,YPoint=300.0,grade='1',blood='100',direction=1 where secretKey='" + secretKey+"'", null);

                JObject js = new JObject();
                js.Add("type", "craetePlayerResult");
                js.Add("ifSuccess", "true");
                js.Add("playerType", playerType);
                client.Send(js.ToString());
                showData();
            }
            else
            {
                //创建失败，有重名的情况
                showLog("客户端" + client.RemoteEndPoint + ":创建角色失败");

                JObject js = new JObject();
                js.Add("type", "craetePlayerResult");
                js.Add("ifSuccess", "false");
                client.Send(js.ToString());
            }
        }
        else if (type == "loginGameScene")
        {
            var secretKey = json["secretKey"].ToString();//获得通信秘钥

            var playername = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + secretKey + "'", null).Tables[0].Rows[0]["playerName"].ToString();
            var playerType = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + secretKey + "'", null).Tables[0].Rows[0]["PlayerType"].ToString();
            var XPoint = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + secretKey + "'", null).Tables[0].Rows[0]["XPoint"].ToString();
            var YPoint = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + secretKey + "'", null).Tables[0].Rows[0]["YPoint"].ToString();
            var grade = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + secretKey + "'", null).Tables[0].Rows[0]["grade"].ToString();
            var blood = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + secretKey + "'", null).Tables[0].Rows[0]["blood"].ToString();
            var direction = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + secretKey + "'", null).Tables[0].Rows[0]["direction"].ToString();

            JObject js = new JObject();
            js.Add("type", "playerInformation");
            js.Add("playerName", playername);
            js.Add("playerType", playerType);
            js.Add("XPoint", float.Parse(XPoint));
            js.Add("YPoint", float.Parse(YPoint));
            js.Add("grade", int.Parse(grade));
            js.Add("blood", float.Parse(blood));
            js.Add("direction", int.Parse(direction));
            client.Send(js.ToString());

            DbConnectionMySQL.ExecuteNonQuery(DbConnectionMySQL.Conn, CommandType.Text, "update game set Online='是' where secretKey='" + secretKey + "'", null);
            showData();

            showLog("角色" + playername + ":登录游戏");
        }
        else if (type == "nearPlayers")
        {
            var secretKey = json["secretKey"].ToString();//获得通信秘钥

            var playername = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + secretKey + "'", null).Tables[0].Rows[0]["playerName"].ToString();
            var playerType = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + secretKey + "'", null).Tables[0].Rows[0]["PlayerType"].ToString();
            var XPoint = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + secretKey + "'", null).Tables[0].Rows[0]["XPoint"].ToString();
            var YPoint = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + secretKey + "'", null).Tables[0].Rows[0]["YPoint"].ToString();
            var grade = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + secretKey + "'", null).Tables[0].Rows[0]["grade"].ToString();
            var blood = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + secretKey + "'", null).Tables[0].Rows[0]["blood"].ToString();
            var direction = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + secretKey + "'", null).Tables[0].Rows[0]["direction"].ToString();

            JObject js = new JObject();
            js.Add("type", "nearPlayer");
            js.Add("playerName", playername);
            js.Add("playerType", playerType);
            js.Add("XPoint", float.Parse(XPoint));
            js.Add("YPoint", float.Parse(YPoint));
            js.Add("grade", int.Parse(grade));
            js.Add("blood", float.Parse(blood));
            js.Add("direction", int.Parse(direction));
            js.Add("state", "free");
            GetAllLayer(secretKey, client,js);
        }
        else if (type == "position")
        {
            var secretKey = json["secretKey"].ToString();//获得通信秘钥
            var state = json["state"].ToString();        //人物的当前状态

            if(state=="walk")
            {
                var XPoint = float.Parse(json["XPoint"].ToString()); //人物的X坐标
                var YPoint = float.Parse(json["YPoint"].ToString());//人物的Y坐标
                var direction = int.Parse(json["direction"].ToString()); //人物的朝向
                var playerState = json["state"].ToString();
                //更新数据库中人物的信息
                DbConnectionMySQL.ExecuteNonQuery(DbConnectionMySQL.Conn, CommandType.Text, "update game set XPoint="+XPoint+" where secretKey='" + secretKey + "'", null);
                DbConnectionMySQL.ExecuteNonQuery(DbConnectionMySQL.Conn, CommandType.Text, "update game set YPoint=" + YPoint + " where secretKey='" + secretKey + "'", null);
                DbConnectionMySQL.ExecuteNonQuery(DbConnectionMySQL.Conn, CommandType.Text, "update game set direction=" + direction + " where secretKey='" + secretKey + "'", null);

                //广播其他玩家
                SendToAllPosition(secretKey, XPoint, YPoint,direction,playerState);
            }
            else if(state=="free")
            {
                SendToAllPosition(secretKey, 0.0f, 0.0f, 0, "free");
            }
            //   showData();
        }
        else if(type=="message")
        {
            var secretKey = json["secretKey"].ToString();//获得通信秘钥
            var message = json["message"].ToString();    //获得发送的内容
            var name = json["playerName"].ToString();    //获得发送消息的玩家
            SendToMessage(secretKey, name, message);
            showLog("角色" + name + ":发送了一条消息，消息内容为："+message);
        }
}
    
    /// <summary>
    /// 向周围的人广播自己的坐标
    /// </summary>
    /// <param name="secretKey">客户秘钥</param>
    /// <param name="x">X坐标</param>
    /// <param name="y">Y坐标</param>
    /// <param name="direction">方向</param>
    /// <param name="playerState">状态</param>
    void SendToAllPosition(string secretKey, float x,float y,int direction,string playerState)
    {
        //广播所有客户端
        foreach (var sendSession in server.GetAllSessions())
        {
            var key = dic[sendSession];
            if(key!=secretKey)
            {
                try
                {
                    var playername = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + secretKey + "'", null).Tables[0].Rows[0]["playerName"].ToString();
                    var playerType = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + secretKey + "'", null).Tables[0].Rows[0]["PlayerType"].ToString();
                    var grade = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + secretKey + "'", null).Tables[0].Rows[0]["grade"].ToString();
                    var blood = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + secretKey + "'", null).Tables[0].Rows[0]["blood"].ToString();

                    JObject js = new JObject();
                    js.Add("type", "nearPlayer");
                    js.Add("playerName", playername);
                    js.Add("playerType", playerType);
                    js.Add("XPoint", x);
                    js.Add("YPoint", y);
                    js.Add("grade", int.Parse(grade));
                    js.Add("blood", float.Parse(blood));
                    js.Add("direction", direction);
                    js.Add("state", playerState);

                    sendSession.Send(js.ToString());
                }
                catch(System.IndexOutOfRangeException)
                {
                    break;
                }
            }

        }

    }

    /// <summary>
    /// 获得当前玩家周围的所有其他角色
    /// </summary>
    /// <param name="secretKey"></param>
    void GetAllLayer(string secretKey, WebSocketSession client, JObject json)
    {
            
        foreach (var sendSession in server.GetAllSessions())
        {
            var key = dic[sendSession];
            if (key != secretKey)
            {
                try
                {
                    var playername = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + key + "'", null).Tables[0].Rows[0]["playerName"].ToString();
                    var playerType = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + key + "'", null).Tables[0].Rows[0]["PlayerType"].ToString();
                    var grade = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + key + "'", null).Tables[0].Rows[0]["grade"].ToString();
                    var blood = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + key + "'", null).Tables[0].Rows[0]["blood"].ToString();
                    var XPoint = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + key + "'", null).Tables[0].Rows[0]["XPoint"].ToString();
                    var YPoint = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + key + "'", null).Tables[0].Rows[0]["YPoint"].ToString();
                    var direction = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where secretKey='" + key + "'", null).Tables[0].Rows[0]["direction"].ToString();
                    JObject js = new JObject();
                    js.Add("type", "nearPlayer");
                    js.Add("playerName", playername);
                    js.Add("playerType", playerType);
                    js.Add("XPoint", float.Parse(XPoint));
                    js.Add("YPoint", float.Parse(YPoint));
                    js.Add("grade", int.Parse(grade));
                    js.Add("blood", float.Parse(blood));
                    js.Add("direction", int.Parse(direction));
                    js.Add("state", "free");

                    sendSession.Send(json.ToString());
                    client.Send(js.ToString());
                }
                catch(System.IndexOutOfRangeException)
                {
                    break;
                }
            }
        }
    }

    private string selectMysqlPassword(string account)
    {
        var tabel = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game where account=" + account, null).Tables[0];
        if (tabel.Rows.Count == 0)
        {
            return "";
        }
        else
        {
            return tabel.Rows[0]["password"].ToString();
        }
    }

    private void showData()
    {
        dataGridView1.DataSource = null;
        dataGridView1.DataSource = DbConnectionMySQL.GetDataSet(DbConnectionMySQL.Conn, CommandType.Text, "select * from game", null).Tables[0].DefaultView;
    }

    private void button1_Click(object sender, EventArgs e)
    {
        if (Notice.Text != "")
        {
            foreach (var sendSession in server.GetAllSessions())
            {
                JObject js = new JObject();
                js.Add("type", "message");
                js.Add("playerName", "公告");
                js.Add("message", Notice.Text);

                sendSession.Send(js.ToString());
                //添加到公告记录上
                noticeText.AppendText(DateTime.Now.ToLongTimeString().ToString() + ":" + Notice.Text + "\n");

                Notice.Text = "";
            }
        }
    }

    private void IpText_TextChanged(object sender, EventArgs e){}

    private void PortText_TextChanged(object sender, EventArgs e){}
}
