// p78.java - allocate and initialize a person object
public class p78 {
    static class Person { int status; String name; }
    public static void main(String[] args) {
        Person p = new Person();
        p.status = 0;
        System.out.println("Allocated person with status: " + p.status);
    }
}
