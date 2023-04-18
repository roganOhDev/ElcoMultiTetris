package org.code;

import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.net.SocketException;

public class ReceiveThread extends Thread {

    private final Socket socket;

    public ReceiveThread(Socket socket) {
        this.socket = socket;
    }

    @Override
    public void run() {
        try {
//            final var tmpbuf = new InputStream(socket.getInputStream());
//            String receiveString;
            while (true) {
                InputStream inputStream = socket.getInputStream();
                byte[] buffer = new byte[1024];
                int numBytes = inputStream.read(buffer);

                if (numBytes != -1) {
                    String receivedData = new String(buffer, 0, numBytes);
                    System.out.println("Received data: " + receivedData);
                }

//                receiveString = tmpbuf.readUTF();
//                System.out.println("상대방 : " + receiveString);
            }
        } catch (SocketException e1) {
            System.out.println("상대방 연결이 종료되었습니다.");
        } catch (IOException e2) {
            e2.printStackTrace();
        }
    }

}