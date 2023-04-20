package org.code;

import java.net.Socket;
import java.util.List;

public class Utils {

    public void broadCastThatNewClient(final List<ClientHandler> clients, final List<MessageSender> messageSenders, final String message, final Socket newSock) {
        for (int i = 0; i < clients.size(); i++) {
            sendMessageToOtherClients(clients, messageSenders, message, newSock, i);
        }
    }

    private void sendMessageToOtherClients(final List<ClientHandler> clients, final List<MessageSender> messageSenders, final String message, final Socket newSock, final int clientIndex) {
        if (clients.get(clientIndex).getClientSocket() != newSock) {
            try {
                messageSenders.get(clientIndex).send(message);

            } catch (Exception e) {
                Log.log.error("Error While Broadcasting Message : " + e.getMessage());
                removeClient(clients, messageSenders, clientIndex);
            }
        }
    }

    public void removeClient(final List<ClientHandler> clients, final List<MessageSender> messageSenders, final int clientIndex) {
        Log.log.warn("Removing Client : " + clients.get(clientIndex).getInfo());

        clients.get(clientIndex).close();
        clients.remove(clientIndex);
        messageSenders.remove(clientIndex);

        Log.log.info("Client Removed");
    }
}
