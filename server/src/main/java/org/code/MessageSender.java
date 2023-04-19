package org.code;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;

public class MessageSender {
    private final PrintWriter printWriter;

    public MessageSender(Socket socket) throws IOException {
        this.printWriter = new PrintWriter(socket.getOutputStream());
    }

    public PrintWriter getPrintWriter(){
        return printWriter;
    }
}
