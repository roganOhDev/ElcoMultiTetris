package org.code;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class Main {
    private static final int PORT = 8888;
    private static final String NEW_CLIENT_MESSAGE = "Here's New Challenger!";

    public static final ArrayList<ClientHandler> clients = new ArrayList<>();
    public static final ArrayList<MessageSender> messageSenders = new ArrayList<>();

    private static final Utils utils = new Utils();

    public static void main(String[] args) {
        try (var socketServer = new ServerSocket(PORT)) {

            while (true) {
                Socket sock = socketServer.accept();

                final var clientHandler = new ClientHandler(sock, messageSenders);
                clients.add(clientHandler);

                utils.broadCastThatNewClient(clients, messageSenders, NEW_CLIENT_MESSAGE, sock);
            }

        } catch (IOException e) {
            Log.log.error("Error While Creating Server Socket : " + e.getMessage());
        }
    }

}