import java.io.*;
import java.net.*;

public class Tester {
    private ServerSocket server;

    public static void main(String[] args) {
        try {
            new Tester().run();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public Tester() throws Exception {
        server = new ServerSocket(80);
    }

    public void run() throws Exception {
        Socket socket = server.accept();
        System.out.println("Accepted a connection.");
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        while (true) {
            String received = in.readLine();
            System.out.println("Received: " + received);
            System.out.println("" + (int)(received.charAt(received.length()-1)) + "\t" + (int)(received.charAt(received.length()-2)) + "\t" + (int)(received.charAt(received.length()-3)));
        }
    }
}
