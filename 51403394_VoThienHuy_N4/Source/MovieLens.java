import java.io.Console;
import java.io.FileNotFoundException;

public class MovieLens {
    public static void main(String[] args) throws FileNotFoundException {
        Graph g = Graph.empty();

        g.readUsersFile("users.dat");
        g.readMoviesFile("movies.dat");
        g.readRatingsFile("ratings.dat");

        Console console = System.console();
        int userID;
        int movieID;
        String question;
        
        while (true) {
            question = console.readLine("Enter question or 'q' to quit: ");
            if (question.equals("q")) {
                System.out.println("See you next time!");
                break;
            }
            switch (question) {
                case "1":
                    userID = Integer.parseInt(console.readLine("Enter userID: "));
                    g.writeFile("51403394_VoThienHuy_Nhom4_Req1.dat", g.GR_Req1(userID));
                    break;
                case "2":
                    movieID = Integer.parseInt(console.readLine("Enter movieID: "));
                    g.writeFile("51403394_VoThienHuy_Nhom4_Req2.dat", g.GR_Req2(movieID));
                    break;
                case "3":
                    movieID = Integer.parseInt(console.readLine("Enter movieID: "));
                    g.writeFile("51403394_VoThienHuy_Nhom4_Req3.dat", g.GR_Req3(movieID));
                    break;
                case "4":
                    userID = Integer.parseInt(console.readLine("Enter userID: "));
                    movieID = Integer.parseInt(console.readLine("Enter movieID: "));
                    g.writeFile("51403394_VoThienHuy_Nhom4_Req4.dat", g.GR_Req4(userID, movieID));
                    break;
                case "5":
                    userID = Integer.parseInt(console.readLine("Enter userID: "));
                    movieID = Integer.parseInt(console.readLine("Enter movieID: "));
                    g.writeFile("51403394_VoThienHuy_Nhom4_Req5.dat", g.GR_Req5(userID, movieID));
                    break;
                case "6":
                    userID = Integer.parseInt(console.readLine("Enter userID: "));
                    movieID = Integer.parseInt(console.readLine("Enter movieID: "));
                    g.writeFile("51403394_VoThienHuy_Nhom4_Req6.dat", g.GR_Req6(userID, movieID));
                    break;
                case "7":
                    userID = Integer.parseInt(console.readLine("Enter userID: "));
                    movieID = Integer.parseInt(console.readLine("Enter movieID: "));
                    g.writeFile("51403394_VoThienHuy_Nhom4_Req7.dat", g.GR_Req7(userID, movieID));
                    break;
            }
        }
    }
}