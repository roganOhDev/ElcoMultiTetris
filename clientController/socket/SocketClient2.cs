using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class SocketClient2 
{
    public class Client
    {
        Socket mainSock;
        private int PORT = 8888;
        private string HOST = "127.0.0.1";
        public AsyncObject ao;

        public void Connect()
        {
            mainSock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            IPAddress serverAddr = IPAddress.Parse(HOST);
            IPEndPoint clientEP = new IPEndPoint(serverAddr, PORT);
            mainSock.BeginConnect(clientEP, new AsyncCallback(ConnectCallback), mainSock);
        }

        public void Close()
        {
            if (mainSock != null)
            {
                mainSock.Close();
                mainSock.Dispose();
            }
        }

        public class AsyncObject
        {
            public byte[] Buffer;
            public Socket WorkingSocket;
            public readonly int BufferSize;

            public AsyncObject(int bufferSize)
            {
                BufferSize = bufferSize;
                Buffer = new byte[(long)BufferSize];
            }

            public void ClearBuffer()
            {
                Array.Clear(Buffer, 0, BufferSize);
            }
        }

        void ConnectCallback(IAsyncResult ar)
        {
            try
            {
                Socket client = (Socket)ar.AsyncState;
                client.EndConnect(ar);
                AsyncObject obj = new AsyncObject(4096);
                obj.WorkingSocket = mainSock;
                mainSock.BeginReceive(obj.Buffer, 0, obj.BufferSize, 0, DataReceived, obj);
                
                ao = obj;
            }
            catch (Exception e)
            {
            }
        }

        void DataReceived(IAsyncResult ar)
        {
            AsyncObject obj = (AsyncObject)ar.AsyncState;

            int received = obj.WorkingSocket.EndReceive(ar);

            byte[] buffer = new byte[received];

            Array.Copy(obj.Buffer, 0, buffer, 0, received);
        }

        public void Send(byte[] msg)
        {
            mainSock.Send(msg);
        }
    }

}