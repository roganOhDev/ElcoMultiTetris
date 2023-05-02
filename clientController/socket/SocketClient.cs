using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class SocketClient
{
    private const int PORT = 8888;
    private const int MAX_BUFFER_SIZE = 1024;

    public void Run()
    {
        var ipAddress = IPAddress.Parse("127.0.0.1");
        var remoteEp = new IPEndPoint(ipAddress, PORT);

        // Create a TCP/IP socket
        var socket = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

        try
        {
            // Connect to the remote endpoint
            socket.Connect(remoteEp);
            Console.WriteLine("Socket connected to {0}", socket.RemoteEndPoint.ToString());

            // Add socket to select set
            while (true)
            {
                if (socket.Poll(-1, SelectMode.SelectRead))
                {
                    var buffer = new byte[MAX_BUFFER_SIZE];
                    var bytesRec = socket.Receive(buffer);
                    if (bytesRec > 0)
                    {
                        Console.WriteLine("Received data: {0}", Encoding.ASCII.GetString(buffer, 0, bytesRec));
                    }
                    else
                    {
                        Console.WriteLine("Server disconnected");
                        break;
                    }
                }

                if (Console.KeyAvailable)
                {
                    var message = Console.ReadLine();
                    var msg = Encoding.ASCII.GetBytes(message);
                    var bytesSent = socket.Send(msg);
                    if (bytesSent == 0)
                    {
                        Console.WriteLine("Send failed");
                        break;
                    }
                }
            }

            // Release the socket
            socket.Shutdown(SocketShutdown.Both);
            socket.Close();
        }
        catch (Exception e)
        {
            Console.WriteLine(e.ToString());
        }
    }
}