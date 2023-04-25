package org.code;

import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;

import static org.code.Log.log;

public class ReceiveThread extends Thread {

    private final Socket socket;
    private final Utils utils = new Utils();

    public ReceiveThread(Socket socket) {
        this.socket = socket;
    }

    @Override
    public void run() {
        try {
            while (true) {
                InputStream inputStream = socket.getInputStream();
                byte[] buffer = new byte[1024];
                int numBytes = inputStream.read(buffer);

                if (numBytes != -1) {
                    receivedData(buffer, numBytes);
                }

            }
        } catch (IOException e1) {
            log.error("Error While Receving Message : ");

            findSocketAndDelete();
        }
    }

    private void findSocketAndDelete() {
        for (int i = 0; i < Main.clients.size(); i++) {
            if (Main.clients.get(i).getClientSocket() == socket) {
                utils.removeClient(Main.clients, Main.messageSenders, i);
            }
        }
    }

    private String receivedData(byte[] buffer, int numBytes) {
        final var receivedData = new String(buffer, 0, numBytes);
        log.info("Received data from " + socket.getInetAddress() + " : " + socket.getPort() + " : " + receivedData);

        return receivedData;
    }

}