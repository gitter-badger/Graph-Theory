public class Edge {
    private Vertex adj;
    private int weight;

    public Edge() {
        this.adj = null;
        this.weight = 0;
    }

    public Edge(Vertex adj, int weight) {
        this.adj = adj;
        this.weight = weight;
    }

    public Vertex getAdj() {
        return adj;
    }

    public void setAdj(Vertex adj) {
        this.adj = adj;
    }

    public int getWeight() {
        return weight;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }
}