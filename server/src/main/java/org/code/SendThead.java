package org.code;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

public class SendThead extends Thread {

    private final Socket socket;
    private Scanner scanner = new Scanner(System.in);

    public SendThead(Socket socket) {
        this.socket = socket;
    }

    @Override
    public void run() {
        try {
            String sendString;
            while (true) {
                sendString = scanner.nextLine();
                final var pw = new PrintWriter(socket.getOutputStream());

                pw.println(sendString);
                pw.flush();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}