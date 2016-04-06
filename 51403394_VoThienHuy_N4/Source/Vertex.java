import java.util.ArrayList;

public class Vertex {
    private ArrayList<Edge> edges;

    public Vertex() {
        this.edges = new ArrayList<>();
    }

    public Vertex(ArrayList<Edge> edges) {
        this.edges = edges;
    }

    public ArrayList<Edge> getEdges() {
        return edges;
    }

    public void setEdges(ArrayList<Edge> edges) {
        this.edges = edges;
    }

    public boolean isGreater(int stars, int movieID) {
        for (Edge edge : this.getEdges()) {
            if (edge.getWeight() > stars &&((Movie)edge.getAdj()).getMovieID() != movieID) {
                return true;
            }
        }
        return false;
    }

    public int getWeightOf(Vertex adj) {
        for (Edge edge : this.getEdges()) {
            if (edge.getAdj() == adj) {
                return edge.getWeight();
            }
        }
        return 0;
    }

    public int getNumberOfEdgesGreaterEqual(int stars) {
        final int[] result = {0};
        this.getEdges().forEach(edge -> {
            if (edge.getWeight() >= stars) {
                result[0] += 1;
            }
        });
        return result[0];
    }

    @Override
    public String toString() {
        if (this.getClass() == Movie.class) {
            String genres = "";
            for (String genre : ((Movie)this).getGenres()) {
                genres += genre + "|";
            }
            genres = genres.substring(0, genres.length()-1);
            return String.valueOf(((Movie)this).getMovieID())
                    + "::" + ((Movie)this).getTitle()
                    + "::" + genres;
        } else  {
            return String.valueOf(((User)this).getUserID()) + "::"
                    + ((User)this).getGender() + "::"
                    + String.valueOf(((User)this).getAge()) + "::"
                    + String.valueOf(((User)this).getOccupation());
        }
    }
}
