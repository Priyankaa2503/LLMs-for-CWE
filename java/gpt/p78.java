public class p78 {
    static class Person {
        int status;
        String name;
    }

    public static void main(String[] args) {
        // Allocate a new Person (Java's `new` is similar to memory allocation)
        Person p = new Person();
        p.status = 0;
        p.name = "John";

        System.out.printf("Person: status=%d, name=%s%n", p.status, p.name);
    }
}
