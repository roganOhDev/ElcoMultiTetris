using Avalonia;
using System;
using System.Text;
using System.Threading;

namespace AvaloniaApplication3
{
    internal class Program
    {
        // Initialization code. Don't use any Avalonia, third-party APIs or any
        // SynchronizationContext-reliant code before AppMain is called: things aren't initialized
        // yet and stuff might break.
        [STAThread]
        public static void Main(string[] args)
        {
            // var socketClient = new SocketClient();
            // var thread = new Thread(socketClient.Run);
            // thread.Start();
            // SocketClient2.Client client = new SocketClient2.Client();
            // client.Connect();
            // var msg = Encoding.UTF8.GetBytes("Hello World!");
        
            // client.Send(msg);
            
            
            BuildAvaloniaApp()
                .StartWithClassicDesktopLifetime(args);

            
            // if (client.ao.Buffer.ToString() != null)
            // {
                // Console.Out.Write(client.ao.Buffer);
            // }
        }

        // Avalonia configuration, don't remove; also used by visual designer.
        public static AppBuilder BuildAvaloniaApp()
            => AppBuilder.Configure<App>()
                .UsePlatformDetect()
                .LogToTrace();
    }
}