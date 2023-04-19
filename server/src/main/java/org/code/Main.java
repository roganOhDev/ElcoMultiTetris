package org.code;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class Main {
    private static final List<ClientHandler> clients = new ArrayList<>();

    public static void main(String[] args) throws IOException {
        int port = 8888;
        ServerSocket socketServer = new ServerSocket(port);
        while (true) {
            Socket sock = socketServer.accept();

            final var clientHandler = new ClientHandler(sock);
            clients.add(clientHandler);

            broadcast("here's new challenger", sock);

        }
    }

    static public void broadcast(String message, Socket sock) throws IOException {
        for (ClientHandler client : clients) {
            if (client.getClientSocket() != sock) {
                final var pw = new PrintWriter(client.getClientSocket().getOutputStream());

                pw.println(message);
                pw.flush();
            }
        }
    }
}