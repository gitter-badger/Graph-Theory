import java.util.ArrayList;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.List;
import java.io.PrintWriter;
import java.util.Scanner;

public class Graph {
    private HashMap<String, Vertex> vertices;

    public Graph() {
        this.vertices = new HashMap<>();
    }

    public Graph(HashMap<String, Vertex> vertices) {
        this.vertices = vertices;
    }

    public HashMap<String, Vertex> getVertices() {
        return this.vertices;
    }

    public void setVertices(HashMap<String, Vertex> vertices) {
        this.vertices = vertices;
    }

    public int readUsersFile(String filename) {
        String[] str;
        FileInputStream in = null;
        try {
            in = new FileInputStream(filename);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        Scanner scanner = new Scanner(in);
        while (scanner.hasNextLine()) {
            // users format: UserID::Gender::Age::Occupation::Zip-code
            str = scanner.nextLine().split("::");
            String id = "u" + str[0];
            Vertex v = new User(
                    new ArrayList<>(),
                    Integer.parseInt(str[0]),
                    str[1],
                    Integer.parseInt(str[2]),
                    Integer.parseInt(str[3])
            );
            this.vertices.put(id, v);
        }
        scanner.close();
        return 1;
    }

    public int readMoviesFile(String filename) {
        String[] str;
        String[] genres;
        FileInputStream in = null;
        try {
            in = new FileInputStream(filename);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        Scanner scanner = new Scanner(in);
        while (scanner.hasNextLine()) {
            // movies format: MovieID::Title::Genres
            str = scanner.nextLine().split("::");
            String id = "m" + str[0];
            genres = str[2].split("[|]");
            ArrayList<String> genera = new ArrayList<>();
            for (String g : genres) {
                genera.add(g);
            }
            Vertex v = new Movie(
                    new ArrayList<>(),
                    Integer.parseInt(str[0]),
                    str[1],
                    genera
            );
            this.vertices.put(id, v);
        }
        scanner.close();
        return 1;
    }

    public int readRatingsFile(String filename) {
        String[] str;
        FileInputStream in = null;
        try {
            in = new FileInputStream(filename);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        Scanner scanner = new Scanner(in);
        while (scanner.hasNextLine()) {
            // ratings format: UserID::MovieID::Rating::Timestamp
            str = scanner.nextLine().split("::");
            int stars = Integer.parseInt(str[2]);
            Vertex user = this.getVertices().get("u"+str[0]);
            Vertex movie = this.getVertices().get("m"+str[1]);
            Edge edge1 = new Edge(movie, stars);
            Edge edge2 = new Edge(user, stars);
            user.getEdges().add(edge1);
            movie.getEdges().add(edge2);
        }
        scanner.close();
        return 1;
    }

    public int writeFile(String filename, List<Vertex> list) throws FileNotFoundException {
        PrintWriter writer = new PrintWriter(filename);
        writer.println(list.size());
        list.forEach(vertex -> writer.println(vertex.toString()));
        writer.close();
        return 1;
    }

    public void sort(List<Vertex> movies, int stars) {
        movies.sort((m1, m2) -> {
            int cmp = Integer.compare(
                m1.getNumberOfEdgesGreaterEqual(stars),
                m2.getNumberOfEdgesGreaterEqual(stars)
            );
            return cmp;
        });
    }

    public List<Vertex> GR_Req1(int userID) {
        List<Vertex> result = new ArrayList<>();
        this.vertices.get("u" + String.valueOf(userID)).getEdges().forEach(edge -> {
            if (edge.getWeight() >= 3) {
                result.add(edge.getAdj());
            }
        });
        return result;
    }

    public List<Vertex> GR_Req2(int movieID) {
        List<Vertex> result = new ArrayList<>();
        this.vertices.get("m" + String.valueOf(movieID)).getEdges().forEach(edge -> {
            if (edge.getWeight() >= 3) {
                result.add(edge.getAdj());
            }
        });
        return result;
    }

    public List<Vertex> GR_Req3(int movieID) {
        List<Vertex> result = new ArrayList<>();
        this.vertices.get("m" + String.valueOf(movieID)).getEdges().forEach(edge -> {
            if (edge.getWeight() > 3 && edge.getAdj().isGreater(3, movieID)) {
                result.add(edge.getAdj());
            }
        });
        return result;
    }

    public List<Vertex> GR_Req4(int userID, int movieID) {
        List<Vertex> result = new ArrayList<>();
        Vertex user = this.vertices.get("u"+String.valueOf(userID));
        Vertex movie = this.vertices.get("m"+String.valueOf(movieID));
        movie.getEdges().forEach(edge -> {
            User tempUser = ((User)edge.getAdj());
            if (tempUser.getUserID() != userID && tempUser.getAge() == ((User)user).getAge()) {
                if (edge.getWeight() >= movie.getWeightOf(user)) {
                    result.add(tempUser);
                }
            }
        });
        return result;
    }

    public List<Vertex> GR_Req5(int userID, int movieID) {
        List<Vertex> result = new ArrayList<>();
        User user = ((User)this.vertices.get("u"+String.valueOf(userID)));
        Movie movie = ((Movie)this.vertices.get("m"+String.valueOf(movieID)));
        int stars = user.getWeightOf(movie);
        movie.getEdges().forEach(edge -> {
            User tempUser = ((User)edge.getAdj());
            if (tempUser.getWeightOf(movie) == stars && tempUser.getGender().equalsIgnoreCase(user.getGender())) {
                tempUser.getEdges().forEach(edge1 -> {
                    Movie tempMovie = ((Movie)edge1.getAdj());
                    if (tempMovie.compareGenre(movie) && tempMovie.getWeightOf(tempUser) >= stars) {
                        if (!result.contains(tempMovie)) {
                            result.add(tempMovie);
                        }
                    }
                });
            }
        });
        sort(result, stars);
        if (result.size() > 15) {
            result.subList(0, result.size() - 15).clear();
        }
        return result;
    }

    public List<Vertex> GR_Req6(int userID, int movieID) {
        List<Vertex> result = new ArrayList<>();
        User user = ((User)this.vertices.get("u"+String.valueOf(userID)));
        Movie movie = ((Movie)this.vertices.get("m"+String.valueOf(movieID)));
        int userOccupation = user.getOccupation();
        int stars = user.getWeightOf(movie);
        movie.getEdges().forEach(edge -> {
            User tempUser = ((User)edge.getAdj());
            if (tempUser.getWeightOf(movie) == stars && tempUser.getOccupation() == userOccupation) {
                tempUser.getEdges().forEach(edge1 -> {
                    Movie tempMovie = ((Movie)edge1.getAdj());
                    if (tempMovie.compareGenre(movie) && tempMovie.getWeightOf(tempUser) >= stars) {
                        if (!result.contains(tempMovie)) {
                            result.add(tempMovie);
                        }
                    }
                });
            }
        });
        sort(result, stars);
        if (result.size() > 10) {
            result.subList(0, result.size() - 10).clear();
        }
        return result;
    }

    public List<Vertex> GR_Req7(int userID, int movieID) {
        List<Vertex> result = new ArrayList<>();
        Movie movie = ((Movie)this.vertices.get("m"+String.valueOf(movieID)));
        movie.getEdges().forEach(edge -> {
            User tempUser = ((User)edge.getAdj());
            if (tempUser.getUserID() != userID && tempUser.getWeightOf(movie) < 3) {
                tempUser.getEdges().forEach(edge1 -> {
                    Movie tempMovie = ((Movie)edge1.getAdj());
                    if (tempMovie.getWeightOf(tempUser) >= 3) {
                        if (!result.contains(tempMovie)) {
                            result.add(tempMovie);
                        }
                    }
                });
            }
        });
        sort(result, 3);
        if (result.size() > 5) {
            result.subList(0, result.size() - 5).clear();
        }
        return result;
    }
}
