package org.code;

import java.io.IOException;
import java.net.Socket;
import java.util.List;

import static org.code.Log.log;

public class ClientHandler {
    private final Socket clientSocket;


    public Socket getClientSocket() {
        return clientSocket;
    }

    public ClientHandler(Socket clientSocket, List<MessageSender> messageSenders) {
        this.clientSocket = clientSocket;

        try {
            log.info("Client Connected : " + getInfo());

            ReceiveThread receiveThread = new ReceiveThread(clientSocket);
            receiveThread.start();

            messageSenders.add(new MessageSender(clientSocket));

        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public void close() {
        try {
            clientSocket.close();
        } catch (IOException e) {
            log.warn("Error While Closing Socket : " + getInfo());
        }
    }

    public String getInfo() {
        return clientSocket.getInetAddress() + " : " + clientSocket.getPort();
    }

}