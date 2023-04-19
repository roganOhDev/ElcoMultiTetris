package org.code;

import java.net.Socket;

public class ClientHandler {
    private final Socket clientSocket;
//    private BufferedReader input;
//    private PrintWriter output;


    public Socket getClientSocket() {
        return clientSocket;
    }
    public ClientHandler(Socket clientSocket) {
        this.clientSocket = clientSocket;
        try {
            System.out.println("ip : " + clientSocket.getInetAddress() + " : " + clientSocket.getPort() + " 와 연결되었습니다.");
            ReceiveThread receiveThread = new ReceiveThread(clientSocket);
            receiveThread.start();
            SendThead sendThead = new SendThead(clientSocket);
            sendThead.start();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

}