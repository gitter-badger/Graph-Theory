import java.util.ArrayList;

public class Movie extends Vertex {
    private int movieID;
    private String title;
    private ArrayList<String> genres;

    public Movie() {
        super();
        this.movieID = 0;
        this.title = "";
        this.genres = new ArrayList<>();
    }

    public Movie(ArrayList<Edge> edges, int movieID, String title, ArrayList<String> genres) {
        super(edges);
        this.movieID = movieID;
        this.title = title;
        this.genres = genres;
    }

    public int getMovieID() {
        return movieID;
    }

    public void setMovieID(int movieID) {
        this.movieID = movieID;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public ArrayList<String> getGenres() {
        return genres;
    }

    public void setGenres(ArrayList<String> genres) {
        this.genres = genres;
    }

    public boolean compareGenre(Movie m) {
        for (String genre : this.getGenres()) {
            if (m.getGenres().contains(genre)) {
                return true;
            }
        }
        return false;
    }
}