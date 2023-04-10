package org.code;

import lombok.RequiredArgsConstructor;

import java.io.IOException;

@RequiredArgsConstructor
public class Main {

    public static void main(String[] args) throws IOException, ClassNotFoundException {
        System.out.println("Hello world!");

        final var a = new SocketServerExample();
        a.run();
    }
}