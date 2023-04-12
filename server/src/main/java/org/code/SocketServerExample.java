package org.code;

import java.net.*;
import java.io.*;

public class SocketServerExample {
    public static void run() throws IOException {
        ServerSocket serverSocket = null;
        try {
            serverSocket = new ServerSocket(12345);
        } catch (IOException e) {
            System.err.println("Could not listen on port: 12345.");
            System.exit(1);
        }

        Socket[] clientSockets = new Socket[2];
        PrintWriter[] out = new PrintWriter[2];
        BufferedReader[] in = new BufferedReader[2];

        try {
            // Wait for two clients to connect
            for (int i = 0; i < 1; i++) {
                clientSockets[i] = serverSocket.accept();
                out[i] = new PrintWriter(clientSockets[i].getOutputStream(), true);
                in[i] = new BufferedReader(new InputStreamReader(clientSockets[i].getInputStream()));
                System.out.println("Client " + (i + 1) + " connected.");
            }
            System.out.println("Client Connected: " + clientSockets[0].getInetAddress().getHostAddress() + ":" + clientSockets[0].getPort());
            System.out.println("Two clients connected. Starting game...");

            String inputLine;
            out[0].println("Welcome to the game! You are player 1.");

            ReceiveThread receiveThread = new ReceiveThread(clientSockets[0]);
            receiveThread.start();
            SendThead sendThead = new SendThead(clientSockets[0]);
            sendThead.start();

//            while ((inputLine = in[0].readLine()) != null) { //read messages from client
//                System.out.println("Received message: " + inputLine);
//                out[0].println("Echo: " + inputLine); //echo message back to client
//
//                while ((inputLine = in[0].readLine()) != null) {
//                    if (inputLine.equals("ack")) {
//                        System.out.println("Client acknowledged message.");
//                        break;
//                    }
//                }
//
//                // TODO: Implement game logic here
//            }

        } catch (IOException e) {
            System.err.println("Accept failed.");
            System.exit(1);
        } finally {
            // Close connections
            for (int i = 0; i < 1; i++) {
                out[i].close();
                clientSockets[i].close();
            }
            serverSocket.close();
        }
    }
}