import com.sun.tools.javac.Main;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

interface SetLoader {
    Set<PostProfile> loadData();
}


class PostProfile implements Comparable<PostProfile> {

    protected String user;
    protected String password;

    public PostProfile(String user, String password) {
        this.user = user;
        this.password = password;
    }

    public String getUser() { return user; }
    public void setUser(String user) { this.user = user; }
    public String getPassword() { return password; }
    public void setPassword(String password) { this.password = password; }

    @Override
    public String toString() {
        return "User = " + user  +
                ", Password = " + password;
    }

    // имплементация на еквивалентност по потребирел и парола
    public boolean equals(Object from) {
        return user.equals(((PostProfile) from).user) &&
                password.equals(((PostProfile) from).password);
    }

    // имплементация на интерфейса по потребител и парола при равенство
    @Override
    public int compareTo(PostProfile from) {
        return user.compareTo(from.user) == 0
                ? password.compareTo((from).password)
                : user.compareTo((from).user);
    }
}

class ProfileManager implements SetLoader {

    protected String fileName = null;

    public ProfileManager(String fileName) {
        this.fileName = fileName;
    }

    @Override
    public Set<PostProfile> loadData() {
        Set<PostProfile> collection = new TreeSet<>();
        try {
            Scanner in = new Scanner(new File(fileName));
            while (in.hasNext()) {
                collection.add(new PostProfile(in.next(), in.next()));
            }
            in.close();

        } catch (FileNotFoundException e) {
            System.out.println("File Not Found...");
        }
        return collection;
    }
}

public class MainPost {   // Post Server
    protected String serverIp;
    Set<PostProfile> accounts = new TreeSet<>();

    public MainPost(String serverIp, ProfileManager pM) {
        this.serverIp = serverIp;
        accounts = pM.loadData();
    }

    public String getServerIp() { return serverIp; }
    public void setServerIp(String serverIp) { this.serverIp = serverIp; }

    public PostProfile searchAccount(String userName, String pass) {
        PostProfile toFind = new PostProfile(userName, pass);

        // ceiling is used to return the least element in this set greater
        // than or equal to the given element, or null if there is no such element.
        if (((TreeSet<PostProfile>) accounts).ceiling(toFind).equals(toFind)){
            return (PostProfile) ((TreeSet<PostProfile>) accounts).ceiling(toFind);
        } else
            return null;
    }

    public List<String> searchUser(String name) {
        List<String> result = new ArrayList<>();
        for (PostProfile cur : accounts) {
            if ((cur.getUser().equals(name))) {
                result.add(cur.getPassword());
            }
        }
        return result;
    }

    public static void main(String[] args) {
        MainPost objP2=new MainPost("123.123. 12.1.", new ProfileManager("PostServer.txt"));
        System.out.println(objP2.toString());
        String findUserName="U3333456";
        PostProfile searchUser = objP2.searchAccount(findUserName, "pass2");
        System.out.println("Find User : "+searchUser);
        List<String> searchSet=objP2.searchUser(findUserName);
        if(searchSet!=null){
            System.out.println("Found List of : "+findUserName+" are "+searchSet);
        }else{
            System.out.println("No Found List of : " +findUserName);
        }
    }
}
