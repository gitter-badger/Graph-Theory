import java.util.ArrayList;

public class User extends Vertex {
    private int userID;
    private String gender;
    private int age;
    private int occupation;

    public User() {
        super();
        this.userID = 0;
        this.gender = "";
        this.age = 0;
        this.occupation = 0;
    }

    public User(ArrayList<Edge> edges, int userID, String gender, int age, int occupation) {
        super(edges);
        this.userID = userID;
        this.gender = gender;
        this.age = age;
        this.occupation = occupation;
    }

    public int getUserID() {
        return userID;
    }

    public void setUserID(int userID) {
        this.userID = userID;
    }

    public String getGender() {
        return gender;
    }

    public void setGender(String gender) {
        this.gender = gender;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public int getOccupation() {
        return occupation;
    }

    public void setOccupation(int occupation) {
        this.occupation = occupation;
    }
}