package org.code;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class Main {
    private static final List<ClientHandler> clients = new ArrayList<>();
    private static final List<MessageSender> messageSenders = new ArrayList<>();

    public static void main(String[] args) throws IOException {
        int port = 8888;

        ServerSocket socketServer = new ServerSocket(port);
        while (true) {
            Socket sock = socketServer.accept();

            final var clientHandler = new ClientHandler(sock, messageSenders);
            clients.add(clientHandler);

            broadcast("here's new challenger", sock);
        }
    }

    static public void broadcast(String message, Socket newSock) {
        for (int i = 0; i < clients.size(); i++) {
            if (clients.get(i).getClientSocket() != newSock) {
                try {
                    final var printWriter = messageSenders.get(i).getPrintWriter();

                    printWriter.println(message);
                    printWriter.flush();
                } catch (Exception e) {
                    Log.log.error("Error While Broadcasting Message : " + e.getMessage());
                    removeClient(i);
                }
            }
        }
    }

    static private void removeClient(final int clientIndex) {
        Log.log.warn("Removing Client : " + clients.get(clientIndex).getClientSocket().getInetAddress() + " : " + clients.get(clientIndex).getClientSocket().getPort());
        clients.get(clientIndex).close();
        clients.remove(clientIndex);
        messageSenders.remove(clientIndex);
        Log.log.info("Client Removed");
    }
}